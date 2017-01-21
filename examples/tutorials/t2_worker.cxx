
// Standard library:
#include <iostream>
#include <unistd.h>

//
#include "rabbitmq/parameters.h"
#include "rabbitmq/connection.h"
#include "rabbitmq/channel.h"

void worker ();

int main (void)
{
  int error_code = EXIT_SUCCESS;
  try {
    worker ();
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
   sleep (msg_.size ());
   std::clog << " [x] Done " << std::endl;
   // if no_ack was set to false (basic_consume) : acknowledge will be done automatically after this
}

void worker ()
{
   std::clog << "\nTUTORIAL 2 : 'Work queues' - worker\n\n" ;
   rabbitmq::connection_parameters c_par;
   rabbitmq::connection            con (c_par);
   if (con.is_ok ()) {
      rabbitmq::channel &        chan = con.grab_channel ();
      std::string                routing_key;
      std::string                message;
      rabbitmq::basic_properties props;
      rabbitmq::queue_parameters q_par;
      q_par.name    = "task_queue";
      q_par.durable = true;
      chan.queue_declare (q_par);
      chan.basic_qos     (1);
      chan.basic_consume ("task_queue");   // no_ack = false
      std::clog << " [*] Waiting for messages. Press Return to exit." << std::endl;
      chan.start_consuming (&my_callback);
      std::cin.ignore      ();
      chan.stop_consuming  ();
   } else {
      std::cerr << "fail to connect ..." << std::endl;
   }
   return;
}



