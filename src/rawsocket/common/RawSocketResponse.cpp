//
// Created by Arthur Motelevicz on 01/03/23.
//

#include "include/rawsocketapi/common/RawSocketResponse.h"

namespace bb {
namespace network {
namespace rs {

Response::Response(const int pCode, const std::string &msg) :
        code(pCode),
        message(msg) {

}

bool Response::isOk() const {
    return code == 0;
}



}
}
}