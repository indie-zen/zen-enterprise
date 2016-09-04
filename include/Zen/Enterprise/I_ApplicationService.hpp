//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_I_APPLICATION_SERVICE_HPP_INCLUDED
#define ZEN_ENTERPRISE_I_APPLICATION_SERVICE_HPP_INCLUDED

#include "Configuration.hpp"

#include <memory>

#include <Zen/Core/Plugins/I_StartupShutdownParticipant.hpp>

#include <Zen/Enterprise/I_RequestHandler.hpp>
#include <Zen/Enterprise/I_Endpoint.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class I_ApplicationServer;
class I_Message;
class I_MessageType;
class I_ResourceLocation;

class ENTERPRISE_DLL_LINK I_ApplicationService
:   public I_RequestHandler
,   public Plugins::I_StartupShutdownParticipant
{
    /// @name Types
    /// @{
public:
    typedef std::shared_ptr<I_Message>                      pMessage_type;
    typedef std::shared_ptr<I_MessageType>             pMessageType_type;
    typedef std::shared_ptr<I_Endpoint>    pEndpoint_type;
    typedef std::shared_ptr<I_ResourceLocation>        pResourceLocation_type;
    /// @}

    /// @name I_ApplicationService interface.
    /// @{
public:
    /// Get the application server which is hosting this application service.
    /// This must be the same reference that was passed to the factory create
    /// method.
    /// @see I_ApplicationServiceFactory
    virtual I_ApplicationServer& getApplicationServer() = 0;

    /// Get the application service name.
    virtual const std::string& getServiceName() const = 0;

    /// Get the application service endpoint.
    virtual pEndpoint_type getServiceEndpoint() = 0;

    /// Get the application service resource location.
    virtual pResourceLocation_type getServiceLocation() = 0;

    /// Handle a message
    /// Messages are one-way notifications and are not expected to return a result.
    virtual void handleMessage(pMessage_type _pMessage) = 0;
    /// @}

    /// @name Static methods
    /// @{
public:
    static const std::string& getNamespace();
    static const std::string& getExtensionPointName();
    /// @}

    /// @name Events
    /// @{
public:
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_ApplicationService();
    virtual ~I_ApplicationService();
    /// @}

};  // interface I_ApplicationService

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Enterprise
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_I_APPLICATION_SERVICE_HPP_INCLUDED
