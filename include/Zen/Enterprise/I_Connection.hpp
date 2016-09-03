//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
// Copyright (C) 2008 - 2010 Matthew Alan Gray
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_I_CONNECTION_HPP_INCLUDED
#define ZEN_ENTERPRISE_I_CONNECTION_HPP_INCLUDED

#include "Configuration.hpp"

// #include <Zen/Core/Memory/managed_ptr.hpp>


//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

// class I_FullyQualifiedResourceLocation;

/// @brief Connection
/// 
///
class ENTERPRISE_DLL_LINK I_Connection
{
    /// @name Types
    /// @{
public:
    // typedef Zen::Memory::managed_ptr<I_FullyQualifiedResourceLocation>  pFQRL_type;
    /// @}

    /// @name I_Connection interface.
    /// @{
public:
    /// Get the connection id.
    // virtual boost::uint64_t getConnectionId() const = 0;

    /// Get the FQRL.
    // virtual pFQRL_type getFQRL() const = 0;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_Connection();
    virtual ~I_Connection();
    /// @}

};  // interface I_Connection

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Enterprise
// namespace Memory {
//     // I_Connection is managed by factory
//     template<>
//     struct is_managed_by_factory<Zen::Enterprise::AppServer::I_Connection> 
//     :   public boost::true_type{};
// }   // namespace Memory
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_I_CONNECTION_HPP_INCLUDED
