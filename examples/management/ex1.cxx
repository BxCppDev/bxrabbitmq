#include <string>
#include <sstream>
#include <iostream>

#include "rabbitmq/config.h"
#if BXRABBITMQ_WITH_MANAGER == 0
#error BxRabbitMQ has no management support
#endif // BXRABBITMQ_WITH_MANAGER
#include "rabbitmq/rabbit_mgr.h"

int main ()
{
   std::clog << "\nrabbit_mgr: ex1 \n" ;
   rabbitmq::rabbit_mgr mgr ("localhost", 15672, "guest", "guest");
   mgr.test ();
   return 0;
}
