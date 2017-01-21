// -*- mode: c++; -*-

#ifndef BXRABBITMQ_RABBIT_MGR_H
#define BXRABBITMQ_RABBIT_MGR_H

//#include "parameters.h"
//#include "basic_properties.h"

namespace rabbitmq {

  /// \brief RabbitMQ Server remote management
  class rabbit_mgr
  {

     public:
        /// Constructor & co
        rabbit_mgr  (const std::string & server_host_,
                     const uint16_t      server_port_,
                     const std::string & user_login_,
                     const std::string & user_passwd_);
        //  Ctor & co : forbidden
        ~rabbit_mgr ();
        rabbit_mgr  ()                                      = delete;
        rabbit_mgr  (const rabbit_mgr & chan_)              = delete;
        rabbit_mgr & operator =  (const rabbit_mgr & chan_) = delete;
        //

        void test ();

     private:
        std::string  _server_host_;
        uint16_t     _server_port_;
        std::string  _user_login_;
        std::string  _user_passwd_;

  };

} // end of namespace rabbitmq

#endif // BXRABBITMQ_RABBIT_MGR_H
