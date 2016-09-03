//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
// Copyright (C) 2008 - 2010 Matthew Alan Gray
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_I_FULLY_QUALIFIED_RESOURCE_LOCATION_HPP_INCLUDED
#define ZEN_ENTERPRISE_I_FULLY_QUALIFIED_RESOURCE_LOCATION_HPP_INCLUDED

#include "Configuration.hpp"

#include <Zen/Core/Memory/managed_ptr.hpp>

#include <boost/noncopyable.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
    namespace Networking {
        class I_Endpoint;
    }   // namespace Networking
namespace Enterprise {
namespace AppServer {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class I_ResourceLocation;

/// @brief Fully Qualified Resource Location
///
///
class ENTERPRISE_DLL_LINK I_FullyQualifiedResourceLocation
:   boost::noncopyable
{
    /// @name Types
    /// @{
public:
    typedef Zen::Memory::managed_ptr<Networking::I_Endpoint>    pEndpoint_type;
    typedef Zen::Memory::managed_ptr<I_ResourceLocation>        pResourceLocation_type;
    /// @}

    /// @name I_FullyQualifiedResourceLocation interface.
    /// @{
public:
    /// Get the endpoint.
    virtual pEndpoint_type getEndpoint() const = 0;

    /// Get the relative resource location.
    virtual pResourceLocation_type getRelativeLocation() const = 0;

    /// Get the location as a URL string.
    virtual const std::string toString() const = 0;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_FullyQualifiedResourceLocation();
    virtual ~I_FullyQualifiedResourceLocation();
    /// @}

};  // interface I_FullyQualifiedResourceLocation

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace AppServer
}   // namespace Enterprise
namespace Memory {
    // I_FullyQualifiedResourceLocation is managed by factory
    template<>
    struct is_managed_by_factory<Zen::Enterprise::AppServer::I_FullyQualifiedResourceLocation> 
    :   public boost::true_type{};
}   // namespace Memory
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_I_FULLY_QUALIFIED_RESOURCE_LOCATION_HPP_INCLUDED
