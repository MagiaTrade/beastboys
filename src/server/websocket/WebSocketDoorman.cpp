//
// Created by Arthur Motelevicz on 26/02/23.
//

#include "WebSocketDoorman.h"
#include "ServerState.h"
#include "HttpListener.h"
#include "common/ErrorHelper.h"

namespace bb::network::server::ws
{
  void WebSocketDoorman::onAccept(boost::system::error_code ec)
  {
    if(!ec) {
      std::make_shared<HttpListener>(std::move(_sock), _serverState)->run();
    }
    else{
      logE << "Error: " << ec.value() << " Msg: " << ec.message();
    }

    run();
  }
}

