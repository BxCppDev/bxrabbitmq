
// Standard library:
#include <iostream>

//
#include "rabbitmq/parameters.h"
#include "rabbitmq/connection.h"
#include "rabbitmq/channel.h"

void receive ();

int main (void)
{
  int error_code = EXIT_SUCCESS;
  try {
    receive ();
  } catch (std::exception & x) {
    std::cerr << "ERROR: " << x.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "ERROR: " << "Unexpected exception!" << std::endl;
    error_code = EXIT_FAILURE;
  }
  return error_code;
}

void my_callback (std::string & msg_, std::string & rkey_, rabbitmq::basic_properties & props_) {
   std::clog << " [x] Received " << msg_ << std::endl;
}

void receive ()
{
   std::clog << "\nTUTORIAL 1 : 'Hello World' - receive\n\n" ;
   rabbitmq::connection_parameters c_par;
   c_par.host   = "localhost";
   c_par.port   = 5672;
   c_par.login  = "guest";
   c_par.passwd = "guest";
   rabbitmq::connection            con (c_par);
   if (con.is_ok ()) {
      std::string                routing_key;
      std::string                message;
      rabbitmq::basic_properties props;
      rabbitmq::channel &        chan = con.grab_channel ();
      rabbitmq::queue_parameters q_par;
      q_par.name = "hello";
      chan.queue_declare (q_par);
      chan.basic_consume ("hello", "", true);  // consumer_tag = "", no_ack = true
      std::clog << " [*] Waiting for messages. Press Return to exit." << std::endl;
      chan.start_consuming (&my_callback);
      std::cin.ignore      ();
      chan.stop_consuming  ();
   } else {
      std::cerr << "fail to connect ..." << std::endl;
   }
   return;
}



