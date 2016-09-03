//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_APPSERVER_I_CONTAINER_HPP_INCLUDED
#define ZEN_ENTERPRISE_APPSERVER_I_CONTAINER_HPP_INCLUDED

#include "Configuration.hpp"

#include <boost/noncopyable.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
namespace AppServer {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class I_ApplicationServer;

/// Helper container class that sets up an application server.
/// Use this implementation if you wish, but it's not required.
class ENTERPRISE_DLL_LINK I_Container
:   public boost::noncopyable
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name I_Container interface
    /// @{
public:
    /// Initialize the container.
    /// @return true if the container was able to load the
    ///     configuration file and install all of the application
    ///     services and protocol services.
    /// Parameters:
    ///     --config -c : configuration xml file.
    ///     --lang -l   : scripting plugin to load.
    ///     --script -s : boot script.
    /// 
    virtual bool init(int _argc, const char* _argv[]) = 0;

    /// Run the container.
    virtual int run() = 0;

    /// Stop the container.
    /// @note The container will need to be reinitialized prior to use after this is called.
    virtual void stop() = 0;

    virtual I_ApplicationServer& getApplicationServer() = 0;
    /// @}

    /// @name Static methods
    /// @{
public:
    /// Get the singleton container.
    static I_Container& getSingleton();
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_Container();
    virtual ~I_Container();
    /// @}
};

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace AppServer
}   // namespace Enterprise
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_APPSERVER_I_CONTAINER_HPP_INCLUDED
