//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#include "NetworkManager.hpp"

#include <Zen/Core/Plugins/I_PluginManager.hpp>
#include <Zen/Core/Plugins/I_ExtensionRegistry.hpp>
#include <Zen/Core/Plugins/I_Application.hpp>
#include <Zen/Core/Plugins/I_ExtensionQuery.hpp>

#include <iostream>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
NetworkManager::NetworkManager()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
NetworkManager::~NetworkManager()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
I_NetworkService*
NetworkManager::createNetworkService(const std::string& _name)
{
    I_NetworkServiceFactory* pFactory = NULL;

    Plugins::I_ExtensionRegistry& extensionRegistry = Plugins::I_ExtensionRegistry::getSingleton();
    const Zen::Plugins::I_ExtensionRegistry::pExtensionQuery_type pQuery = extensionRegistry.createQuery();

    pQuery->setNamespace("IndieZen::Networking");
    pQuery->setExtensionPoint("NetworkService");
    pQuery->setType(_name);

    // Get the extensions
    // Note that the result set takes ownership of pQuery
    Zen::Plugins::I_ExtensionRegistry::extension_result_set_ptr_type pExtensions = extensionRegistry.findExtensions(pQuery);

    // Grab the first extension; if there are more installed then eventually we can
    // deal with that but for now just grab one.
    Zen::Plugins::I_ExtensionRegistry::extension_result_set_type::iterator pExtensionIter = pExtensions->begin();

    if (pExtensionIter != pExtensions->end())
    {
        Zen::Plugins::I_ExtensionRegistry::class_factory_ref_type 
            classFactory(extensionRegistry.getClassFactory(*pExtensionIter));

        pFactory = (dynamic_cast<I_NetworkServiceFactory*>(&classFactory));

        I_NetworkService* const pService = pFactory->create(_name);

        m_factories[pService] = pFactory;

        return pService;
    }
    else
    {
        // TODO Throw an exception / Log an error
        std::cout << "NetworkManager::createNetworkService(): Error finding NetworkService for " << _name << std::endl;
    }

    return NULL;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
NetworkManager::destroyNetworkService(I_NetworkService* _pNetworkService)
{
    m_factories[_pNetworkService]->destroy(_pNetworkService);

    // I_Extension needs to implement a return() method and we should
    // keep track of the extension used to create each factory and 
    // destroy the factory here.
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Networking
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
