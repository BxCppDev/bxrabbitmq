#include <iostream>

//
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

// Ourselves:
#include "channel.h"
#include "connection.h"
#include "exception.h"

// pimpl rabbitmq-c:
#include <amqp.h>
#include <amqp_tcp_socket.h>
#include <amqp_ssl_socket.h>


namespace rabbitmq {

   /*******************************************************************************/
    
   class channel::impl
   {
      public:
         static const std::string              str_from_amqp   (const amqp_bytes_t &            bytes);
         static const amqp_bytes_t             str_to_amqp     (const std::string &             str);
         static const amqp_basic_properties_t  props_to_amqp   (const basic_properties &        props_);
         static const basic_properties         props_from_amqp (const amqp_basic_properties_t & props_);

      public:
         impl  (const bool publisher_confirm = false);
         ~impl ();  //  TODO

         void connect          (const connection_parameters & params, const unsigned int num);

         bool is_ok            ();

         void exchange_declare (const exchange_parameters &   params_);

         void queue_declare    (queue_parameters &            params_);

         void queue_bind       (const std::string &           queue_,
                                const std::string &           exchange_,
                                const std::string &           bindingkey_);

         publish_status_type
         basic_publish         (const std::string &           exchange_,
                                const std::string &           routing_key_,
                                const std::string &           body_,
                                const basic_properties &      props_);

        void basic_consume     (const std::string &           queue_,
                                const std::string &           consumer_tag_,
                                //const bool &                  no_local_,
                                const bool &                  no_ack_,
                                const bool &                  exclusive_);
     
        consume_status_type
        consume_message        (std::string &                 msg_,
                                std::string &                 routing_key_,
                                basic_properties &            props_,
                                uint64_t &                    delivery_tag_,
                                const float &                 timeout_sec_);

        void basic_ack         (const uint64_t &              delivery_tag_,
                                const bool &                  multiple_);

        void basic_qos         (const uint16_t &              prefetch_count_);

        void start_consuming   (const msg_consume_func &      callback_);

        void stop_consuming    ();

      private:
         amqp_connection_state_t _amqp_con_;
         amqp_socket_t*          _amqp_soc_;
         unsigned int            _amqp_ch_;
         bool                    _login_ok_;
         bool                    _channel_ok_;
         pid_t                   _consuming_;
         bool                    _acknowledge_;
         bool                    _publisher_confirm_;
   };

   /*******************************************************************************/


   channel::channel (const connection & con_,
                     const unsigned int num_,
                     const bool         publisher_confirm_)
   {
      _pimpl_ = new impl (publisher_confirm_);
      _pimpl_->connect (con_.get_connection_parameters (), num_);
      return;
   }

   channel::~channel ()
   {
      delete _pimpl_;
      return;
   }

   bool channel::is_ok () const
   {
      return _pimpl_->is_ok ();
   }

   void channel::exchange_declare (const exchange_parameters & params_)
   {
      _pimpl_->exchange_declare (params_);
   }

   void channel::queue_declare (queue_parameters & params_)
   {
      _pimpl_->queue_declare (params_);
   }

   void channel::queue_bind (const std::string queue_,
                             const std::string exchange_,
                             const std::string bindingkey_)
   {
      _pimpl_->queue_bind (queue_, exchange_, bindingkey_);
   }

   publish_status_type
   channel::basic_publish (const std::string        exchange_,
                           const std::string        routing_key_,
                           const std::string        body_,
                           const basic_properties & props_)
   {
      return _pimpl_->basic_publish (exchange_, routing_key_, body_, props_);
   }

   void channel::basic_consume (const std::string queue_,
                                const std::string consumer_tag_,
                                //const bool        no_local_,
                                const bool        no_ack_,
                                const bool        exclusive_)
   {
      //_pimpl_->basic_consume (queue_, consumer_tag_, no_local_, no_ack_, exclusive_);
      _pimpl_->basic_consume (queue_, consumer_tag_, no_ack_, exclusive_);
   }
  
   consume_status_type
   channel::consume_message (std::string &      msg_,
                             std::string &      routing_key_,
                             basic_properties & props_,
                             uint64_t &         delivery_tag_,
                             const float        timeout_sec_)
   {
     return _pimpl_->consume_message (msg_, routing_key_, props_, delivery_tag_, timeout_sec_);
   }

   void channel::basic_ack (const uint64_t delivery_tag_,
                            const bool     multiple_)
   {
      _pimpl_->basic_ack (delivery_tag_, multiple_);
   }

   void channel::basic_qos (const uint16_t prefetch_count_) {
      _pimpl_->basic_qos (prefetch_count_);
   }

   void channel::start_consuming (const msg_consume_func callback_)
   {
      _pimpl_->start_consuming (callback_);
   }

   void channel::stop_consuming ()
   {
      _pimpl_->stop_consuming ();
   }

   void channel::test ()
   {
      std::clog << "\nTEST 1\n\n";
      std::string  str1 = "BOB";
      std::string  str2;
      amqp_bytes_t byt0;
      byt0 = impl::str_to_amqp   (str1);
      str2 = impl::str_from_amqp (byt0);
      std::clog << "str2 =" << str2 << "=" << std::endl;

      std::clog << "\nTEST 2\n\n";
      amqp_basic_properties_t prop0;
      basic_properties prop1;
      basic_properties prop2;
      prop1.set_reply_to       ("Reply_To_Bob");
      prop1.set_correlation_id ("Bob_corid");
      std::clog << "prop1 = " << prop1.to_string () << std::endl;
      prop0 = impl::props_to_amqp   (prop1);
      //prop0._flags         = prop0._flags | AMQP_BASIC_CORRELATION_ID_FLAG;
      //prop0.correlation_id = impl::str_to_amqp (prop1.get_correlation_id ());
      //prop0._flags         = prop0._flags | AMQP_BASIC_REPLY_TO_FLAG;
      //prop0.reply_to       = impl::str_to_amqp (prop1.get_reply_to ());
      if (prop0._flags & AMQP_BASIC_CORRELATION_ID_FLAG) {
         std::clog << "prop0 corid = " << (char*) prop0.correlation_id.bytes << std::endl;
      } else {
         std::clog << "prop0 no corid" << std::endl;
      }
      prop2 = impl::props_from_amqp (prop0);
      std::clog << "prop2 = " << prop2.to_string () << std::endl;
   }

   /////////////////////////////////////////////////////////////////////////////////////////////////

   const std::string channel::impl::str_from_amqp (const amqp_bytes_t & bytes) {
      std::string str ((char*) bytes.bytes, (char*) bytes.bytes + bytes.len);
      return str;
   }

   const amqp_bytes_t channel::impl::str_to_amqp (const std::string & str) {
      amqp_bytes_t bytes;
      bytes.len   =         str.size ();
      bytes.bytes = (char*) str.data ();
      return bytes;
   }

   const amqp_basic_properties_t channel::impl::props_to_amqp (const basic_properties & props_)
   {
      amqp_basic_properties_t props;
      props._flags = 0;
      if (props_.has_content_type ()) {
         props._flags       = props._flags | AMQP_BASIC_CONTENT_TYPE_FLAG;
         props.content_type = str_to_amqp (props_.get_content_type ());
      }
      if (props_.has_content_encoding ()) {
         props._flags           = props._flags | AMQP_BASIC_CONTENT_ENCODING_FLAG;
         props.content_encoding = str_to_amqp (props_.get_content_encoding ());
      }
      if (props_.has_headers ()) {
         throw ::rabbitmq::exception ("Unexpected exception : todo headers");
      }
      if (props_.has_delivery_mode ()) {
         props._flags        = props._flags | AMQP_BASIC_DELIVERY_MODE_FLAG;
         props.delivery_mode = props_.get_delivery_mode ();
      }
      if (props_.has_priority ()) {
         props._flags   = props._flags | AMQP_BASIC_PRIORITY_FLAG;
         props.priority = props_.get_priority ();
      }
      if (props_.has_correlation_id ()) {
         props._flags         = props._flags | AMQP_BASIC_CORRELATION_ID_FLAG;
         props.correlation_id = str_to_amqp (props_.get_correlation_id ());
      }
      if (props_.has_reply_to ()) {
         props._flags   = props._flags | AMQP_BASIC_REPLY_TO_FLAG;
         props.reply_to = str_to_amqp (props_.get_reply_to ());
      }
      if (props_.has_expiration ()) {
         props._flags     = props._flags | AMQP_BASIC_EXPIRATION_FLAG;
         props.expiration = str_to_amqp (props_.get_expiration ());
      }
      if (props_.has_message_id ()) {
         props._flags     = props._flags | AMQP_BASIC_MESSAGE_ID_FLAG;
         props.message_id = str_to_amqp (props_.get_message_id ());
      }
      if (props_.has_timestamp ()) {
         props._flags    = props._flags | AMQP_BASIC_TIMESTAMP_FLAG;
         props.timestamp = props_.get_timestamp ();
      }
      if (props_.has_type ()) {
         props._flags = props._flags | AMQP_BASIC_TYPE_FLAG;
         props.type   = str_to_amqp (props_.get_type ());
      }
      if (props_.has_user_id ()) {
         props._flags  = props._flags | AMQP_BASIC_USER_ID_FLAG;
         props.user_id = str_to_amqp (props_.get_user_id ());
      }
      if (props_.has_app_id ()) {
         props._flags = props._flags | AMQP_BASIC_APP_ID_FLAG;
         props.app_id = str_to_amqp (props_.get_app_id ());
      }
      if (props_.has_cluster_id ()) {
         props._flags     = props._flags | AMQP_BASIC_CLUSTER_ID_FLAG;
         props.cluster_id = str_to_amqp (props_.get_cluster_id ());
      }
      return props;
   }

   const basic_properties channel::impl::props_from_amqp (const amqp_basic_properties_t & props_)
   {
      basic_properties props;
      if (props_._flags & AMQP_BASIC_CONTENT_TYPE_FLAG) {
         props.set_content_type (str_from_amqp (props_.content_type));
      }
      if (props_._flags & AMQP_BASIC_CONTENT_ENCODING_FLAG) {
         props.set_content_encoding (str_from_amqp (props_.content_encoding));
      }
      if (props_._flags & AMQP_BASIC_HEADERS_FLAG) {
         throw ::rabbitmq::exception ("Unexpected exception : todo headers");
      }
      if (props_._flags & AMQP_BASIC_DELIVERY_MODE_FLAG) {
         props.set_delivery_mode (props_.delivery_mode);
      }
      if (props_._flags & AMQP_BASIC_PRIORITY_FLAG) {
         props.set_priority (props_.priority);
      }
      if (props_._flags & AMQP_BASIC_CORRELATION_ID_FLAG) {
         props.set_correlation_id (str_from_amqp (props_.correlation_id));
      }
      if (props_._flags & AMQP_BASIC_REPLY_TO_FLAG) {
         props.set_reply_to (str_from_amqp (props_.reply_to));
      }
      if (props_._flags & AMQP_BASIC_EXPIRATION_FLAG) {
         props.set_expiration (str_from_amqp (props_.expiration));
      }
      if (props_._flags & AMQP_BASIC_MESSAGE_ID_FLAG) {
         props.set_message_id (str_from_amqp (props_.message_id));
      }
      if (props_._flags & AMQP_BASIC_TIMESTAMP_FLAG) {
         props.set_timestamp (props_.timestamp);
      }
      if (props_._flags & AMQP_BASIC_TYPE_FLAG) {
         props.set_type (str_from_amqp (props_.type));
      }
      if (props_._flags & AMQP_BASIC_USER_ID_FLAG) {
         props.set_user_id (str_from_amqp (props_.user_id));
      }
      if (props_._flags & AMQP_BASIC_APP_ID_FLAG) {
         props.set_app_id (str_from_amqp (props_.app_id));
      }
      if (props_._flags & AMQP_BASIC_CLUSTER_ID_FLAG) {
         props.set_cluster_id (str_from_amqp (props_.cluster_id));
      }
      return props;
   }

   channel::impl::impl (const bool publisher_confirm_)
   {
      _login_ok_          = false;
      _channel_ok_        = false;
      _consuming_         = 0;
      _publisher_confirm_ = publisher_confirm_;
   }

   void channel::impl::connect (const connection_parameters & params_, const unsigned int num_)
   {
      int              err;
      struct timeval   tv;
      struct timeval*  ptv = &tv;
      bool             tls = (params_.port == 5671);
      amqp_rpc_reply_t reply;

      ptv->tv_sec   = 5;  // timeout 5 sec
      ptv->tv_usec  = 0;
      _amqp_ch_     = num_;
      _amqp_con_    = amqp_new_connection ();
      if (tls) {
          //  std::clog << "trying ssl socket ... " << params_.port << std::endl;
         _amqp_soc_ = amqp_ssl_socket_new (_amqp_con_);
      } else {
         //  std::clog << "trying tcp socket ... " << params_.port << std::endl;
         _amqp_soc_ = amqp_tcp_socket_new (_amqp_con_);
      }
      if (!_amqp_soc_) {
         throw ::rabbitmq::exception ("Unable to create TCP socket");
      }
      if (tls) {
         amqp_ssl_socket_set_verify_peer     (_amqp_soc_, 0);
         amqp_ssl_socket_set_verify_hostname (_amqp_soc_, 0);
      }
      err = amqp_socket_open_noblock (_amqp_soc_, params_.host.c_str (), params_.port, ptv);
      if (err != AMQP_STATUS_OK) {
         std::clog << "open socket error = " << err << std::endl;
         throw ::rabbitmq::exception ("Unable to open TCP socket");
      }
      reply = amqp_login (_amqp_con_,
                          params_.vhost.c_str (),
                          connection::NB_CHANNEL_MAX,
                          131072,
                          0,
                          AMQP_SASL_METHOD_PLAIN,
                          params_.login.c_str (),
                          params_.passwd.c_str ());
      if (reply.reply_type != AMQP_RESPONSE_NORMAL) {
         throw ::rabbitmq::exception ("Unable to login Rabbit server");
      }
      _login_ok_ = true;
      amqp_channel_open (_amqp_con_, _amqp_ch_);
      reply = amqp_get_rpc_reply (_amqp_con_);
      if (reply.reply_type != AMQP_RESPONSE_NORMAL) {
         throw ::rabbitmq::exception ("Unable to create Rabbit channel");
      }
      if (_publisher_confirm_) {
         amqp_confirm_select_ok_t* ok = amqp_confirm_select (_amqp_con_, _amqp_ch_);
         if (ok == NULL) {
            throw ::rabbitmq::exception ("Unable to select publisher confirm mode");
         }
      }
      _channel_ok_ = true;
   }

   channel::impl::~impl ()  //  TODO
   {
      int              err;   // err < 0 => error
      amqp_rpc_reply_t reply;
      if (_channel_ok_) {
         reply = amqp_channel_close (_amqp_con_, _amqp_ch_, AMQP_REPLY_SUCCESS);
      }
      if (_login_ok_) {
         reply = amqp_connection_close   (_amqp_con_, AMQP_REPLY_SUCCESS);
         err   = amqp_destroy_connection (_amqp_con_);
      }
   }

   bool channel::impl::is_ok ()
   {
      return _channel_ok_;
   }

   void channel::impl::exchange_declare (const exchange_parameters & params_)
   {
      if (_channel_ok_) {
         amqp_exchange_declare (_amqp_con_,
                                _amqp_ch_,
                                str_to_amqp (params_.name),
                                str_to_amqp (params_.type),
                                params_.passive,
                                params_.durable,
                                params_.auto_delete,
                                params_.internal,
                                amqp_empty_table); // todo argums
         amqp_rpc_reply_t reply = amqp_get_rpc_reply (_amqp_con_);
         if (reply.reply_type != AMQP_RESPONSE_NORMAL) {
            throw ::rabbitmq::exception ("exchange_declare failure");
            // todo precisions
         }
      }
   }

   void channel::impl::queue_declare (queue_parameters & params_)
   {
      if (_channel_ok_) {
         amqp_queue_declare_ok_t *r = amqp_queue_declare (_amqp_con_,
                                                          _amqp_ch_,
                                                          str_to_amqp (params_.name),
                                                          params_.passive,
                                                          params_.durable,
                                                          params_.exclusive,
                                                          params_.auto_delete,
                                                          amqp_empty_table);
         if (r == NULL) {
            throw ::rabbitmq::exception ("queue_declare failure");
         }
         params_.name           = str_from_amqp (r->queue);
         amqp_rpc_reply_t reply = amqp_get_rpc_reply (_amqp_con_);
         if (reply.reply_type != AMQP_RESPONSE_NORMAL) {
            throw ::rabbitmq::exception ("queue_declare failure");
            // todo precisions
         }
      } else {
         throw ::rabbitmq::exception ("no channel for queue_declare");
      }
   }

   void channel::impl::queue_bind (const std::string & queue_,
                                   const std::string & exchange_,
                                   const std::string & bindingkey_)
   {
      if (_channel_ok_) {
         amqp_queue_bind (_amqp_con_,
                          _amqp_ch_,
                          str_to_amqp (queue_),
                          str_to_amqp (exchange_),
                          str_to_amqp (bindingkey_),
                          amqp_empty_table);
         amqp_rpc_reply_t reply = amqp_get_rpc_reply (_amqp_con_);
         if (reply.reply_type != AMQP_RESPONSE_NORMAL) {
            throw ::rabbitmq::exception ("queue_bind failure");
            // todo precisions
         }
      } else {
         throw ::rabbitmq::exception ("no channel for queue_bind");
      }
   }

   publish_status_type
   channel::impl::basic_publish (const std::string &      exchange_,
                                 const std::string &      routing_key_,
                                 const std::string &      body_,
                                 const basic_properties & props_)
   {
     publish_status_type ret = PUBLISH_OK;
      if (_channel_ok_) {
         amqp_basic_properties_t props = props_to_amqp (props_);
         int err = amqp_basic_publish (_amqp_con_,
                                       _amqp_ch_,
                                       str_to_amqp (exchange_),
                                       str_to_amqp (routing_key_),
                                       _publisher_confirm_,      //  'mandatory'
                                       0,                        //  'immediate' no more supported by amqp
                                       & props,
                                       str_to_amqp (body_));
         if (err != AMQP_STATUS_OK) {
           // throw ::rabbitmq::exception ("basic_publish failure with code : " + err);
           ret = PUBLISH_ERROR;
           return ret;
         }
         if (_publisher_confirm_) {
            bool         basic_return = false;
            amqp_frame_t frame;
            while (1) {
               //  std::clog << "---  confirm steps  ---" << std::endl;
               err = amqp_simple_wait_frame (_amqp_con_, &frame);
               if (err != AMQP_STATUS_OK) {
                 //throw ::rabbitmq::exception ("basic_publish confirm failure with code : " + err);
                 ret = PUBLISH_ERROR;
                 return ret;
               } else {
                  if (frame.frame_type == AMQP_FRAME_METHOD) {
                     if (frame.payload.method.id == AMQP_BASIC_ACK_METHOD) {
                        //  std::clog << "basic_publish confirm1 ACK    : channel=" << frame.channel << std::endl;
                        if (basic_return) {
                          ret = PUBLISH_NO_CONFIRM;
                          // throw ::rabbitmq::exception ("basic_publish confirm 'return'");
                        }
                        break;
                     } else if (frame.payload.method.id == AMQP_BASIC_RETURN_METHOD) {
                        basic_return = true;
                        //  std::clog << "basic_publish confirm1 RETURN : channel=" << frame.channel << std::endl;
                     } else if (frame.payload.method.id == AMQP_CHANNEL_CLOSE_METHOD) {
                        //  std::clog << "basic_publish confirm1 CLOSE CHANNEL : channel=" << frame.channel << std::endl;
                       // throw ::rabbitmq::exception ("basic_publish confirm 'close channel'");
                        ret = PUBLISH_CLOSED_CHANNEL;
                     } else if (frame.payload.method.id == AMQP_CONNECTION_CLOSE_METHOD) {
                        //  std::clog << "basic_publish confirm1 CLOSE CONNECTION : channel=" << frame.channel << std::endl;
                       // throw ::rabbitmq::exception ("basic_publish confirm 'close connection'");
                        ret = PUBLISH_CLOSED_CONNECTION;
                     } else {
                        //  std::clog << "basic_publish confirm1 METHOD : channel=" << frame.channel << "  method_id=" << frame.payload.method.id << std::endl;
                        //throw ::rabbitmq::exception ("basic_publish confirm methode code : " + frame.payload.method.id);
                        ret = PUBLISH_ERROR;
                     }
                  }
                  if (frame.frame_type == AMQP_FRAME_HEADER) {
                     //  std::clog << "basic_publish confirm2 HEADER" << std::endl;
                  }
                  if (frame.frame_type == AMQP_FRAME_BODY) {
                     //  std::clog << "basic_publish confirm3 BODY" << std::endl;
                  }
               }
            }
         }
      } else {
         throw ::rabbitmq::exception ("basic_publish channel isn't ok");
      }
      return ret;
   }

   void channel::impl::basic_consume (const std::string & queue_,
                                      const std::string & consumer_tag_,
                                      //const bool &        no_local_,
                                      const bool &        no_ack_,
                                      const bool &        exclusive_)
   {
      if (_channel_ok_) {
         if (not _consuming_) {
            amqp_basic_consume (_amqp_con_,
                                _amqp_ch_,
                                str_to_amqp (queue_),
                                str_to_amqp (consumer_tag_),
                                0, //no_local_,
                                no_ack_,
                                exclusive_,
                                amqp_empty_table);  // todo args
            amqp_rpc_reply_t reply = amqp_get_rpc_reply (_amqp_con_);
            if (reply.reply_type == AMQP_RESPONSE_NORMAL) {
               _acknowledge_ = not no_ack_;
            } else {
               throw ::rabbitmq::exception ("basic_consume failure");
               // todo precisions
            }
         }
      } else {
         throw ::rabbitmq::exception ("no channel for basic_consume");
      }
   }

   consume_status_type
   channel::impl::consume_message (std::string &      msg_,
                                   std::string &      routing_key_,
                                   basic_properties & props_,
                                   uint64_t &         delivery_tag_,
                                   const float &      timeout_sec_)
   {
     consume_status_type ret = CONSUME_OK;
      if (_channel_ok_) {
         if (not _consuming_) {
            bool             is_timeout = false;
            struct timeval*  p_timeout  = NULL;
            struct timeval   timeout;
            amqp_rpc_reply_t res;
            amqp_envelope_t  envelope;
            if (timeout_sec_ > 0) {
               timeout.tv_sec  = (int) timeout_sec_;
               timeout.tv_usec = (int) ((timeout_sec_ - timeout.tv_sec) * 1000.0) / 1000;
               p_timeout = &timeout;
            }
            amqp_maybe_release_buffers (_amqp_con_);
            res = amqp_consume_message (_amqp_con_, &envelope, p_timeout, 0);
            if (AMQP_RESPONSE_NORMAL != res.reply_type) {
               std::cerr << "ERROR consume message unexpected reply type : " << res.reply_type << std::endl;
               std::cerr << "                                 lib err    : " << std::to_string (res.library_error) << std::endl;
               std::cerr << "                                 lib err    : " << amqp_error_string2 (res.library_error) << std::endl;
               if (res.library_error == -13) {
                 is_timeout = true;
               } else {
                 ret = CONSUME_ERROR;
               }
            }
            if (envelope.channel != _amqp_ch_) {
               std::cerr << "ERROR consume message unexpected channel num: " << envelope.channel << std::endl;
               ret = CONSUME_BAD_CHANNEL;
            }
            delivery_tag_ = envelope.delivery_tag,
            routing_key_  = str_from_amqp   (envelope.routing_key);
            props_        = props_from_amqp (envelope.message.properties);
            msg_          = str_from_amqp   (envelope.message.body);
            if (is_timeout) {
              ret = CONSUME_TIMEOUT;
            }
            amqp_destroy_envelope (&envelope);
         }
      } else {
        ret = CONSUME_MISSING_CHANNEL;
        // throw ::rabbitmq::exception ("no channel for consume_message");
      }
      return ret;
   }

   void channel::impl::basic_ack (const uint64_t & delivery_tag_,
                                  const bool &     multiple_)
   {
      if (_channel_ok_) {
         if (_acknowledge_) {
            int err = amqp_basic_ack (_amqp_con_, _amqp_ch_, delivery_tag_, multiple_);
            if (err != AMQP_STATUS_OK) {
               throw ::rabbitmq::exception ("basic_ack failure");
               // todo precisions
            }
         }
      } else {
         throw ::rabbitmq::exception ("no channel for basic_ack");
      }
   }

   void channel::impl::basic_qos (const uint16_t & prefetch_count_)
   {
      if (_channel_ok_) {
         amqp_basic_qos_ok_t* ok = amqp_basic_qos (_amqp_con_, _amqp_ch_, 0, prefetch_count_, 0);
         if (not ok) {
            throw ::rabbitmq::exception ("basic_qos failure");
            // todo precisions
         }
      } else {
         throw ::rabbitmq::exception ("no channel for basic_qos");
      }
   }

   void channel::impl::start_consuming (const msg_consume_func & callback_)
   {
      if (_channel_ok_) {
         if (not _consuming_) {
            _consuming_ = fork ();
            if (_consuming_ == 0) {
               std::string      msg;
               std::string      routing_key;
               basic_properties props;
               uint64_t         delivery_tag;
               while (1) {
                  consume_message (msg, routing_key, props, delivery_tag, -1.0);
                  callback_       (msg, routing_key, props);
                  if (_acknowledge_) basic_ack (delivery_tag, false);
               }
            }
         }
      } else {
         throw ::rabbitmq::exception ("no channel for start_consuming");
      }
   }

   void channel::impl::stop_consuming ()
   {
      if (_channel_ok_) {
         if (_consuming_) {
            kill (_consuming_, SIGKILL);
            _consuming_ = 0;
         }
      } else {
         throw ::rabbitmq::exception ("no channel for start_consuming");
      }
   }

   /////////////////////////////////////////////////////////////////////////////////////////////////

} // end of namespace rabbitmq
