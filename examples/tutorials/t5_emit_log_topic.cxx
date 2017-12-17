
// Standard library:
#include <iostream>

//
#include "rabbitmq/parameters.h"
#include "rabbitmq/connection.h"
#include "rabbitmq/channel.h"

void emit_log_topic (const std::string routing_key_, const std::string message_);

int main (int argc, char** argv)
{
  int error_code = EXIT_SUCCESS;
  try {
    if (argc > 2) {
      emit_log_topic (argv [1], argv [2]);
    } else if (argc > 1) {
      emit_log_topic ("anonymous.info", argv [1]);
    } else {
      emit_log_topic ("anonymous.info", "Hello World!");
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

void emit_log_topic (const std::string routing_key_, const std::string message_)
{
   std::clog << "\nTUTORIAL 5 : 'Topics' - emit log topic\n\n" ;
   const bool                      publisher_confirm = true;
   rabbitmq::connection_parameters c_par;
   rabbitmq::connection            con (c_par, publisher_confirm);
   if (con.is_ok ()) {
      rabbitmq::channel &           chan = con.grab_channel ();
      rabbitmq::exchange_parameters x_par;
      x_par.name = "topic_logs";
      x_par.type = "topic";
      chan.exchange_declare (x_par);
      chan.basic_publish ("topic_logs", routing_key_, message_);
      std::clog << " [x] Sent " << routing_key_ << ":" << message_ << std::endl;
   } else {
      std::cerr << "fail to connect ..." << std::endl;
   }
   return;
}



