//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
// Copyright (C) 2008 - 2009 Matthew Alan Gray
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_NETWORKING_I_ADDRESS_HPP_INCLUDED
#define ZEN_ENTERPRISE_NETWORKING_I_ADDRESS_HPP_INCLUDED

#include "Configuration.hpp"

#include <Zen/Core/Memory/managed_ptr.hpp>
#include <Zen/Core/Memory/managed_weak_ptr.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Networking {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class NETWORKING_DLL_LINK I_Address
{
    /// @name Types
    /// @{
public:
    typedef Zen::Memory::managed_ptr<I_Address>         pAddress_type;
    typedef Zen::Memory::managed_weak_ptr<I_Address>    wpAddress_type;
    /// @}

    /// @name I_Address interface
    /// @{
public:
    virtual std::string toString() const = 0;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_Address();
    virtual ~I_Address();
    /// @}

};  // interface I_Address

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Networking
namespace Memory 
{
    /// I_Endpoint is managed by a factory
    template<>
    struct is_managed_by_factory<Networking::I_Address> : public boost::true_type{};
}   // namespace Memory
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif  // ZEN_ENTERPRISE_NETWORKING_I_ADDRESS_HPP_INCLUDED
