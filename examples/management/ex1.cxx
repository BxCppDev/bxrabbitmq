#include <string>
#include <sstream>
#include <iostream>

#include "rabbitmq/rabbit_mgr.h"

int main ()
{
   std::clog << "\nrabbit_mgr: ex1 \n" ;
   rabbitmq::rabbit_mgr mgr ("localhost", 15672, "guest", "guest");
   mgr.test ();
   delete mgr;
   return 0;
}
