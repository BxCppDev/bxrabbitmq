#include <iostream>

// Ourselves:
#include "parameters.h"


namespace rabbitmq {

   const std::string & connection_parameters::default_host ()
   {
      static const std::string def ("localhost");
      return def;
   }

   const std::uint16_t connection_parameters::default_port ()
   {
      static const uint16_t    def (5672);
      return def;
   }

   const std::string & connection_parameters::default_vhost ()
   {
      static const std::string def ("/");
      return def;
   }

   const std::string & connection_parameters::default_login ()
   {
      static const std::string def ("guest");
      return def;
   }

   const std::string & connection_parameters::default_passwd ()
   {
      static const std::string def ("guest");
      return def;
   }

   connection_parameters::connection_parameters ()
   {
      host        = default_host   ();
      port        = default_port   ();
      vhost       = default_vhost  ();
      login       = default_login  ();
      passwd      = default_passwd ();
      return;
   }

} // end of namespace rabbitmq
