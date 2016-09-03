//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_I_NETWORK_CONNECTION_LISTENER_HPP_INCLUDED
#define ZEN_ENTERPRISE_I_NETWORK_CONNECTION_LISTENER_HPP_INCLUDED

#include "Configuration.hpp"

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Networking {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

/// A listener interface for network connections.
/// In order to receive network connect / disconnect notifications an application
/// developer should implement this interface and register using 
/// I_NetworkService::registerConnectionListener()
///
/// Some network services don't directly dispatch these event notifications,
/// specifically connectionless network services.  In this case it is the
/// network protocol's responsibility for dispatching the event.
///
class NETWORKING_DLL_LINK I_NetworkConnectionListener
{
    /// @name I_NetworkConnectionListener interface
    /// @{
public:
    /// Called when a connection has been established.
    virtual void onNewConnection(I_NetworkConnection& _connection) = 0;

    /// Called when a connection has been closed.
    virtual void onClosedConnection(I_NetworkConnection& _connection) = 0;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_NetworkConnectionListener();
    virtual ~I_NetworkConnectionListener();
    /// @}

};  // interface I_NetworkConnectionListener

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Networking
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_I_NETWORK_CONNECTION_LISTENER_HPP_INCLUDED
