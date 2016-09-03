//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_RESOURCE_LOCATION_HPP_INCLUDED
#define ZEN_ENTERPRISE_RESOURCE_LOCATION_HPP_INCLUDED

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
;

class ResourceLocation
:   public I_ResourceLocation
{
    /// @name Types
    /// @{
public:
    typedef Memory::managed_ptr<I_ApplicationService>       pApplicationService_type;
    /// @}

    /// @name I_ResourceLocation implementation.
    /// @{
public:
    virtual const std::string& toString() const;
    virtual bool operator==(const I_ResourceLocation& _otherLocation) const;
    virtual bool operator!=(const I_ResourceLocation& _otherLocation) const;
    /// @}

    /// @name ResourceLocation implementation
    /// @{
public:
    /// Set the application service that handles this resource location.
    /// There can be one and only one service that handles any given location
    /// (not including filters).
    void setApplicationService(pApplicationService_type _pApplicationService);

    pApplicationService_type getApplicationService() const;
    /// @}

    /// @name Events
    /// @{
public:
    /// @}

    /// @name 'Structors
    /// @{
protected:
    friend class ApplicationServerManager;
    explicit ResourceLocation(const std::string& _fromString);
    virtual ~ResourceLocation();
    /// @}

    /// @name Member Variables
    /// @{
private:
    /// String value of this resource location
    std::string                 m_stringValue;
    pApplicationService_type    m_pApplicationService;
    /// @}

};  // class ResourceLocation

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Enterprise
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_RESOURCE_LOCATION_HPP_INCLUDED
