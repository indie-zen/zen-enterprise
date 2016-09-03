//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#include "ApplicationServerManager.hpp"

#include "ResourceLocation.hpp"

#include <Zen/Core/Threading/MutexFactory.hpp>
#include <Zen/Core/Threading/CriticalSection.hpp>

#include <Zen/Core/Plugins/I_ExtensionRegistry.hpp>
#include <Zen/Core/Plugins/I_ExtensionPoint.hpp>

#include <Zen/Core/Utility/runtime_exception.hpp>

#include <boost/bind.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
ApplicationServerManager::ApplicationServerManager()
:   m_pResourceLocationGuard(Threading::MutexFactory::create())
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
ApplicationServerManager::~ApplicationServerManager()
{
    Threading::MutexFactory::destroy(m_pResourceLocationGuard);
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
ApplicationServerManager::pProtocolService_type
ApplicationServerManager::createProtocolService(I_ApplicationServer& _server, const std::string& _type)
{
    Plugins::I_ExtensionPoint::pExtension_type pExtension = 
        Plugins::I_ExtensionRegistry::getSingleton()
            .getExtensionPoint(I_ProtocolService::getNamespace(), I_ProtocolService::getExtensionPointName())
                ->getExtension(_type);

    if (pExtension)
    {
        I_ProtocolServiceFactory* pFactory = 
            dynamic_cast<I_ProtocolServiceFactory*>(&pExtension->getClassFactory());

        if (pFactory)
        {
            return pFactory->create(_server, _type);
        }
    }

    return pProtocolService_type();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
ApplicationServerManager::pApplicationService_type
ApplicationServerManager::createApplicationService(I_ApplicationServer& _server, const std::string& _type)
{
    Plugins::I_ExtensionPoint::pExtension_type pExtension = 
        Plugins::I_ExtensionRegistry::getSingleton()
            .getExtensionPoint(I_ApplicationService::getNamespace(), I_ApplicationService::getExtensionPointName())
                ->getExtension(_type);

    if (pExtension)
    {
        I_ApplicationServiceFactory* pFactory = 
            dynamic_cast<I_ApplicationServiceFactory*>(&pExtension->getClassFactory());

        if (pFactory)
        {
            return pFactory->create(_server, _type);
        }
    }

    return pApplicationService_type();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
ApplicationServerManager::pResourceLocation_type
ApplicationServerManager::createLocation(const std::string& _location)
{
    // Lock for consistency
    Threading::CriticalSection lock(m_pResourceLocationGuard);

    // Look to see if the resource location already exists
    ResourceLocations_type::iterator iter = m_resourceLocations.find(_location);
    if (iter != m_resourceLocations.end())
    {
        if (!iter->second.expired())
        {
            return iter->second.lock();
        }
        else
        {
            m_resourceLocations.erase(iter);
        }
    }

    // Wasn't found, so make one.
    pResourceLocation_type pLocation = pResourceLocation_type(new ResourceLocation(_location), boost::bind(&ApplicationServerManager::destroyLocation, this, _1));

    m_resourceLocations[_location] = pLocation.getWeak();
    return pLocation;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
ApplicationServerManager::destroyLocation(wpResourceLocation_type _pLocation)
{
    ResourceLocation* pLocation = dynamic_cast<ResourceLocation*>(_pLocation.get());
    if (pLocation != NULL)
    {
        {
            Threading::CriticalSection lock(m_pResourceLocationGuard);
            m_resourceLocations.erase(pLocation->toString());
        }        

        delete pLocation;
    }
    else
    {
        // TODO Error, wrong type!
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Enterprise
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
