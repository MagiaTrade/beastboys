//
// Created by Arthur Motelevicz on 29/07/24.
//

#include "include/server/rawsocket/RawDoorman.h"
#include "include/server/common/ServerState.h"
#include "include/server/rawsocket/RSConnection.h"
#include "Logger.h"

namespace bb::network::server::rs
{
  void RawDoorman::onAccept(boost::system::error_code ec)
  {
    if (!ec)
    {
      std::make_shared<bb::network::server::rs::RSConnection>(std::move(_sock), _serverState)->run();
    } else {
      lg(mgutils::Error) << "Error: " << ec.value() << " Msg: " << ec.message();
    }
    run();
  }
}