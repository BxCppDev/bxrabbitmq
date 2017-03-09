// -*- mode: c++; -*-

#ifndef BXRABBITMQ_RABBIT_MGR_H
#define BXRABBITMQ_RABBIT_MGR_H

#include <curlpp/Easy.hpp>

#include "rabbitmq/management.h"

namespace rabbitmq {

  /// \brief RabbitMQ Server remote management
  class rabbit_mgr
  {

     public:
        static const uint16_t SSL_PORT = 15671;

     public:
        /// Constructor & co
        rabbit_mgr  (const std::string & server_host_,
                     const uint16_t      server_port_,
                     const std::string & user_login_,
                     const std::string & user_passwd_);
        //  Ctor & co : forbidden
        ~rabbit_mgr ();
        rabbit_mgr  ()                                     = delete;
        rabbit_mgr  (const rabbit_mgr & mgr_)              = delete;
        rabbit_mgr & operator =  (const rabbit_mgr & mgr_) = delete;
        //

        //  VHOSTS
        bool get_vhosts    (vhost::list       & vhosts_,
                            error_response    & error_);

        bool create_vhost  (const std::string & name_,
                            error_response    & error_);

        bool delete_vhost  (const std::string & name_,
                            error_response    & error_);

        //  EXCHANGES
        bool get_exchanges   (const std::string & vhost_,
                              exchange::list    & exchanges_,
                              error_response    & error_);

        bool create_exchange (const std::string & name_,
                              const std::string & vhost_,
                              const std::string & type_,
                              const bool          durable_,
                              const bool          auto_delete_,
                              const bool          internal_,
                              error_response    & error_);

        bool delete_exchange (const std::string & name_,
                              const std::string & vhost_,
                              error_response    & error_);

     private:
        std::string  _server_host_;
        uint16_t     _server_port_;
        std::string  _user_login_;
        std::string  _user_passwd_;

     private:
        void _request_setBaseOpts_ (curlpp::Easy      & request_,
                                    const std::string & cmd_,
                                    const std::string & custom_ = "POST",
                                    const bool          appli_  = false);


  };

} // end of namespace rabbitmq

#endif // BXRABBITMQ_RABBIT_MGR_H
