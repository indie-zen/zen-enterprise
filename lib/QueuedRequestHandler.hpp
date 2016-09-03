//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Enterprise Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ENTERPRISE_QUEUED_REQUEST_HANDLER_HPP_INCLUDED
#define ZEN_ENTERPRISE_QUEUED_REQUEST_HANDLER_HPP_INCLUDED

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Enterprise {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
;

/// Queued Request Handler
/// This class queues a series of request handlers and dispatches 
/// them sequentially and asynchronously.  After the final request
/// handler returns, the final response handler is executed.
class QueuedRequestHandler
{
    /// @name Types
    /// @{
public:
    typedef std::list<pRequestHandler_type>     RequestHandlerList_type;
    /// @}

    /// @name QueuedRequestHandler interface.
    /// @{
public:
    /// @}

    /// @name Events
    /// @{
public:
    /// @}

    /// @name 'Structors
    /// @{
public:
    /// @param _requestHandlerList The list of request handlers.  This list
    ///     is copied and this class wlll not retain a reference to it.
    /// @param _pResponseHandler the final response handler that will be executed
    ///     after all of the request handlers have been dispatched.
    /// @param _threadPool the thread pool that this queued request handler
    ///     will use to dispatch the requests.
    explicit QueuedRequestHandler(RequestHandlerList_type& _requestHandlerList, pResponseHandler_type _pResponseHandler, Threading::ThreadPool& _threadPool);
    virtual ~QueuedRequestHandler();
    /// @}

};  // interface QueuedRequestHandler

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Enterprise
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ENTERPRISE_QUEUED_REQUEST_HANDLER_HPP_INCLUDED
