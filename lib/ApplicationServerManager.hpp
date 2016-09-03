//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_APPLICATION_SERVER_MANAGER_HPP_INCLUDED
#define ZEN_ENTERPRISE_APPLICATION_SERVER_MANAGER_HPP_INCLUDED

#include <Zen/Core/Memory/managed_weak_ptr.hpp>

#include <Zen/Core/Threading/I_Mutex.hpp>

#include <map>
#include <string>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class I_ResourceLocation;

class ApplicationServerManager
:   public I_ApplicationServerManager
{
    /// @name Types
    /// @{
public:
    typedef Memory::managed_ptr<I_ProtocolService>          pProtocolService_type;
    typedef Memory::managed_ptr<I_ApplicationService>       pApplicationService_type;
    typedef Memory::managed_ptr<I_ResourceLocation>         pResourceLocation_type;
    typedef Memory::managed_weak_ptr<I_ResourceLocation>    wpResourceLocation_type;
    /// @}

    /// @name I_ApplicationServerManager implementation.
    /// @{
public:
    virtual pProtocolService_type createProtocolService(I_ApplicationServer& _server, const std::string& _type);
    virtual pApplicationService_type createApplicationService(I_ApplicationServer& _server, const std::string& _type);
    virtual pResourceLocation_type createLocation(const std::string& _location);
    /// @}

    /// @name ApplicationServerManager implementation
    /// @{
private:
    void destroyLocation(wpResourceLocation_type _location);
    /// @}

    /// @name 'Structors
    /// @{
protected:
    friend class I_ApplicationServerManager;
             ApplicationServerManager();
    virtual ~ApplicationServerManager();
    /// @}

    /// @name Member Variables
    /// @{
private:
    typedef std::map<std::string, wpResourceLocation_type>   ResourceLocations_type;

    /// Guard for m_resourceLocations
    Threading::I_Mutex*                                 m_pResourceLocationGuard;
    /// Map of resource locations from the string representation to the actual object
    ResourceLocations_type                              m_resourceLocations;
    /// @}

};  // interface ApplicationServerManager

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Enterprise
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_APPLICATION_SERVER_MANAGER_HPP_INCLUDED
