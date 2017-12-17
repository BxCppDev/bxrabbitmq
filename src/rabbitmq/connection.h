// -*- mode: c++; -*-

#ifndef BXRABBITMQ_CONNECTION_H
#define BXRABBITMQ_CONNECTION_H

// Standard library:
#include <memory>

// Third party:
// - Boost:
// #include <boost/core/noncopyable.hpp>

// this project:
#include "parameters.h"

namespace rabbitmq {

  class channel;

  /// \brief Connection to a RabbitMQ server
  class connection
  {
     public:
        static const int NB_CHANNEL_MAX = 1;

     public:
        /// Constructor & co
        connection  (const connection_parameters & params_,
                     const bool                    publisher_confirm_ = false);
        //  forbidden
        connection  ()                                    = delete;
        connection  (const connection & con_)             = delete;
        connection & operator = (const connection & con_) = delete;
        //
        bool                          is_ok                     () const;
        const connection_parameters & get_connection_parameters () const;
        const channel &               get_channel               () const;
        channel &                     grab_channel              ();

     private:
        connection_parameters     _params_;
        std::unique_ptr <channel> _chan1_;  // TODO thread safety => for now only one channel
                                            // later: several possible with different connection
  };

} // end of namespace rabbitmq

#endif // BXRABBITMQ_CONNECTION_H
