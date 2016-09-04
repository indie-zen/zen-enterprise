//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_I_NUMERIC_TYPE_MESSAGE_REGISTRY_HPP_INCLUDED
#define ZEN_ENTERPRISE_I_NUMERIC_TYPE_MESSAGE_REGISTRY_HPP_INCLUDED

#include "Configuration.hpp"

#include <memory>
#include <memory>

#include <Zen/Enterprise/I_MessageRegistry.hpp>
#include <Zen/Enterprise/I_MessageType.hpp>

#include <boost/cstdint.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

/// Message Registry that uses I_MessageType with a numeric
/// uint32_t implementation.
class ENTERPRISE_DLL_LINK I_NumericTypeMessageRegistry
:   public I_MessageRegistry
{
    /// @name Types
    /// @{
public:
    typedef std::shared_ptr<I_MessageType>         pMessageType_type;
    typedef Zen::Memory::managed_weak_ptr<I_MessageType>    wpMessageType_type;
    typedef std::shared_ptr<I_MessageRegistry>     pMessageRegistry_type;
    /// @}

    /// @name I_NumericTypeMessageRegistry interface.
    /// @{
public:
    virtual pMessageType_type getMessageType(boost::uint64_t _type) = 0;
    /// @}

    /// @name Inner types 
    /// @{
public:
    class I_NumericType
    :   public I_MessageType
    {
    public:
        virtual boost::uint64_t getType() const = 0;
    };  // class NumericType

    /// @}
    /// @name 'Structors
    /// @{
protected:
             I_NumericTypeMessageRegistry();
    virtual ~I_NumericTypeMessageRegistry();
    /// @}

};  // interface I_NumericTypeMessageRegistry

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Enterprise
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_I_NUMERIC_TYPE_MESSAGE_REGISTRY_HPP_INCLUDED
