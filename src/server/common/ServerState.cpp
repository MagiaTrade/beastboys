//
// Created by Arthur Motelevicz on 26/02/23.
//

#include "ServerState.h"
#include "Client.h"
#include "Connection.h"
#include "common/ErrorHelper.h"

namespace bb::network::server
{
  std::shared_ptr<Client> ServerState::join(Connection *connection)
  {
    auto client = std::make_shared<Client>(connection);
    _clients.push_back(client);
    if(_onClientJoinCallback)
      _onClientJoinCallback(client);
    return client;
  }

  void ServerState::leave(Connection *connection)
  {
    auto it = std::find_if(_clients.begin(), _clients.end(), [&](std::shared_ptr<Client> &client) {
      return client->getConnection() == connection;
    });

    if (it != _clients.end())
      _clients.erase(it);
  }

  void ServerState::send(const std::string &message)
  {
    for (const auto &c: _clients)
      c->getConnection()->send(message);
  }

  void ServerState::sendTo(const std::shared_ptr<Client>& client, const std::string &message)
  {
    client->getConnection()->send(message);
  }

  void ServerState::pingAll()
  {
    for (const auto &c: _clients)
      c->getConnection()->ping();
  }

  void ServerState::leaveAll()
  {
    for (const auto &c: _clients)
      c->getConnection()->disconnect();

    _clients.clear();
  }

  void ServerState::setOnSendMessageCB(const OnSendMessageCallback& cb)
  {
    _onSendMessageCb = cb;
  }

  void ServerState::setOnClientJoinCallback(const OnClientJoinCallback& cb)
  {
    _onClientJoinCallback = cb;
  }

  void ServerState::setOnClientSentCallback(const OnClientSentCallback& cb)
  {
    _onClientSentCallback = cb;
  }

  ServerState::~ServerState()
  {
    if(!_clients.empty())
      logE << "Clients not empty on ServerState destructor!";
  }

  void ServerState::onReceive(Connection * connection, const std::string &message)
  {
    auto it = std::find_if(_clients.begin(), _clients.end(),
                               [connection](const std::shared_ptr<Client>& client)
    {
       return connection == client->getConnection();
    });

    if(it != _clients.end())
    {
      if(_onClientSentCallback)
        _onClientSentCallback(*it, message);
    }
    else
      assert(false && "Client not found!");
  }
}
