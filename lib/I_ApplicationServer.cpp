//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#include "ApplicationServer.hpp"

#include <Zen/Core/Threading/MutexFactory.hpp>
#include <Zen/Core/Threading/I_Mutex.hpp>
#include <Zen/Core/Threading/CriticalSection.hpp>

#include <map>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
I_ApplicationServer::I_ApplicationServer()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
I_ApplicationServer::~I_ApplicationServer()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
static std::map<std::string, I_ApplicationServer*>   sm_servers;
static Threading::I_Mutex* sm_pServerGuard = Threading::MutexFactory::create();
namespace {
    class gc 
    { 
    public: 
        ~gc() 
        { 
            {
                Zen::Threading::CriticalSection guard(sm_pServerGuard);

                while (!sm_servers.empty())
                {
                    delete sm_servers.begin()->second;
                    sm_servers.erase(sm_servers.begin());
                }
            }

            Threading::MutexFactory::destroy(sm_pServerGuard); 
        } 
    }; 
    static gc sm_garbageCollection;
}   // namespace
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
I_ApplicationServer&
I_ApplicationServer::getInstance(const std::string& _instanceName)
{
    Threading::CriticalSection lock(sm_pServerGuard);
    
    std::map<std::string, I_ApplicationServer*>::iterator iter = sm_servers.find(_instanceName);
    if (iter == sm_servers.end())
    {
        I_ApplicationServer* pServer = new ApplicationServer();
        sm_servers[_instanceName] = pServer;
        return *pServer;
    }
    else
    {
        return *iter->second;
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Enterprise
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

