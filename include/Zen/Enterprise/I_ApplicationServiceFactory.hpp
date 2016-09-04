//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_I_APPLICATION_SERVICE_FACTORY_HPP_INCLUDED
#define ZEN_ENTERPRISE_I_APPLICATION_SERVICE_FACTORY_HPP_INCLUDED

#include "Configuration.hpp"

#include <memory>

#include <Zen/Core/Plugins/I_ClassFactory.hpp>

#include <string>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class I_ApplicationServer;
class I_ApplicationService;

class ENTERPRISE_DLL_LINK I_ApplicationServiceFactory
:   public Plugins::I_ClassFactory
{
    /// @name Types
    /// @{
public:
    typedef std::shared_ptr<I_ApplicationService>       pApplicationService_type;
    /// @}

    /// @name I_ApplicationServiceFactory interface.
    /// @{
public:
    /// @param _server - Application server which will be containing the newly created application service.
    virtual pApplicationService_type create(I_ApplicationServer& _server, const std::string& _name) = 0;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_ApplicationServiceFactory();
    virtual ~I_ApplicationServiceFactory();
    /// @}

};  // interface I_ApplicationServiceFactory

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Enterprise
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_I_APPLICATION_SERVICE_FACTORY_HPP_INCLUDED
