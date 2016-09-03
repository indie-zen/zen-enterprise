//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_I_NETWORK_ADDRESS_FACTORY_HPP_INCLUDED
#define ZEN_ENTERPRISE_I_NETWORK_ADDRESS_FACTORY_HPP_INCLUDED

#include "Configuration.hpp"

#include <Zen/Core/Plugins/I_ClassFactory.hpp>
#include <Zen/Core/Plugins/I_ConfigurationElement.hpp>

#include <string>
#include <list>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Networking {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class I_NetworkAddress;

/// Base Network Address Factory
class NETWORKING_DLL_LINK I_NetworkAddressFactory
:   public  Plugins::I_ClassFactory
{
    /// @name I_NetworkAddressFactory interface
    /// @{
public:
    /// Returns the address type
    virtual const std::list<std::string> getAddressTypes() const = 0;

	virtual I_NetworkAddress* create(const Plugins::I_ConfigurationElement& _configuration) = 0;

    virtual void destroy(I_NetworkAddress* _pAddress) = 0;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_NetworkAddressFactory();
    virtual ~I_NetworkAddressFactory();
    /// @}

};  // interface I_NetworkAddressFactory

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Networking
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_I_NETWORK_ADDRESS_FACTORY_HPP_INCLUDED
