#include <string>
#include <sstream>
#include <iostream>

#include "rabbitmq/config.h"
#if BXRABBITMQ_WITH_MANAGER == 0
#error BxRabbitMQ has no management support
#endif // BXRABBITMQ_WITH_MANAGER

#include "rabbitmq/management.h"
#include "rabbitmq/rabbit_mgr.h"

int main ()
{
   std::clog << "\nrabbit_mgr: ex1 \n" ;
   bool                     ok;
   rabbitmq::error_response error;
   rabbitmq::vhost::list    vhosts;
   rabbitmq::rabbit_mgr     mgr ("localhost", 15671, "admin", "what");

   ok = mgr.list_vhosts (vhosts, error);
   if (ok) {
      std::clog << "vhosts list : " << std::endl;
      for (rabbitmq::vhost::list::iterator iter = vhosts.begin(); iter != vhosts.end(); iter++) {
         std::clog << (*iter).name << std::endl;
      }
   } else {
      std::cerr << "vhosts list error : " << error.error << "  " << error.reason << std::endl;
   }
   return 0;
}
