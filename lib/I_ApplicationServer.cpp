//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#include <Zen/Enterprise/I_ApplicationServer.hpp>

#include <map>
#include <mutex>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
static std::map<std::string, I_ApplicationServer*>   sm_servers;
static std::mutex sm_pServerGuard = new std::mutex();
namespace {
    class gc 
    { 
    public: 
        ~gc() 
        { 
            {
                std::lock_guard<std::mutex> lock(*sm_pServerGuard);

                while (!sm_servers.empty())
                {
                    delete sm_servers.begin()->second;
                    sm_servers.erase(sm_servers.begin());
                }
            }

            delete sm_pServerGuard;
        } 
    }; 
    static gc sm_garbageCollection;
}   // namespace
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
I_ApplicationServer&
I_ApplicationServer::getInstance(const std::string& _instanceName)
{
    std::lock_guard<std::mutex> lock(*sm_pServerGuard);
    
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

