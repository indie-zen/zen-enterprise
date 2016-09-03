//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_NETWORKING_NETWORK_MANAGER_HPP_INCLUDED
#define ZEN_NETWORKING_NETWORK_MANAGER_HPP_INCLUDED

#include <map>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class I_NetworkService;
class I_NetworkServiceFactory;

class NetworkManager
:   public I_NetworkManager
{
    /// @name Types
    /// @{
public:
    typedef std::map<I_NetworkService*, I_NetworkServiceFactory*> factories_type;
    /// @}

    /// @name I_NetworkManager implementation
    /// @{
public:
    virtual I_NetworkService* createNetworkService(const std::string& _name);

    virtual void destroyNetworkService(I_NetworkService* _pNetworkService);
    /// @}

    /// @name 'Structors
    /// @{
public:
             NetworkManager();
    virtual ~NetworkManager();
    /// @}

    /// @name Member Variables
    /// @{
private:
    factories_type  m_factories;
    /// @}

};  // class NetworkManager

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Networking
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~


#endif // ZEN_NETWORKING_NETWORK_MANAGER_HPP_INCLUDED
