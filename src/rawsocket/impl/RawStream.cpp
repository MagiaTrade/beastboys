//
// Created by Arthur Motelevicz on 04/03/23.
//

#include "RawStream.h"
#include <iostream>
#include <utility>
#include "common/ErrorHelper.h"

namespace bb::network::rs
{

Stream::Stream(boost::asio::io_context &ioc,
               std::string host,
               std::string port,
               std::string target,
               StreamCB cb,
               char delimiter):
_host(std::move(host)),
_port(std::move(port)),
_target(std::move(target)),
_cb(std::move(cb)),
_readUntilDelimiter(delimiter)
{
  _id = ++id;
  _socket = std::make_shared<boost::asio::ip::tcp::socket>(ioc);

  logI << "[RawStream] Stream " << _id << " created!";
}

Stream::Stream(boost::asio::io_context &ioc,
               std::string host,
               std::string port,
               std::string target,
               StreamCB2 cb,
               char delimiter):
    _host(std::move(host)),
    _port(std::move(port)),
    _target(std::move(target)),
    _cb2(std::move(cb)),
    _readUntilDelimiter(delimiter)

{
  _id = ++id;
  _socket = std::make_shared<boost::asio::ip::tcp::socket>(ioc);
  logI << "[RawStream] Stream " << _id << " created!";
}

uint32_t Stream::getId() const
{
  return _id;
}

std::string Stream::host() const
{
  return _host;
}

std::string Stream::port() const
{
  return _port;
}

std::string Stream::target() const
{
  return _target;
}

boost::asio::ip::tcp::socket& Stream::getSocket()
{
  return *_socket;
}

void Stream::feedData(const std::string& data)
{
  auto self = shared_from_this();
  if(_cb)
    _cb(true, data, std::move(self));
}

void Stream::feedData(const char* data, size_t length)
{
  auto self = shared_from_this();

  if(_cb2)
  {
    _cb2(true, data, length, std::move(self));
    return;
  }

  feedData(std::string(data, length));
}


void Stream::connectionAborted(boost::system::error_code ec)
{
  auto self = shared_from_this();
  if(_cb)
    _cb(false, ec.message(), std::move(self));
  else if(_cb2)
    _cb2(false, ec.message().data(), ec.message().size(), std::move(self));
}

void Stream::internalStop(const FinishCallback& cb)
{
  if (_socket && _socket->is_open())
  {
//    _socket->async_close(boost::beast::websocket::close_code::normal, [&](boost::system::error_code ec) {
//        if(_wasClosedByServer) return;
//        logI << "[RawStream] Stream " << id << " stopped by user!\n";
//    });

    boost::asio::post(_socket->get_executor(),
    [self = shared_from_this(), cb]()
    {
      boost::system::error_code ec;

      // Shutdown the socket to disallow further sends and receives
      self->_socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);

      RETURN_IF_ASIO_ERROR_(ec)

      self->_socket->close(ec);

      RETURN_IF_ASIO_ERROR_(ec)

      if(self->_wasClosedByServer)
        return;

      logI << "[RawStream] Stream " << self->getId() << " stopped by user!";

      if(cb)
        cb();
    });
  }
}

void Stream::stop(const FinishCallback& cb) {
  _wasClosedByClient = true;
  internalStop(cb);
}

void Stream::stopWithCloseCallbackTriggered()
{
  auto self = shared_from_this();
  stop();
  if(_closeStreamCB)
    _closeStreamCB(std::move(self));
}

//void Stream::ping(const std::string& payload) {
//
//    auto pingCb = [&](boost::system::error_code ec) {
//        REPORT_ASIO_ERROR_(ec)
//    };
//
////    _socket->async_ping(payload.c_str(),pingCb);
//}

Stream::~Stream()
{
  logI << "[RawStream] Destructor stream ID: (" << getId() << ") [ "<< this << "]";
}


void Stream::setCloseStreamCallback(const CloseStreamCallback& cb)
{
  _closeStreamCB = cb;
}

void Stream::setPongStreamCallback(const PongStreamCallback& cb)
{
  _pongStreamCB = cb;
}

void Stream::setPingStreamCallback(const PingStreamCallback& cb)
{
  _pingStreamCB = cb;
}

bool Stream::wasClosedByServer() const
{
  return _wasClosedByServer;
}

bool Stream::wasClosedByClient() const
{
  return _wasClosedByClient;
}

bool Stream::isOpen() const
{
  return _socket->is_open();
}

char Stream::getReadUntilDelimiter() const
{
  return _readUntilDelimiter;
}

}