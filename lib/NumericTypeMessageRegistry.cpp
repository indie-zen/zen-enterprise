//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#include "NumericTypeMessageRegistry.hpp"

#include <Zen/Core/Memory/managed_weak_ptr.hpp>

#include <Zen/Core/Threading/CriticalSection.hpp>
#include <Zen/Core/Threading/MutexFactory.hpp>

#include <Zen/Core/Utility/runtime_exception.hpp>

#include <Zen/Enterprise/I_MessageType.hpp>
#include <Zen/Enterprise/I_MessageFactory.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>

#include <iostream>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
NumericTypeMessageRegistry::NumericTypeMessageRegistry()
:   m_pMessageTypesMutex(Threading::MutexFactory::create())
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
NumericTypeMessageRegistry::~NumericTypeMessageRegistry()
{
    Threading::MutexFactory::destroy(m_pMessageTypesMutex);
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
NumericTypeMessageRegistry::destroyMessageType(wpMessageType_type _wpMessageType)
{
    NumericType* pMessageType = 
        dynamic_cast<NumericType*>(_wpMessageType.get());

    if( pMessageType != NULL )
    {
        delete pMessageType;
    }
    else
    {
        throw Zen::Utility::runtime_exception("NumericTypeMessageRegistry::destroyMessageType() : Invalid Type.");
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
NumericTypeMessageRegistry::pMessageType_type
NumericTypeMessageRegistry::getMessageType(boost::uint64_t _type)
{
    std::cout << "Getting message type " << _type << std::endl;

    NumericType* pRawMessageType = new NumericType(_type);

    pMessageType_type pMessageType(pRawMessageType, destroyMessageType);

    return pMessageType;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
NumericTypeMessageRegistry::registerMessageType(pMessageType_type _pMessageType)
{

    NumericType* pMessageType = 
        dynamic_cast<NumericType*>(_pMessageType.get());


    if (pMessageType != NULL)
    {
        Threading::CriticalSection guard(m_pMessageTypesMutex);

        std::cout << "Registering message type " << pMessageType->getType() << std::endl;

        MessageTypes_type::iterator iter = m_messageTypes.find(pMessageType->getType());
        if( iter == m_messageTypes.end() )
        {
            m_messageTypes[pMessageType->getType()] = _pMessageType;
        }
        else
        {
            throw Zen::Utility::runtime_exception("NumericTypeMessageRegistry::registerMessageType() : Message Type is already registered.");
        }
    }
    else
    {
        throw Zen::Utility::runtime_exception("NumericTypeMessageRegistry::registerMessageType() : Invalid type.");
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
NumericTypeMessageRegistry::unregisterMessageType(pMessageType_type _pMessageType)
{
    NumericType* pMessageType =
        dynamic_cast<NumericType*>(_pMessageType.get());

    if( pMessageType != NULL )
    {
        Threading::CriticalSection guard(m_pMessageTypesMutex);

        MessageTypes_type::iterator iter = m_messageTypes.find(pMessageType->getType());
        if(iter != m_messageTypes.end())
        {
            m_messageTypes.erase(iter);
        }
        else
        {
            throw Zen::Utility::runtime_exception("NumericTypeMessageRegistry::registerMessageType() : Message Type is not registered.");
        }
    }
    else
    {
        throw Zen::Utility::runtime_exception("NumericTypeMessageRegistry::unregisterMessageType() : Invalid type.");
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
static void destroy(Memory::managed_weak_ptr<I_MessageHeader> _pMessageHeader)
{
    NumericTypeMessageRegistry::MessageHeader* pMessageHeader = dynamic_cast<NumericTypeMessageRegistry::MessageHeader*>(_pMessageHeader.get());
    if (pMessageHeader)
    {
        delete pMessageHeader;
    }
    else
    {
        // TODO Error?
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
NumericTypeMessageRegistry::pMessageHeader_type
NumericTypeMessageRegistry::getMessageHeader(boost::archive::polymorphic_iarchive& _archive) const
{
    boost::uint64_t messageType, messageId, requestId;
    std::string srcLocation, destLocation;

    _archive & messageType;
    _archive & messageId;
    _archive & requestId;
    _archive & srcLocation;
    _archive & destLocation;

    {
        Threading::CriticalSection guard(m_pMessageTypesMutex);

        MessageTypes_type::const_iterator iter = m_messageTypes.find(messageType);

        if (iter != m_messageTypes.end())
        {
            return createMessageHeader(iter->second, messageId, requestId, srcLocation, destLocation);
        }
        else
        {
            // TODO Error?  Invalid message type
            pMessageHeader_type pMessageHeader;
            return pMessageHeader;
        }
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
NumericTypeMessageRegistry::pMessageHeader_type
NumericTypeMessageRegistry::createMessageHeader(pMessageType_type _pMessageType, boost::uint64_t _messageId, boost::uint64_t _requestId, const std::string& _srcLocation, const std::string& _destLocation) const
{
    return pMessageHeader_type(new MessageHeader(_pMessageType, _messageId, _requestId, _srcLocation, _destLocation), destroy);
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Enterprise
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
