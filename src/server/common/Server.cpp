//
// Created by Arthur Motelevicz on 26/02/23.
//

#include "Server.h"

namespace bb::network::server
{
  void Server::stop()
  {
    // Capture SIGINT and SIGTERM to perform a clean shutdown
    boost::asio::signal_set signals(_ioc, SIGINT, SIGTERM);
    signals.async_wait(
    [&](boost::system::error_code const &, int) {
      disconnectAll();
      _doorMan->stop();
      // Stop the io_context. This will cause run()
      // to return immediately, eventually destroying the
      // io_context and any remaining handlers in it.
      _ioc.stop();
    });
  }

  void Server::disconnectAll()
  {
    _serverState->leaveAll();
  }

  void Server::setOnSendMessageCB(const OnSendMessageCallback& cb)
  {
    _onSendMessageCb = cb;
    if(_serverState)
      _serverState->setOnSendMessageCB(_onSendMessageCb);
  }

  void Server::setOnClientJoinCB(const OnClientJoinCallback & cb)
  {
    _onClientJoinCallback = cb;
    if(_serverState)
      _serverState->setOnClientJoinCallback(_onClientJoinCallback);
  }

  void Server::setOnClientSentCallback(const OnClientSentCallback& cb)
  {
    _onClientSentCallback = cb;
    if(_serverState)
      _serverState->setOnClientSentCallback(_onClientSentCallback);
  }

  void Server::broadcast(const std::string& message) const
  {
    _serverState->send(message);
  }

  void Server::sendTo(const std::shared_ptr<Client>& client, const std::string &message)
  {
    _serverState->sendTo(client, message);
  }

  void Server::pingAll()
  {
    _serverState->pingAll();
  }

}
