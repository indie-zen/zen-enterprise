//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
// Copyright (C) 2008 - 2010 Matthew Alan Gray
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_FULLY_QUALIFIED_RESOURCE_LOCATION_HPP_INCLUDED
#define ZEN_ENTERPRISE_FULLY_QUALIFIED_RESOURCE_LOCATION_HPP_INCLUDED

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class FullyQualifiedResourceLocation
:   public I_FullyQualifiedResourceLocation
{
    /// @name Types
    /// @{
public:
    typedef Zen::Memory::managed_ptr<I_ApplicationService>  pApplicationService_type;
    /// @}

    /// @name I_FullyQualifiedResourceLocation implementation.
    /// @{
public:
    virtual pEndpoint_type getEndpoint() const;
    virtual pResourceLocation_type getRelativeLocation() const;
    virtual const std::string toString() const;
    /// @}

    /// @name FullyQualifiedResourceLocation implementation
    /// @{
public:
    /// @}

    /// @name Events
    /// @{
public:
    /// @}

    /// @name 'Structors
    /// @{
protected:
    friend class ApplicationServerManager;
    explicit FullyQualifiedResourceLocation(const std::string& _fromURLString);
             FullyQualifiedResourceLocation(pEndpoint_type _pEndpoint, const std::string& _fromLocationString);
             FullyQualifiedResourceLocation(pEndpoint_type _pEndpoint, pResourceLocation_type _pLocation);
    virtual ~FullyQualifiedResourceLocation();
    /// @}

    /// @name Member Variables
    /// @{
private:
    pEndpoint_type          m_pEndpoint;
    pResourceLocation_type  m_pLocation;
    /// @}

};  // class FullyQualifiedResourceLocation

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Enterprise
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_FULLY_QUALIFIED_RESOURCE_LOCATION_HPP_INCLUDED
