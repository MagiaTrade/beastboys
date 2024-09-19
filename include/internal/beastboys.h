//
// Created by Arthur Motelevicz on 06/03/23.
//

#ifndef BEAST_BOYS_BEASTBOYS_H
#define BEAST_BOYS_BEASTBOYS_H

#ifdef _WIN32
#include <SDKDDKVer.h>
#endif

#include "rest/common/NetworkTypes.h"
#include "websocket/common/WebsocketTypes.h"
#include "rawsocket/common/RawSocketTypes.h"
#include "server/rawsocket/RawDoorman.h"
#include "server/websocket/WebSocketDoorman.h"
#include "websocket/Streamer.h"
#include "websocket/impl/Stream.h"
#include "rawsocket/RawStreamer.h"
#include "rawsocket/RawMessenger.h"
#include "websocket/Messenger.h"
#include "rawsocket/impl/RawStream.h"
#include "rest/RestApi.h"
#include "rest/common/NetworkRequestSettings.h"
#include "common/CryptoHelper.h"
#include "server/common/Server.h"
#include "common/Logger.h"

#endif //BEAST_BOYS_BEASTBOYS_H
