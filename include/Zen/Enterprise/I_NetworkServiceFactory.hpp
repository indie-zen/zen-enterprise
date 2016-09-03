//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_I_NETWORK_SERVICE_FACTORY_HPP_INCLUDED
#define ZEN_ENTERPRISE_I_NETWORK_SERVICE_FACTORY_HPP_INCLUDED

#include "Configuration.hpp"

#include <Zen/Core/Plugins/I_ClassFactory.hpp>

#include <boost/shared_ptr.hpp>

#include <string>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Networking {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class I_NetworkService;

/// Base Network Service Factory interface
class NETWORKING_DLL_LINK I_NetworkServiceFactory
:   public  Plugins::I_ClassFactory
{
    /// @name Types
    /// @{
public:
    typedef I_NetworkServiceFactory*    service_factory_ptr_type;
    typedef I_NetworkService*           service_ptr_type;
    /// @}

    /// @name I_NetworkService interface
    /// @{
public:
    virtual service_ptr_type create(const std::string& _name) = 0;
    virtual void destroy(service_ptr_type _pService) = 0;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_NetworkServiceFactory();
    virtual ~I_NetworkServiceFactory();
    /// @}

};  // interface I_NetworkServiceFactory

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Networking
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_I_NETWORK_SERVICE_FACTORY_HPP_INCLUDED
