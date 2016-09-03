//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_I_ABSTRACT_NETWORK_SERVICE_FACTORY_HPP_INCLUDED
#define ZEN_ENTERPRISE_I_ABSTRACT_NETWORK_SERVICE_FACTORY_HPP_INCLUDED

#include "Configuration.hpp"

#include <Zen/Core/Plugins/I_AbstractClassFactory.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Networking {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

/// Abstract Network Address Factory
class NETWORKING_DLL_LINK I_AbstractNetworkServiceFactory
:   public Plugins::I_AbstractClassFactory
{
	/// @name Types
	/// @{
public:
	/// @}

    /// @name Factory methods
    /// @{
public:
    static I_AbstractNetworkServiceFactory& getSingleton();
    /// @}

    /// @name I_AbstractNetworkAddressFactory interface
    /// @{
public:
    virtual void registerFactory(I_NetworkAddressFactory& _networkAddressFactory) = 0;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_AbstractNetworkServiceFactory();
    virtual ~I_AbstractNetworkServiceFactory();
    /// @}

};  // interface I_AbstractNetworkServiceFactory

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Networking
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_I_ABSTRACT_NETWORK_SERVICE_FACTORY_HPP_INCLUDED
