// -*- mode: c++; -*-

#ifndef BXRABBITMQ_EXCEPTION_H
#define BXRABBITMQ_EXCEPTION_H

// Standard library:
#include <string>
#include <exception>


namespace rabbitmq {

  /// \brief Basic exception
  class exception : public std::exception
  {
     public:

        /// Constructor
        exception(const std::string & error_);

        /// Return the embedded error message
        const char * what() const noexcept;

     private:

        std::string _error_; ///< Embedded error message

  };

} // end of namespace rabbitmq

#endif // BXRABBITMQ_EXCEPTION_H
