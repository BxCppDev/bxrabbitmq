// -*- mode: c++; -*-

#ifndef BXRABBITMQ_PARAMETERS_H
#define BXRABBITMQ_PARAMETERS_H

namespace rabbitmq {


  /// \brief Connection parameters to a RabbitMQ server
  struct connection_parameters
  {

     std::string  host;
     uint16_t     port;
     std::string  vhost;
     std::string  login;
     std::string  passwd;

     connection_parameters ();

     static const std::string  & default_host   ();
     static const uint16_t       default_port   ();
     static const std::string  & default_vhost  ();
     static const std::string  & default_login  ();
     static const std::string  & default_passwd ();
  };

  /// \brief RabbitMQ exchange parameters
  struct exchange_parameters
  {
     std::string name        = "";
     std::string type        = "";
     bool        passive     = false;
     bool        durable     = false;
     bool        auto_delete = false;
     bool        internal    = false;
     bool        nowait      = false;
     // todo arguments

     //exchange_parameters ();
  };

  /// \brief RabbitMQ queue parameters
  struct queue_parameters
  {
     std::string name        = "";
     bool        passive     = false;
     bool        durable     = false;
     bool        exclusive   = false;
     bool        auto_delete = false;
     bool        nowait      = false;
     // todo arguments

     //queue_parameters ();
  };

} // end of namespace rabbitmq

#endif // BXRABBITMQ_PARAMETERS_H
