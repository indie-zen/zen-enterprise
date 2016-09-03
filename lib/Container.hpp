//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Server
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_CONTAINER_HPP_INCLUDED
#define ZEN_ENTERPRISE_CONTAINER_HPP_INCLUDED

#include <Zen/Core/Plugins/I_ConfigurationElement.hpp>

#include <Zen/Core/Scripting/I_ScriptingManager.hpp>
#include <Zen/Core/Scripting/I_ScriptEngine.hpp>

#include <Zen/Enterprise/I_ApplicationServerManager.hpp>
#include <Zen/Enterprise/I_ProtocolService.hpp>
#include <Zen/Enterprise/I_ApplicationService.hpp>
#include <Zen/Enterprise/I_ApplicationServer.hpp>
#include <Zen/Enterprise/I_ResourceLocation.hpp>

#include <boost/program_options.hpp>

#include <string>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
;

/// Container for Application Server(s)
class Container
:   public I_Container
{
    /// @name Types
    /// @{
public:
    typedef Scripting::I_ScriptingManager::pScriptEngine_type   pScriptEngine_type;

    typedef boost::program_options::variables_map           variables_map_type;

    typedef Plugins::I_ConfigurationElement::const_ptr_type pConfig_type;

    typedef Zen::Event::I_EventManager::pEventService_type  pEventService_type;
    /// @}

    /// @name I_Container implementation
    /// @{
public:
    /// Initialize the server
    virtual bool init(int _argc, const char* _argv[]);

    /// Run the server
    virtual int run();

    /// Stop the container.
    /// @note The container will need to be reinitialized prior to use after this is called.
    virtual void stop();

    virtual I_ApplicationServer& getApplicationServer();
    /// @}

    /// @name Container implementation
    /// @{
private:
    bool initializeScriptEngine();
    bool runScriptInit();
    /// @}

    /// @name 'Structors
    /// @{
public:
             Container();
    virtual ~Container();
    /// @}

    /// @name Member Variables
    /// @{
private:
    /// Variables from the command line
    variables_map_type          m_variables;
    
    /// Application configuration path
    std::string                 m_configPath;

    /// Output log filename
    std::string                 m_logFile;

    /// Script language plugin to load
    std::string                 m_scriptLanguage;

    /// Default script file to load
    std::string                 m_defaultScript;

    /// Run interactively after loading the script?
    bool                        m_bRunInteractive;

    /// Default script engine.
    pScriptEngine_type          m_pScriptEngine;

    /// Main event service.
    pEventService_type          m_pEventService;

    /// Primary application server
    I_ApplicationServer*        m_pAppServer;

    /// @}

};  // class Container

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Enterprise
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_CONTAINER_HPP_INCLUDED
