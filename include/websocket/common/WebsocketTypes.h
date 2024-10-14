//
// Created by Arthur Motelevicz on 01/03/23.
//

#ifndef BINANCEBEAST_WEBSOCKETTYPES_H
#define BINANCEBEAST_WEBSOCKETTYPES_H

#include <boost/variant.hpp>
#include <boost/beast.hpp>
#include "WebsocketResponse.h"

namespace bb::network::ws {
    class Stream;
};

namespace bb::network::ws
{
  using CloseStreamCallback = std::function<void(std::shared_ptr<bb::network::ws::Stream> stream)>;
  using PongStreamCallback = std::function<void(std::shared_ptr<bb::network::ws::Stream> stream)>;
  using PingStreamCallback = std::function<void(std::shared_ptr<bb::network::ws::Stream> stream)>;
  using StreamCB = std::function<void(bool success, const std::string& data, std::shared_ptr<bb::network::ws::Stream> stream)>;
  using SendMessageCB = std::function<void(bool success)>;
  //Todo:: create other types (bytes, text, html, etc...)
}


#endif //BINANCEBEAST_WEBSOCKETTYPES_H
