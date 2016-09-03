//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_NETWORKING_ABSTRACT_NETWORK_ADDRESS_FACTORY_HPP_INCLUDED
#define ZEN_NETWORKING_ABSTRACT_NETWORK_ADDRESS_FACTORY_HPP_INCLUDED

#include <Zen/Enterprise/I_AbstractNetworkAddressFactory.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

/// Abstract Network Address Factory implementation
class AbstractNetworkAddressFactory
:   public I_AbstractNetworkAddressFactory
{
	/// @name Types
	/// @{
public:
	/// @}

    /// @name I_AbstractNetworkAddressFactory implementation
    /// @{
public:
	virtual void registerFactory(Plugins::I_ClassFactory& _classFactory);

    virtual void registerFactory(I_NetworkAddressFactory& _networkAddressFactory);
    virtual void unregisterFactory(I_NetworkAddressFactory& _networkAddressFactory);
    /// @}

    /// @name 'Structors
    /// @{
public:
             AbstractNetworkAddressFactory();
    virtual ~AbstractNetworkAddressFactory();
    /// @}

};  // class AbstractNetworkAddressFactory

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Networking
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_NETWORKING_ABSTRACT_NETWORK_ADDRESS_FACTORY_HPP_INCLUDED
