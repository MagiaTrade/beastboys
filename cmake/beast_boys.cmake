set(BEAST_BOYS_HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/common/cacert_data.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/websocket/impl/Resolver.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/websocket/impl/Stream.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/websocket/impl/Connector.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/websocket/impl/SSLHandShaker.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/websocket/impl/TargetHandShaker.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/websocket/impl/Receiver.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/websocket/impl/Sender.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/websocket/impl/WebsocketImpl.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/websocket/impl/SharedState.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/websocket/Streamer.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/websocket/Messenger.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/websocket/common/WebsocketTypes.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/websocket/common/WebsocketResponse.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rawsocket/RawMessenger.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rawsocket/RawStreamer.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rawsocket/common/RawSocketResponse.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rawsocket/common/RawSocketTypes.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rawsocket/impl/RawConnector.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rawsocket/impl/RawReceiver.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rawsocket/impl/RawResolver.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rawsocket/impl/RawSender.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rawsocket/impl/RawSharedState.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rawsocket/impl/RawSocketImpl.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rawsocket/impl/RawStream.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/server/common/Client.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/server/common/Connection.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/server/common/Doorman.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/server/common/Server.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/server/common/ServerState.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/server/rawsocket/RawDoorman.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/server/rawsocket/RSConnection.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/server/websocket/WebSocketDoorman.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/server/websocket/HttpListener.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/server/websocket/HandShaker.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/server/websocket/WSConnection.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/common/ErrorHelper.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/common/CryptoHelper.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rest/RestApi.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rest/common/NetworkRequestSettings.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rest/common/NetworkTypes.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rest/common/RestApiResponse.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rest/impl/BoostInternalImpl.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rest/impl/ResponseHelper.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/beastboys
)


set(BEAST_BOYS_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/websocket/impl/Resolver.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/websocket/impl/Stream.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/websocket/impl/Connector.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/websocket/impl/SSLHandShaker.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/websocket/impl/TargetHandShaker.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/websocket/impl/Receiver.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/websocket/impl/Sender.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/websocket/impl/WebsocketImpl.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/websocket/impl/SharedState.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/websocket/Streamer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/websocket/Messenger.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/websocket/common/WebsocketResponse.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rawsocket/RawMessenger.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rawsocket/RawStreamer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rawsocket/common/RawSocketResponse.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rawsocket/impl/RawConnector.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rawsocket/impl/RawReceiver.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rawsocket/impl/RawResolver.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rawsocket/impl/RawSender.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rawsocket/impl/RawSharedState.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rawsocket/impl/RawSocketImpl.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rawsocket/impl/RawStream.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/server/common/Client.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/server/common/Connection.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/server/common/Doorman.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/server/common/Server.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/server/common/ServerState.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/server/rawsocket/RawDoorman.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/server/rawsocket/RSConnection.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/server/websocket/WebSocketDoorman.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/server/websocket/HttpListener.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/server/websocket/HandShaker.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/server/websocket/WSConnection.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/common/CryptoHelper.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rest/common/NetworkRequestSettings.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rest/common/RestApiResponse.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rest/impl/BoostInternalImpl.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rest/impl/ResponseHelper.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rest/RespApi.cpp
)

set(BEAST_BOYS_INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}/external
  ${CMAKE_CURRENT_SOURCE_DIR}/external/rapidjson/include
  ${CMAKE_CURRENT_SOURCE_DIR}/fmt/include
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include/internal
  ${CMAKE_CURRENT_SOURCE_DIR}/include/websocket
  ${CMAKE_CURRENT_SOURCE_DIR}/include/websocket/common
  ${CMAKE_CURRENT_SOURCE_DIR}/include/websocket/impl
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rest
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rest/common
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rest/impl
  ${CMAKE_CURRENT_SOURCE_DIR}/include/server/rawsocket
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rawsocket
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rawsocket/common
  ${CMAKE_CURRENT_SOURCE_DIR}/include/rawsocket/impl
  ${CMAKE_CURRENT_SOURCE_DIR}/include/server
  ${CMAKE_CURRENT_SOURCE_DIR}/include/server/common
  ${CMAKE_CURRENT_SOURCE_DIR}/include/server/rawsocket
  ${CMAKE_CURRENT_SOURCE_DIR}/include/server/websocket
)
