//
// Created by Arthur Motelevicz on 26/02/23.
//

#ifndef SOCKET_SERVERSTATE_H
#define SOCKET_SERVERSTATE_H

#include <boost/asio.hpp>
#include <iostream>

namespace bb::network::server
{
  class ServerState;
  class Client;
  class Connection;

  using OnSendMessageCallback = std::function<void(const std::string& message)>;
  using OnClientJoinCallback = std::function<void(const std::shared_ptr<Client>& client)>;
  using OnClientSentCallback = std::function<void(const std::shared_ptr<Client>& client, const std::string& message)>;

  class ServerState : public std::enable_shared_from_this<ServerState>
  {
  public:
    ServerState() = default;
    ~ServerState();

    std::shared_ptr<Client> join(Connection *connection);
    void leave(Connection *connection);
    void send(const std::string &message);
    void sendTo(const std::shared_ptr<Client>& client, const std::string &message);
    void pingAll();
    void leaveAll();
    void setOnSendMessageCB(const OnSendMessageCallback& cb);
    void setOnClientJoinCallback(const OnClientJoinCallback& cb);
    void setOnClientSentCallback(const OnClientSentCallback& cb);

    void onReceive(Connection * connection, const std::string &message);
  private:
    OnSendMessageCallback _onSendMessageCb{nullptr};
    OnClientJoinCallback _onClientJoinCallback{nullptr};
    OnClientSentCallback _onClientSentCallback{nullptr};
    std::vector<std::shared_ptr<Client>> _clients;
  };
}


#endif //SOCKET_SERVERSTATE_H
