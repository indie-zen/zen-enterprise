//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_I_PROTOCOL_SERVICE_HPP_INCLUDED
#define ZEN_ENTERPRISE_I_PROTOCOL_SERVICE_HPP_INCLUDED

#include "Configuration.hpp"

#include <Zen/Core/Memory/managed_ptr.hpp>

#include <Zen/Core/Plugins/I_StartupShutdownParticipant.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
    namespace Networking {
        class I_Endpoint;
    }   // namespace Networking
    namespace Event {
        class I_Event;
    }
namespace Enterprise {
namespace AppServer {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class I_ApplicationServer;
class I_Message;
class I_MessageRegistry;
class I_MessageHeader;

class ENTERPRISE_DLL_LINK I_ProtocolService
:   public Plugins::I_StartupShutdownParticipant
{
    /// @name Types
    /// @{
public:
    typedef Memory::managed_ptr<I_Message>                  pMessage_type;
    typedef Memory::managed_ptr<I_MessageHeader>            pMessageHeader_type;
    typedef Memory::managed_ptr<Networking::I_Endpoint>     pEndpoint_type;
    typedef Memory::managed_ptr<I_MessageRegistry>          pMessageRegistry_type;
    /// @}

    /// @name I_ProtocolService interface.
    /// @{
public:
    /// Get the application server which is hosting this protocol service.
    /// This must be the same reference that was passed to the factory create
    /// method.
    /// @see I_ProtocolServiceFactory
    virtual I_ApplicationServer& getApplicationServer() = 0;

    /// Get the endpoint for this protocol adapter.
    virtual pEndpoint_type getEndpoint() = 0;

    /// Resolve the endpoint for an address and port specified by strings.
    /// If the resolver and the operating system supports it, _port can also 
    /// contain service names such as "http".
    virtual pEndpoint_type resolveEndpoint(const std::string& _address, const std::string& _port) = 0;

    /// Send a message to an endpoint, potentially establishing the connection first.
    virtual void sendTo(pMessage_type _pMessage, pEndpoint_type _pEndpoint) = 0;

    /// Disconnect from an endpoint.
    virtual void disconnect(pEndpoint_type _pEndpoint) = 0;

    /// Get the "Connected" event.
    /// This event is fired when a connection is established.
    /// The payload for the event is the pEndpoint_type of the
    /// destination endpoint that was disconnected.
    virtual Event::I_Event& getConnectedEvent() = 0;

    /// Get the "Disconnected" event.
    /// This event is fired when a connection is established.
    /// The payload for the event is the pEndpoint_type of the
    /// destination endpoint that was disconnected.
    virtual Event::I_Event& getDisconnectedEvent() = 0;
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
             I_ProtocolService();
    virtual ~I_ProtocolService();
    /// @}

};  // interface I_ProtocolService

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace AppServer
}   // namespace Enterprise
namespace Memory 
{
    /// I_ProtocolService is managed by a factory
    template<>
    struct is_managed_by_factory<Enterprise::AppServer::I_ProtocolService> : public boost::true_type{};
}   // namespace Memory
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_I_PROTOCOL_SERVICE_HPP_INCLUDED
