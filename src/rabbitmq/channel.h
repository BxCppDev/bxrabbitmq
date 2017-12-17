// -*- mode: c++; -*-

#ifndef BXRABBITMQ_CHANNEL_H
#define BXRABBITMQ_CHANNEL_H

// This project:
#include "parameters.h"
#include "basic_properties.h"

namespace rabbitmq {

  class connection;

  /// \brief RabbitMQ Channel
  class channel
  {

     public:
        typedef void (*msg_consume_func) (std::string &      msg_,
                                          std::string &      routing_key_,
                                          basic_properties & props_);

     public:
        /// Constructor & co
        channel  (const connection & con_,
                  const unsigned int num_,
                  const bool         publisher_confirm_ = false);
        //  Ctor & co : forbidden
        ~channel ();
        channel  ()                                   = delete;
        channel  (const channel & chan_)              = delete;
        channel & operator =  (const channel & chan_) = delete;
        //
        bool is_ok            () const;

        void exchange_declare (const exchange_parameters & params_);

        void queue_declare    (queue_parameters &          params_);  // not const -> if not set, return queue name choosen by rabbit

        void queue_bind       (const std::string           queue_,
                               const std::string           exchange_,
                               const std::string           bindingkey_ = "");

        void basic_publish    (const std::string           exchange_,
                               const std::string           routing_key_,
                               const std::string           body_,
                               const basic_properties &    props_     = basic_properties::default_basic_properties ());

        void basic_consume    (const std::string           queue_,
                               const std::string           consumer_tag_ = "",
                               // const bool                  no_local_     = false,  //  ??
                               const bool                  no_ack_       = false,
                               const bool                  exclusive_    = false);

        void consume_message  (std::string &               msg_,
                               std::string &               routing_key_,
                               basic_properties &          props_,
                               uint64_t &                  delivery_tag_,
                               const float                 timeout_sec_ = -1.0); // négative -> infinity -> blocking

        void basic_ack        (const uint64_t              delivery_tag_,
                               const bool                  multiple_ = false);

        void basic_qos        (const uint16_t              prefetch_count_);
                               //const uint32_t              prefetch_size_,
                               //const bool                  global);

        void start_consuming  (const msg_consume_func      callback_);

        void stop_consuming   ();

        void test ();

     private:
        class impl;
        impl* _pimpl_;

  };

} // end of namespace rabbitmq

#endif // BXRABBITMQ_CHANNEL_H
