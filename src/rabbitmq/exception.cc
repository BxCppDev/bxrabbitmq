// Ourselves:
#include "exception.h"

namespace rabbitmq {

  exception::exception (const std::string & error_)
    : _error_ (error_)
  {
    return;
  }

  const char * exception::what () const noexcept
  {
    return _error_.c_str ();
  }

} // end of namespace rabbitmq
