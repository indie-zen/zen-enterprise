//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_I_NETWORK_MANAGER_HPP_INCLUDED
#define ZEN_ENTERPRISE_I_NETWORK_MANAGER_HPP_INCLUDED

#include "Configuration.hpp"

#include <string>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class I_NetworkService;

class ENTERPRISE_DLL_LINK I_NetworkManager
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name I_NetworkManager interface
    /// @{
public:
    /// Create a network service by name
    virtual I_NetworkService* createNetworkService(const std::string& _name) = 0;

    /// Destroy the specified I_NetworkService that was created by
    /// createNetworkService();
    virtual void destroyNetworkService(I_NetworkService* _pService) = 0;
    /// @}

    /// @name Static Methods
    /// @{
public:
    static I_NetworkManager& getSingleton();
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_NetworkManager();
    virtual ~I_NetworkManager();
    /// @}

};  // interface I_NetworkManager

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Enterprise
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_I_NETWORK_MANAGER_HPP_INCLUDED
