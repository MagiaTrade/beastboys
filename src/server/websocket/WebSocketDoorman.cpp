//
// Created by Arthur Motelevicz on 26/02/23.
//

#include "include/server/websocket/WebSocketDoorman.h"
#include "include/server/common/ServerState.h"
#include "include/server/websocket/HttpListener.h"
#include "Logger.h"

namespace bb::network::server::ws
{
  void WebSocketDoorman::onAccept(boost::system::error_code ec)
  {
    if(!ec) {
      std::make_shared<HttpListener>(std::move(_sock), _serverState)->run();
    }
    else{
      lg(mgutils::Error)<< "Error: " << ec.value() << " Msg: " << ec.message();
    }

    run();
  }
}

