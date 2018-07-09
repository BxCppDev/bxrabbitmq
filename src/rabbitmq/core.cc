// Ourselves:
#include "core.h"

// Standard library:
#include <string>
#include <memory>
#include <cstdlib>
#include <iostream>

namespace rabbitmq {
   
  core::core()
  {
    char * env = getenv("BXRABBITMQ_LOGGING");
    if (env != nullptr) {
      std::string loggin_repr(env);
      if (loggin_repr == "debug") {
        logging_level = LOGGING_DEBUG;
      } else if (loggin_repr == "warning") {
        logging_level = LOGGING_WARNING;
      } else if (loggin_repr == "notice") {
        logging_level = LOGGING_NOTICE;
      } else if (loggin_repr == "error") {
        logging_level = LOGGING_ERROR;
      } else if (loggin_repr == "fatal") {
        logging_level = LOGGING_FATAL;
      } else if (loggin_repr == "mute") {
        logging_level = LOGGING_MUTE;
      }
    }
    return;
  }
 
  // static
  core & core::_instance_()
  {
    static std::unique_ptr<core> _c;
    if (!_c) {
      _c.reset(new core);
    }
    return *_c;
  }

  bool core::is_debug() const
  {
    return logging_level >= LOGGING_DEBUG;
  }
  
  bool core::is_notice() const
  {
    return logging_level >= LOGGING_NOTICE;
  }

  bool core::is_warning() const
  {
    return logging_level >= LOGGING_WARNING;
  }

  core & core::instance()
  {
    return core::_instance_();
  }

  const core & core::const_instance()
  {
    return const_cast<core&>(core::_instance_());
  }
 
} // end of namespace rabbitmq
