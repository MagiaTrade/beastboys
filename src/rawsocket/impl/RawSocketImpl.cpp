//
// Created by Arthur Motelevicz on 01/03/23.
//

#include <iostream>
#include <memory>
#include <optional>

#include "RawSocketImpl.h"
#include "RawSharedState.h"
#include "RawStream.h"
#include "RawResolver.h"

#ifdef __APPLE__
#include <pthread.h>
#endif

namespace bb{
namespace network{
namespace rs{

using namespace boost;

  RawSocketImpl::RawSocketImpl()
  {
    _workGuard = std::make_unique<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>>(_ioc.get_executor());
    _sharedState = std::make_shared<SharedState>();
}

std::shared_ptr<RawSocketImpl> RawSocketImpl::create()
{
  auto instance = std::shared_ptr<RawSocketImpl>(new RawSocketImpl());
  instance->initialize();
  return instance;
}

void RawSocketImpl::initialize()
{
  startContext();
}

void RawSocketImpl::startContext()
{
  auto self = shared_from_this();
  _worker = std::thread([self]()
  {
#ifdef __APPLE__
    pthread_setname_np("RawSockApi-Worker");
#endif

    while(!self->_stopWorker)
    {
      try {
          self->_ioc.run_one();
      }
      catch (const boost::system::system_error &e) {
        REPORT_ASIO_ERROR_(e.code())
        self->restartContext();
      }
    }
  });
}


void RawSocketImpl::restartContext(){
    _workGuard.reset();
    _ioc.restart();
    _workGuard = std::make_unique<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>>(_ioc.get_executor());
}

std::weak_ptr<Stream>  RawSocketImpl::openStream(std::string baseUrl,
                              std::string port,
                              std::string endPoint,
                              StreamCB cb,
                             char delimiter)
{
    //safe check to defaults port and target
    if(port.empty())
        port = "443";

    if(endPoint.empty())
        endPoint = "/";

    std::shared_ptr<Stream> stream{nullptr};


    stream = std::make_shared<Stream>(_ioc,
                                      std::move(baseUrl),
                                      std::move(port),
                                      std::move(endPoint),
                                      std::move(cb),
                                      delimiter);



    std::make_shared<Resolver>(_sharedState, stream, _ioc)->run();

    return stream;
}

  std::weak_ptr<Stream>  RawSocketImpl::openStream(std::string baseUrl,
                                                   std::string port,
                                                   std::string endPoint,
                                                   StreamCB2 cb,
                                                   char delimiter)
  {

    //safe check to defaults port and target
    if(port.empty())
      port = "443";

    if(endPoint.empty())
      endPoint = "/";

    std::shared_ptr<Stream> stream{nullptr};


    stream = std::make_shared<Stream>(_ioc,
                                      std::move(baseUrl),
                                      std::move(port),
                                      std::move(endPoint),
                                      std::move(cb),
                                      delimiter);



    std::make_shared<Resolver>(_sharedState, stream, _ioc)->run();

    return stream;
  }

RawSocketImpl::~RawSocketImpl(){
  _stopWorker = true;
  _workGuard.reset();
  _ioc.stop();
  if(_worker.joinable())
  {
    if (std::this_thread::get_id() != _worker.get_id()) {
      _worker.join();
    } else {
      logE << "[RawSocketImpl] Attempted to join worker thread from within itself.";
    }
  }

  logT << "Destructor RawSocketImpl";
}

}
}
}