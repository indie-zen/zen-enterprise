//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
// Copyright (C) 2008 - 2009 Matthew Alan Gray
// Copyright (C)        2009 Joshua Cassity
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_I_APPLICATION_SERVER_HPP_INCLUDED
#define ZEN_ENTERPRISE_I_APPLICATION_SERVER_HPP_INCLUDED

#include "Configuration.hpp"

#include <Zen/Core/Scripting/I_ScriptEngine.hpp>
#include <Zen/Core/Event/I_EventManager.hpp>

#include <Zen/Enterprise/I_Endpoint.hpp>

#include <boost/noncopyable.hpp>

#include <map>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
    namespace Database {
        class I_DatabaseConnection;
    }   // namespace Database
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class I_ProtocolService;
class I_ApplicationService;
class I_ResourceLocation;
class I_Message;
class I_Request;
class I_Response;
class I_ResponseHandler;
class I_SessionEvent;
class I_MessageRegistry;

/// Base Application Server.
class ENTERPRISE_DLL_LINK I_ApplicationServer
:   boost::noncopyable
{
    /// @name Forward declarations
    /// @{
public:
    struct I_ResourceLocationVisitor;
    /// @}

    /// @name Types
    /// @{
public:
    typedef std::shared_ptr<I_ProtocolService>          pProtocolService_type;
    typedef std::shared_ptr<I_ApplicationService>       pApplicationService_type;
    typedef std::shared_ptr<I_Message>                  pMessage_type;
    typedef std::weak_ptr<I_Message>                    wpMessage_type;
    typedef std::shared_ptr<I_Request>                  pRequest_type;
    typedef std::shared_ptr<I_Response>                 pResponse_type;
    typedef std::shared_ptr<I_ResponseHandler>          pResponseHandler_type;
    typedef std::shared_ptr<I_SessionEvent>             pSessionEvent_type;
    typedef std::shared_ptr<I_ResourceLocation>         pResourceLocation_type;
    typedef std::shared_ptr<I_MessageRegistry>          pMessageRegistry_type;

    typedef std::shared_ptr<I_Endpoint>     pEndpoint_type;

    typedef std::shared_ptr<Database::I_DatabaseConnection> pDatabaseConnection_type;

    typedef Zen::Plugins::I_ConfigurationElement::const_ptr_type    pConfig_type;

    typedef std::shared_ptr<Scripting::I_ScriptEngine>  pScriptEngine_type;
    typedef std::shared_ptr<Scripting::I_ScriptModule>  pScriptModule_type;

    typedef Event::I_EventManager::pEventService_type   pEventService_type;
    typedef std::map<std::string, std::string>          config_type;
    /// @}

    /// @name I_ApplicationServer interface.
    /// @{
public:
    /// Start the application server.
    /// @return the condition variable that indicates when the application server
    ///     has fully started.
    virtual Zen::Threading::I_Condition* start() = 0;

    /// @brief Stop the application server.
    ///
    /// This method will return when the application server is fully stopped and destroyed.
    /// Do not reference this object after stop() is called.
    virtual void stop() = 0;

    /// Register the default script engine for all application services.
    /// Every application service that has been created or is created in the future
    /// will use this script engine.
    /// @param _pEngine NULL to set the default engine to none, but doing so will
    ///             not unregister the script engine to services that have already
    ///             been created.  It will only prevent subsequent services from
    ///             using this script engine.
    virtual void registerDefaultScriptEngine(pScriptEngine_type _pEngine) = 0;

    /// Get the default script engine.
    virtual pScriptEngine_type getDefaultScriptEngine() = 0;

    /// Get the event service that the application server uses for publishing events.
    virtual pEventService_type getEventService() = 0;

    /// Install multiple protocol services using the provided configuration.
    /// The provided configuration should have zero or more <protocol/> entries which
    /// are used to invoke installProtocol using a protocol service specified by the "type" attribute.
    /// @param _pProtocolsConfig - The <protocols/> configuration element that contains zero or more
    ///     <protocol/> elements.
    /// @see http://www.indiezen.org/wiki/wiki/zoss/ZenServer/Configuration
    virtual void installProtocols(pConfig_type _pProtocolsConfig) = 0;

    /// Install a Protocol Service into this Application Server
    /// @param _protocolName the name of the protocol.  This name must be unique to this Application Server.
    virtual void installProtocol(pProtocolService_type _pProtocolService, const std::string& _protocolName) = 0;

    /// Get a Protocol Service that's already been installed by the name.
    /// @param _protocolName the name of the protocol used when installing the protocol service in installProtocol().
    /// @see I_ApplicationServer::installProtocol()
    virtual pProtocolService_type getProtocol(const std::string& _protocolName) = 0;

    /// Install multiple application services using the provided configuration.
    /// The provided configuration should have zero or more <application/> entries which
    /// are used to invoke installApplication at the specified "location" attribute using an application
    /// service specified by the "type" attribute.
    /// @param _pAppServicesConfig - The <applications/> configuration element that contains zero or more
    ///     <application/> elements.
    /// @see http://www.indiezen.org/wiki/wiki/zoss/ZenServer/Configuration
    virtual void installApplications(pConfig_type _pAppServicesConfig) = 0;

    /// Install an Application into this Application Server.
    /// @param _pApplicationService - Application service to install
    /// @param _rootLocation - Root resource location at which this application should be installed.
    virtual void installApplication(pApplicationService_type _pApplicationService, pResourceLocation_type _pRootLocation) = 0;

    /// Configure the application.
    virtual void configureApplication(pApplicationService_type _pApplicationService, pConfig_type _pConfig) = 0;

    /// Get the application.
    virtual pApplicationService_type getApplication(pResourceLocation_type _pServiceLocation) const = 0;

    /// Get the application by name.
    virtual pApplicationService_type getApplication(const std::string& _serviceLocation) const = 0;

    /// Visit the resource locations.
    virtual void getResourceLocations(I_ResourceLocationVisitor& _visitor) const = 0;

    /// Get the message registry.
    virtual pMessageRegistry_type getMessageRegistry() = 0;

    /// Handle a message.
    /// Messages are one-way notifications and are not expected to return a result.
    virtual void handleMessage(pMessage_type _pMessage) = 0;

    /// Handle a request asynchronously.
    /// A request is a message that requires a response, but the response can be handled
    /// asynchronously.
    /// @param _pResponseHandler dispatch object that will handle the reponse to this request.
    virtual void handleRequest(pRequest_type _pRequest, pResponseHandler_type _pResponseHandler) = 0;

    /// Handle a session event.
    /// A session event is an event such as a succesful authentication, (or unsuccesful
    /// for that matter), or a login or logout request event, etc.
    /// @see I_SessionEvent
    virtual void handleSessionEvent(pSessionEvent_type _pSessionEvent) = 0;

    /// Install database connections.
    /// Install one or more database connections using the provided configuration.
    /// The provided configuration should have zero or more <database/> entries which
    /// are used to invoke createDatabaseEntry().
    /// service specified by the "type" attribute.
    /// @param _pDatabasesConfig - The <databases/> configuration element that contains zero or more
    ///     <database/> elements.
    /// @see http://www.indiezen.org/wiki/wiki/zoss/ZenServer/Configuration
    virtual void installDatabaseConnections(pConfig_type _pDatabasesConfig) = 0;

    /// Create a database connection entry.
    /// Database connections are pooled by the application server.  This method creates the 
    /// connection information entry by a connection name.  When you call getDatabaseConnection()
    /// and pass the same connection name, it will return the appropriate connection.
    /// @todo Refactor to use config_type instead of pConfig_type.
    virtual void createDatabaseEntry(const std::string& _connectionName, const std::string& _databaseType, config_type& _config) = 0;

    /// Get the database connection for the current thread.
    virtual pDatabaseConnection_type getDatabaseConnection(const std::string& _connectionName) = 0;
    /// @}

    /// @name Inner classes
    /// @{
public:
    struct ENTERPRISE_DLL_LINK I_ResourceLocationVisitor
    {
        virtual void begin() = 0;
        virtual void visit(pResourceLocation_type _pResourceLocation, pApplicationService_type _pService) = 0;
        virtual void end() = 0;
    };  // struct I_ResourceLocationVisitor
    /// @}

    /// @name Static Instance
    /// @{
public:
    /// Get an application server by name.
    ///
    /// The lifetime of an application server is from the time that getInstance()
    /// returns to the time that I_ApplicationServer::stop() is called and the 
    /// application server is fully stopped.
    static I_ApplicationServer& getInstance(const std::string& _instanceName);
    /// @}

    /// @name Events
    /// @{
public:
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_ApplicationServer() = default;
public:
    virtual ~I_ApplicationServer() = default;
    /// @}

};  // interface I_ApplicationServer

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Enterprise
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_I_APPLICATION_SERVER_HPP_INCLUDED
