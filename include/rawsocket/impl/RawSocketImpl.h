//
// Created by Arthur Motelevicz on 01/03/23.
//

#ifndef RAW_SOCKETIMPL_H
#define RAW_SOCKETIMPL_H

#include <memory>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include "RawSocketTypes.h"

namespace bb{
namespace network{
namespace rs{

class Stream;
class SharedState;

class RawSocketImpl: public std::enable_shared_from_this<RawSocketImpl>{
public:

    std::weak_ptr<Stream> openStream( std::string baseUrl,
                                      std::string port,
                                      std::string endPoint,
                                      StreamCB cb,
                                      char delimiter = '\0');

    std::weak_ptr<Stream> openStream(std::string baseUrl,
                                   std::string port,
                                   std::string endPoint,
                                   StreamCB2 cb,
                                   char delimiter = '\0');

    virtual ~RawSocketImpl();
    boost::asio::io_context _ioc;
    std::shared_ptr<SharedState> _sharedState{nullptr};
    std::thread _worker;
    std::unique_ptr<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>> _workGuard;
//  boost::asio::executor_work_guard<boost::asio::io_context::executor_type> _workGuard;
    std::atomic<bool> _stopWorker{false};

  static std::shared_ptr<RawSocketImpl> create();

private:
  RawSocketImpl();
  void initialize();
  void startContext();
  void restartContext();
};

}
}
}

#endif //RAW_SOCKETIMPL_H
