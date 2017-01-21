
// Standard library:
#include <iostream>
#include <unistd.h>
#include <signal.h>

//
#include "rabbitmq/parameters.h"
#include "rabbitmq/connection.h"
#include "rabbitmq/channel.h"

void rpc_server ();

int main (void)
{
  int error_code = EXIT_SUCCESS;
  try {
    rpc_server ();
  } catch (std::exception & x) {
    std::cerr << "ERROR: " << x.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "ERROR: " << "Unexpected exception!" << std::endl;
    error_code = EXIT_FAILURE;
  }
  return error_code;
}

long int fibo (int n) {
   int      i;
   long int f1 = 0;
   long int f2 = 1;
   long int f3 = 1;
   if (n < 1) return 0;
   if (n < 3) return 1;
   for (i=2; i<=n; i++) {
      f3 = f1 + f2;
      f1 = f2;
      f2 = f3;
   }
   return f3;
}

void rpc_server ()
{
   std::clog << "\nTUTORIAL 6 : 'RPC' - rpc server\n\n" ;
   rabbitmq::connection_parameters c_par;
   rabbitmq::connection            con (c_par);
   if (con.is_ok ()) {
      int                        num;
      long int                   fib;
      rabbitmq::channel &        chan = con.grab_channel ();
      std::string                routing_key;
      std::string                request;
      uint64_t                   delivery;
      rabbitmq::basic_properties prop_in;
      rabbitmq::basic_properties prop_out;
      rabbitmq::queue_parameters q_par;
      q_par.name = "rpc_queue";
      chan.queue_declare (q_par);
      chan.basic_qos     (1);
      chan.basic_consume ("rpc_queue");
      std::clog << " [x] Awaiting RPC requests. Press return to exit." << std::endl;

      pid_t  service_pid = fork ();
      if (service_pid == 0) {
         while (1) {
            chan.consume_message (request, routing_key, prop_in, delivery);
            if (not prop_in.has_correlation_id () or not prop_in.has_reply_to ()) {
               chan.basic_ack (delivery);
               continue;
            }
            num = std::stoi (request); // todo try
            fib = fibo (num);
            prop_out.set_correlation_id (prop_in.get_correlation_id ());
            chan.basic_publish          ("", prop_in.get_reply_to (), std::to_string (fib), prop_out);
            chan.basic_ack              (delivery);
            std::clog << " [.] fib (" << num << ")" << std::endl;
         }
      } else {
         std::cin.ignore ();
         kill            (service_pid, SIGKILL);
      }

   } else {
      std::cerr << "fail to connect ..." << std::endl;
   }
   return;
}



