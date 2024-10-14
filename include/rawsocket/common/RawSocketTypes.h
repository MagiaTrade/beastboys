//
// Created by Arthur Motelevicz on 01/03/23.
//

#ifndef RAWSOCKETTYPES_H
#define RAWSOCKETTYPES_H

#include <boost/variant.hpp>
#include <memory>
#include "RawSocketResponse.h"

namespace bb::network::rs {
    class Stream;
};

namespace bb::network::rs {
    using CloseStreamCallback = std::function<void(std::shared_ptr<bb::network::rs::Stream> stream)>;
    using PongStreamCallback = std::function<void(std::shared_ptr<bb::network::rs::Stream> stream)>;
    using PingStreamCallback = std::function<void(std::shared_ptr<bb::network::rs::Stream> stream)>;
    using StreamCB = std::function<void(bool success, const std::string& data, std::shared_ptr<bb::network::rs::Stream> stream)>;
    using StreamCB2 = std::function<void(bool success, const char* data, size_t length, std::shared_ptr<bb::network::rs::Stream> stream)>;
    using SendMessageCB = std::function<void(bool success)>;
    using FinishCallback = std::function<void()>;

    //Todo:: create other types (bytes, text, html, etc...)

}


#endif //RAWSOCKETTYPES_H
