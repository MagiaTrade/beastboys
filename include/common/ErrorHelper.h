//
// Created by Arthur Motelevicz on 30/09/24.
//

#ifndef BEASTBOYS_ERRORHELPER_H
#define BEASTBOYS_ERRORHELPER_H

#include <mgutils/Logger.h>

#define RETURN_IF_ASIO_ERROR_(ec) \
  if (ec.value() != 0) { \
      NOTIFY_ERROR(ec.value(), ec.message()); \
      return; \
  }

#define REPORT_ASIO_ERROR_(ec) \
  if (ec.value() != 0) { \
    NOTIFY_ERROR(ec.value(), ec.message()); \
  }

#endif //BEASTBOYS_ERRORHELPER_H
