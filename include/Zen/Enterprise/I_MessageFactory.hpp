//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_I_MESSAGE_FACTORY_HPP_INCLUDED
#define ZEN_ENTERPRISE_I_MESSAGE_FACTORY_HPP_INCLUDED

#include "Configuration.hpp"

// #include <Zen/Core/Memory/managed_ptr.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
    namespace Networking {
        class I_Endpoint;
    }   // namespace Networking
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class I_Message;
class I_MessageHeader;

class ENTERPRISE_DLL_LINK I_MessageFactory
:   boost::noncopyable
{
    /// @name Types
    /// @{
public:
    typedef Zen::Memory::managed_ptr<I_Message>                              pMessage_type;
    typedef Zen::Memory::managed_weak_ptr<I_Message>                         wpMessage_type;
    typedef Zen::Memory::managed_ptr<Networking::I_Endpoint>                 pEndpoint_type;
    typedef Zen::Memory::managed_ptr<I_MessageHeader>                        pMessageHeader_type;
    /// @}

    /// @name I_MessageFactory interface
    /// @{
public:
    /// Create a message.
    virtual pMessage_type create(pMessageHeader_type _pMessageHeader, pEndpoint_type _pSourceEndpoint, pEndpoint_type _pDestinationEndpoint) = 0;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_MessageFactory();
    virtual ~I_MessageFactory();
    /// @}

};  // interface I_MessageFactory

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Enterprise
namespace Memory {
    // I_Message is managed by factory
    template<>
    struct is_managed_by_factory<Zen::Enterprise::AppServer::I_MessageFactory> : public boost::true_type{};
}   // namespace Memory
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_I_MESSAGE_FACTORY_HPP_INCLUDED
