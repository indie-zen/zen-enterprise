//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Engine Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#include "Container.hpp"

#include <Zen/Core/Event/I_EventManager.hpp>
#include <Zen/Core/Event/I_EventService.hpp>

#include <Zen/Core/Plugins/I_Application.hpp>
#include <Zen/Core/Plugins/I_PluginManager.hpp>
#include <Zen/Core/Plugins/I_Configuration.hpp>

#include <Zen/Core/Scripting/I_ScriptingManager.hpp>

#include <Zen/Core/Utility/I_EnvironmentHandler.hpp>

#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>

#include <iostream>

#include <stddef.h>

namespace po = boost::program_options;

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
Container::Container()
:   m_pAppServer(NULL)
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
Container::~Container()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
bool
Container::init(int _argc, const char* _argv[])
{
    // Declare the supported options.
    po::options_description description("Allowed options");

    description.add_options()
        ("help,h", "Produce this help message")
        ("config,c", po::value<std::string>(&m_configPath)->default_value("config.xml"), "Configuration XML file")
        ("lang,l", po::value<std::string>(&m_scriptLanguage)->default_value("lua"), "Script language extension")
        ("script,s", po::value<std::string>(&m_defaultScript)->default_value("initServer.py"), "Boot script")
        ("log-file", po::value<std::string>(&m_logFile)->default_value("Zen.log"), "Output log filename")
        //("interactive,i", po::value<bool>(&m_bRunInteractive)->default_value(false), "Run interactively")
    ;

    po::store(po::parse_command_line(_argc, (char**)_argv, description), m_variables);
    po::notify(m_variables);

    if (m_variables.size() == 0 || m_variables.count("help") == 1)
    {
        std::cout << std::endl << description << std::endl;
        return false;
    }

    std::map<std::string, std::string> newEnv;

    // TODO Fix this.  Skip the arguments that were already processed.
    const int skipArgs = m_variables.size();
    for(int x = skipArgs; x < _argc; x++)
    {
        std::stringstream stream;
        stream << "arg" << x - skipArgs;
        newEnv[stream.str()] = _argv[x];
    }

    Utility::I_EnvironmentHandler& environment = Utility::I_EnvironmentHandler::getDefaultHandler();

    environment.appendEnvironment(newEnv);

    // Initialize application
    boost::filesystem::path configPath = boost::filesystem::system_complete
        (
            boost::filesystem::path(m_configPath)
        ).normalize();

    boost::filesystem::path logPath = boost::filesystem::system_complete
        (
            boost::filesystem::path(m_logFile)
        ).normalize();

    Plugins::I_PluginManager::app_ptr_type pApp = Plugins::I_PluginManager::getSingleton().installApplication(configPath, logPath);

    Zen::Utility::log_stream& logStream(pApp->getLogStream());

    I_ApplicationServerManager& manager =
        I_ApplicationServerManager::getSingleton();

    // Initialize the main application server
    m_pAppServer = &I_ApplicationServer::getInstance("main");

    // Initialize the script engine
    if (!m_scriptLanguage.empty())
    {
        m_pScriptEngine = Scripting::I_ScriptingManager::getSingleton().createScriptEngine(m_scriptLanguage);

        if (!m_pScriptEngine.isValid())
        {
            std::cout << "Error loading script engine: " << m_scriptLanguage << std::endl;
            return false;
        }

        m_pAppServer->registerDefaultScriptEngine(m_pScriptEngine);
    }

    // Initialize the main event service an
    m_pEventService =
        Zen::Event::I_EventManager::getSingleton().create("eventService");

    if (m_pScriptEngine.isValid())
    {
        m_pEventService->registerScriptEngine(m_pScriptEngine);
    }

    pConfig_type pAppConfig = pApp->getConfiguration().getConfigurationElement("application");

    // Install the databases
    pConfig_type pDatabases = pAppConfig->getChild("databases");
    if (pDatabases)
    {
        m_pAppServer->installDatabaseConnections(pDatabases);
    }

    // Install the applications
    pConfig_type pApplications = pAppConfig->getChild("applications");
    if (pApplications)
    {
        m_pAppServer->installApplications(pApplications);
    }

    // Install the protocols
    pConfig_type pProtocols = pAppConfig->getChild("protocols");

    if (pProtocols)
    {
        m_pAppServer->installProtocols(pProtocols);
    }

    m_pAppServer->start();

    return true;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
int
Container::run()
{
    runScriptInit();

    // TODO integrate with the console and wait until told to stop.

    return 0;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
Container::stop()
{
    m_pAppServer->stop();

    /// TODO Need to identify all instances of m_pScriptEngine and make
    /// sure they go out of scope when m_pAppServer->stop() is called.
    m_pScriptEngine.reset();

    /// TODO Need to get the script engine to handle garbage collection
    /// appropriately so that all instances of m_pEventService go out of
    /// scope and its destructor is called when m_pAppServer->stop() is
    /// called.
    m_pEventService.reset();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
I_ApplicationServer&
Container::getApplicationServer()
{
    return *m_pAppServer;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
bool
Container::runScriptInit()
{
    std::cout << "About to run the script." << std::endl;

    if (m_pScriptEngine.isValid())
    {
        if (!m_pScriptEngine->executeScript(m_defaultScript))
        {
            std::cout << "Error loading script " << m_defaultScript << std::endl;
            return false;
        }
    }

    std::cout << "Finished running the script." << std::endl;

    return true;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Enterprise
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
