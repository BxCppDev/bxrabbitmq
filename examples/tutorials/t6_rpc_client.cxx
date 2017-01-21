
// Standard library:
#include <iostream>
#include <cstdlib>

//
#include "rabbitmq/parameters.h"
#include "rabbitmq/connection.h"
#include "rabbitmq/channel.h"

void rpc_client (const unsigned int num);

int main (int argc, char** argv)
{
  int error_code = EXIT_SUCCESS;
  try {
    if (argc > 1) {
      rpc_client (std::stoi (argv [1]));
    } else {
       std::cerr << "usage : " << argv [0] << " unsigned_int_value" << std::endl;
       return EXIT_FAILURE;
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

void rpc_client (const unsigned int num)
{
   std::clog << "\nTUTORIAL 6 : 'RPC' - rpc client\n\n" ;
   rabbitmq::connection_parameters c_par;
   rabbitmq::connection            con (c_par);
   if (con.is_ok ()) {
      rabbitmq::channel &          chan = con.grab_channel ();
      std::string                  routing_key;
      std::string                  response;
      uint64_t                     delivery;
      rabbitmq::basic_properties   prop_out;
      rabbitmq::basic_properties   prop_in;
      rabbitmq::queue_parameters   q_par;
      q_par.name      = "";
      q_par.exclusive = true;
      chan.queue_declare          (q_par);
      chan.basic_consume          (q_par.name, "", true);
      prop_out.set_correlation_id ("corid_" + std::to_string (std::rand ()));
      prop_out.set_reply_to       (q_par.name);
      chan.basic_publish          ("", "rpc_queue", std::to_string (num), prop_out);
      std::clog << " [x] Requesting Fibo (" << num << ")" << std::endl;
      while (1) {
         chan.consume_message (response, routing_key, prop_in, delivery);
         if (not prop_in.has_correlation_id ()) continue;
         if (prop_in.get_correlation_id () == prop_out.get_correlation_id ()) break;
      }
      std::clog << " [x] Got " << response << std::endl;
   } else {
      std::cerr << "fail to connect ..." << std::endl;
   }
   return;
}



