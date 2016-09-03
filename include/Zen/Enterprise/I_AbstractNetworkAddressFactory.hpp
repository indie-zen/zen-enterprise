//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_I_ABSTRACT_NETWORK_ADDRESS_FACTORY_HPP_INCLUDED
#define ZEN_ENTERPRISE_I_ABSTRACT_NETWORK_ADDRESS_FACTORY_HPP_INCLUDED

#include "Configuration.hpp"

#include <Zen/Core/Plugins/I_ClassFactory.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Networking {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class I_NetworkAddressFactory;

/// Abstract Network Address Factory
class NETWORKING_DLL_LINK I_AbstractNetworkAddressFactory
{
	/// @name Types
	/// @{
public:
	/// @}

    /// @name Factory methods
    /// @{
public:
    static I_AbstractNetworkAddressFactory& getSingleton();
    /// @}

    /// @name I_AbstractNetworkAddressFactory interface
    /// @{
public:
    /// Register a Network Address Factory
    virtual void registerFactory(I_NetworkAddressFactory& _networkAddressFactory) = 0;

    /// Unregister a Network Address Factory
    virtual void unregisterFactory(I_NetworkAddressFactory& _networkAddressFactory) = 0;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_AbstractNetworkAddressFactory();
    virtual ~I_AbstractNetworkAddressFactory();
    /// @}

};  // interface I_AbstractNetworkAddressFactory

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Networking
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_I_ABSTRACT_NETWORK_ADDRESS_FACTORY_HPP_INCLUDED
