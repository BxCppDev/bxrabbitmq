// Ourselves:
#include <rabbitmq/testing/test_mgr.h>

// Standard library:
#include <unistd.h>
#include <iostream>

// This project:
#include <rabbitmq/connection.h>
#include <rabbitmq/channel.h>
#include <rabbitmq/parameters.h>
#include <rabbitmq/rabbit_mgr.h>

namespace rabbitmq {

  namespace testing {

    // static
    void test_mgr::run_test_0 ()     //  rabbit management
    {
      std::clog << "\nrabbitmq::testing::test_mgr::run_test_0: \n" ;
      rabbit_mgr mgr ("localhost", 15672, "guest", "guest");
      //
      bool           ok;
      error_response error;
      vhost::list    vhosts;
      exchange::list exchanges;

      std::clog << "== T1 =================" << std::endl;
      ok = mgr.get_vhosts (vhosts, error);
      if (ok) {
         std::clog << "vhosts list : " << std::endl;
         for (vhost::list::iterator iter = vhosts.begin(); iter != vhosts.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << "vhosts list error : " << error.what << "  " << error.why << std::endl;
      }

      std::clog << "== T2 =================" << std::endl;
      ok = mgr.create_vhost ("/foo", error);
      if (ok) {
         std::clog << "create vhost /foo" << std::endl;
      } else {
         std::cerr << "create vhost error : " << error.what << "  " << error.why << std::endl;
      }

      std::clog << "== T1 =================" << std::endl;
      ok = mgr.get_vhosts (vhosts, error);
      if (ok) {
         std::clog << "vhosts list : " << std::endl;
         for (vhost::list::iterator iter = vhosts.begin(); iter != vhosts.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << "vhosts list error : " << error.what << "  " << error.why << std::endl;
      }

      std::clog << "== T3 =================" << std::endl;
      ok = mgr.delete_vhost ("/foo", error);
      if (ok) {
         std::clog << "delete vhost /foo" << std::endl;
      } else {
         std::cerr << "delete vhost error : " << error.what << "  " << error.why << std::endl;
      }

      std::clog << "== T1 =================" << std::endl;
      ok = mgr.get_vhosts (vhosts, error);
      if (ok) {
         std::clog << "vhosts list : " << std::endl;
         for (vhost::list::iterator iter = vhosts.begin(); iter != vhosts.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << "vhosts list error : " << error.what << "  " << error.why << std::endl;
      }


      std::clog << "== T4 =================" << std::endl;
      ok = mgr.get_exchanges ("/", exchanges, error);
      if (ok) {
         std::clog << "/ exchanges list : " << std::endl;
         for (exchange::list::iterator iter = exchanges.begin(); iter != exchanges.end(); iter++) {
            std::clog << (*iter).name << "  " << (*iter).type << std::endl;
         }
      } else {
         std::cerr << "exchanges list error : " << error.what << "  " << error.why << std::endl;
      }

      std::clog << "== T5 =================" << std::endl;
      ok = mgr.create_exchange ("testex", "/", "direct", true, false, false, error);
      if (ok) {
         std::clog << "create exchange 'testex' in '/' " << std::endl;
      } else {
         std::cerr << "create exchange error : " << error.what << "  " << error.why << std::endl;
      }

      std::clog << "== T4 =================" << std::endl;
      ok = mgr.get_exchanges ("/", exchanges, error);
      if (ok) {
         std::clog << "/ exchanges list : " << std::endl;
         for (exchange::list::iterator iter = exchanges.begin(); iter != exchanges.end(); iter++) {
            std::clog << (*iter).name << "  " << (*iter).type << std::endl;
         }
      } else {
         std::cerr << "exchanges list error : " << error.what << "  " << error.why << std::endl;
      }

      std::clog << "== T6 =================" << std::endl;
      ok = mgr.delete_exchange ("testex", "/", error);
      if (ok) {
         std::clog << "delete exchange 'testex' in '/' " << std::endl;
      } else {
         std::cerr << "delete exchange error : " << error.what << "  " << error.why << std::endl;
      }

      std::clog << "== T4 =================" << std::endl;
      ok = mgr.get_exchanges ("/", exchanges, error);
      if (ok) {
         std::clog << "/ exchanges list : " << std::endl;
         for (exchange::list::iterator iter = exchanges.begin(); iter != exchanges.end(); iter++) {
            std::clog << (*iter).name << "  " << (*iter).type << std::endl;
         }
      } else {
         std::cerr << "exchanges list error : " << error.what << "  " << error.why << std::endl;
      }

      return;
    }

  } // end of namespace testing

} // end of namespace rabbitmq
