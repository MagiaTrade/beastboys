//
// Created by Arthur Motelevicz on 04/03/23.
//

#include "Stream.h"
#include <iostream>
#include "common/ErrorHelper.h"

namespace bb::network::ws {

//Stream::Stream(boost::asio::io_context &ioc, std::string host, std::string port, std::string target, bool usesSSL):
//_ssl_context(boost::asio::ssl::context::sslv23_client),
//_host(std::move(host)),
//_port(std::move(port)),
//_target(std::move(target)),
//_usesSSL(usesSSL){
//    _id = ++id;
//
//    if(_usesSSL)
//    {
//        _ssl_context.set_default_verify_paths();
//        _ssl_context.set_verify_mode(boost::asio::ssl::verify_peer);
//
//        _socketSSL = std::make_shared<boost::beast::websocket::stream<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>>(ioc,_ssl_context);
//    }
//    else{
//        _socket = std::make_shared<boost::beast::websocket::stream<boost::asio::ip::tcp::socket>>(ioc);
//    }
//}

Stream::Stream(boost::asio::io_context &ioc,
               std::string host,
               std::string port,
               std::string target,
               boost::asio::ssl::context& ssl_context,
               StreamCB cb):
_host(std::move(host)),
_port(std::move(port)),
_target(std::move(target)),
_usesSSL(true),
_cb(cb)
{
    _id = ++id;
    _socketSSL = std::make_shared<boost::beast::websocket::stream<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>>(ioc,ssl_context);
}


Stream::Stream(boost::asio::io_context &ioc,
               std::string host,
               std::string port,
               std::string target,
               StreamCB cb):
_host(std::move(host)),
_port(std::move(port)),
_target(std::move(target)),
_usesSSL(false),
_cb(cb){
    _id = ++id;
    _socket = std::make_shared<boost::beast::websocket::stream<boost::asio::ip::tcp::socket>>(ioc);
}


uint32_t Stream::getId() const{
    return _id;
}

std::string Stream::host() const{
    return _host;
}

std::string Stream::port() const{
    return _port;
}

std::string Stream::target() const{
    return _target;
}

boost::beast::websocket::stream<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>& Stream::getSocketSSL(){
    return *_socketSSL;
}

boost::beast::websocket::stream<boost::asio::ip::tcp::socket>& Stream::getSocket(){
    return *_socket;
}

bool Stream::usesSSL() const {
    return _usesSSL;
}

void Stream::feedData(const std::string& data)
{
  auto self = shared_from_this();
  if(_cb)
      _cb(true, data, std::move(self));
}

void Stream::connectionAborted(boost::system::error_code ec)
{
  auto self = shared_from_this();
  if(_cb)
        _cb(false, ec.message(), std::move(self));
}

void Stream::internalStop()
{
  auto self = shared_from_this();

  if(_usesSSL)
  {
    if(_socketSSL->is_open())
    {
      _socketSSL->async_close(boost::beast::websocket::close_code::normal, [self = std::move(self)](boost::system::error_code ec)
      {
        if(self->_wasClosedByServer) return;
        logI << "Stream " << self->getId() << " stopped by user! Use count: " << self.use_count();
      });
    }

    return;
  }

    if(_socket->is_open())
    {
      _socket->async_close(boost::beast::websocket::close_code::normal, [self = std::move(self)](boost::system::error_code ec)
      {
        if(self->_wasClosedByServer) return;
        logI << "Stream " << self->getId() << " stopped by user! Use count: " << self.use_count();;
      });
    }
}

void Stream::stop()
{
    _wasClosedByClient = true;
    internalStop();
}

void Stream::stopWithCloseCallbackTriggered() {
    stop();
    if(_closeStreamCB)
        _closeStreamCB(shared_from_this());
}

void Stream::ping(const std::string& payload) {

    auto pingCb = [](boost::system::error_code ec) {
        REPORT_ASIO_ERROR_(ec)
    };

    if(_usesSSL) {
        _socketSSL->async_ping(payload.c_str(),pingCb);
        return;
    }
    _socket->async_ping(payload.c_str(),pingCb);
}

Stream::~Stream(){
  logI << "Destructor stream ID: (" << getId() << ") [ "<< this << "]";
}

void Stream::setWatchControlMessages()
{
  auto controlCB = [weakSelf = weak_from_this()](boost::beast::websocket::frame_type kind, boost::string_view payload)
  {
    auto self = weakSelf.lock();
      if(!self)
        return;

      switch (kind)
      {
        case boost::beast::websocket::frame_type::ping:
        {
//                    std::cout << "Ping message received! Payload: " << payload << "\n";
            if (self->_pingStreamCB)
              self->_pingStreamCB(self);
            return;
        }
        case boost::beast::websocket::frame_type::pong:
        {
//                    std::cout << "Pong message received! Payload: " << payload << "\n";
            if (self->_pongStreamCB)
              self->_pongStreamCB(self);
            return;
        }
        case boost::beast::websocket::frame_type::close:
        {
            //first flag to not call the client normal callback when shutting down
          self->_wasClosedByServer = true;
            //now stop it
          self->internalStop();
            if (self->_closeStreamCB)
              self->_closeStreamCB(self);
            return;
        }
      }
    };

    if(_usesSSL){
        _socketSSL->control_callback(controlCB);
        return;
    }

    _socket->control_callback(controlCB);
}

void Stream::setCloseStreamCallback(const CloseStreamCallback& cb){
    _closeStreamCB = cb;
}

void Stream::setPongStreamCallback(const PongStreamCallback& cb){
    _pongStreamCB = cb;
}

void Stream::setPingStreamCallback(const PingStreamCallback& cb){
    _pingStreamCB = cb;
}

bool Stream::wasClosedByServer(){
    return _wasClosedByServer;
}

bool Stream::wasClosedByClient(){
    return _wasClosedByClient;
}

bool Stream::isOpen() const
{
  return _usesSSL ? _socketSSL->is_open() : _socket->is_open();
}

}