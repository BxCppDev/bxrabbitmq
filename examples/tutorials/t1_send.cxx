
// Standard library:
#include <iostream>

//
#include "rabbitmq/parameters.h"
#include "rabbitmq/connection.h"
#include "rabbitmq/channel.h"

void send ();

int main (void)
{
  int error_code = EXIT_SUCCESS;
  try {
    send ();
  } catch (std::exception & x) {
    std::cerr << "ERROR: " << x.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "ERROR: " << "Unexpected exception!" << std::endl;
    error_code = EXIT_FAILURE;
  }
  return error_code;
}

void send ()
{
   std::clog << "\nTUTORIAL 1 : 'Hello World' - send\n\n" ;
   rabbitmq::connection_parameters c_par;
   c_par.host   = "caerabbitmq.in2p3.fr";
   c_par.port   = 5671;
   c_par.login  = "guest";
   c_par.passwd = "guest";
   rabbitmq::connection            con (c_par);
   if (con.is_ok ()) {
      rabbitmq::channel &        chan = con.grab_channel ();
      rabbitmq::queue_parameters q_par;
      q_par.name = "hello";
      chan.queue_declare (q_par);
      chan.basic_publish ("", "hello", "Hello World!");
      std::clog << " [x] Sent 'Hello World!'" << std::endl;
   } else {
      std::cerr << "fail to connect ..." << std::endl;
   }
   return;
}



