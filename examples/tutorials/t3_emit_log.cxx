
// Standard library:
#include <iostream>

//
#include "rabbitmq/parameters.h"
#include "rabbitmq/connection.h"
#include "rabbitmq/channel.h"

void emit_log (const std::string log_msg_);

int main (int argc, char** argv)
{
  int error_code = EXIT_SUCCESS;
  try {
    if (argc > 1) {
      emit_log (argv [1]);
    } else {
      emit_log ("info: Hello_World!");
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

void emit_log (const std::string log_msg_)
{
   std::clog << "\nTUTORIAL 3 : 'Publish/Subscribe' - emit log\n\n" ;
   rabbitmq::connection_parameters c_par;
   rabbitmq::connection            con (c_par);
   if (con.is_ok ()) {
      rabbitmq::channel &           chan = con.grab_channel ();
      rabbitmq::exchange_parameters x_par;
      x_par.name = "logs";
      x_par.type = "fanout";
      chan.exchange_declare (x_par);
      chan.basic_publish ("logs", "", log_msg_);
      std::clog << " [x] Sent '" << log_msg_ << "'" << std::endl;
   } else {
      std::cerr << "fail to connect ..." << std::endl;
   }
   return;
}



