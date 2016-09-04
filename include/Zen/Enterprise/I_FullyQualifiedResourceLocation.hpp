//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
// Copyright (C) 2008 - 2010 Matthew Alan Gray
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_I_FULLY_QUALIFIED_RESOURCE_LOCATION_HPP_INCLUDED
#define ZEN_ENTERPRISE_I_FULLY_QUALIFIED_RESOURCE_LOCATION_HPP_INCLUDED

#include "Configuration.hpp"

#include <memory>

#include <boost/noncopyable.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class I_Endpoint;
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
    typedef std::shared_ptr<I_Endpoint>    pEndpoint_type;
    typedef std::shared_ptr<I_ResourceLocation>        pResourceLocation_type;
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
}   // namespace Enterprise
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_I_FULLY_QUALIFIED_RESOURCE_LOCATION_HPP_INCLUDED
