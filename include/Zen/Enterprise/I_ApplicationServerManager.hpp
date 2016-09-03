//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_I_APPLICATION_SERVER_MANAGER_HPP_INCLUDED
#define ZEN_ENTERPRISE_I_APPLICATION_SERVER_MANAGER_HPP_INCLUDED

#include "Configuration.hpp"

#include <Zen/Core/Memory/managed_ptr.hpp>

#include <boost/noncopyable.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
namespace AppServer {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class I_ProtocolService;
class I_ApplicationService;
class I_ResourceLocation;
class I_ApplicationServer;

class ENTERPRISE_DLL_LINK I_ApplicationServerManager
:   boost::noncopyable
{
    /// @name Types
    /// @{
public:
    typedef Memory::managed_ptr<I_ProtocolService>          pProtocolService_type;
    typedef Memory::managed_ptr<I_ApplicationService>       pApplicationService_type;
    typedef Memory::managed_ptr<I_ResourceLocation>         pResourceLocation_type;
    /// @}

    /// @name I_ApplicationServerManager interface.
    /// @{
public:
    /// Create a protocol service of the specified type.
    virtual pProtocolService_type createProtocolService(I_ApplicationServer& _server, const std::string& _type) = 0;

    /// Create an Application Service
    virtual pApplicationService_type createApplicationService(I_ApplicationServer& _server, const std::string& _type) = 0;

    /// Create a resource location
    virtual pResourceLocation_type createLocation(const std::string& _location) = 0;
    /// @}

    /// @name Static Instance
    /// @{
public:
    /// Get the singleton
    /// @return Reference to the singleton instance.
    static I_ApplicationServerManager& getSingleton();
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_ApplicationServerManager();
    virtual ~I_ApplicationServerManager();
    /// @}

};  // interface I_ApplicationServerManager

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace AppServer
}   // namespace Enterprise
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_I_APPLICATION_SERVER_MANAGER_HPP_INCLUDED
