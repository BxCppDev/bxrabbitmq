
// Standard library:
#include <iostream>

//
#include "rabbitmq/parameters.h"
#include "rabbitmq/connection.h"
#include "rabbitmq/channel.h"

void new_task (const std::string task_cmd_);

int main (int argc, char** argv)
{
  int error_code = EXIT_SUCCESS;
  try {
    if (argc > 1) {
      new_task (argv [1]);
    } else {
      new_task ("Hello_World!");
    }
  } catch (std::exception & x) {
    std::cerr << "ERROR: " << x.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "ERROR: " << "Unexpected exception!" << std::endl;
    error_code = EXIT_FAILURE;
  }
  return error_code;
}

void new_task (const std::string task_cmd_)
{
   std::clog << "\nTUTORIAL 2 : 'Work queues' - new task\n\n" ;
   rabbitmq::connection_parameters c_par;
   rabbitmq::connection            con (c_par);
   if (con.is_ok ()) {
      rabbitmq::channel &        chan = con.grab_channel ();
      rabbitmq::basic_properties props;
      rabbitmq::queue_parameters q_par;
      q_par.name    = "task_queue";
      q_par.durable = true;
      chan.queue_declare (q_par);
      props.set_delivery_mode (2);
      chan.basic_publish ("", "task_queue", task_cmd_, props);
      std::clog << " [x] Sent '" << task_cmd_ << "'" << std::endl;
   } else {
      std::cerr << "fail to connect ..." << std::endl;
   }
   return;
}



