// -*- mode: c++; -*-

#ifndef BXRABBITMQ_CONNECTION_H
#define BXRABBITMQ_CONNECTION_H

#include <memory>
#include <boost/scoped_ptr.hpp>

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
        connection  (const connection_parameters & params_);
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
        connection_parameters       _params_;
        boost::scoped_ptr <channel> _chan1_;  // TODO thread safety => pour l'instant un seul channel
                                              // +tard plusieurs (avec différentes connexions en implem)
  };

} // end of namespace rabbitmq

#endif // BXRABBITMQ_CONNECTION_H
