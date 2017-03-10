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
      queue::list    queues;
      user::list     users;

      std::clog << "== T1 =================" << std::endl;
      ok = mgr.list_vhosts (vhosts, error);
      if (ok) {
         std::clog << "vhosts list : " << std::endl;
         for (vhost::list::iterator iter = vhosts.begin(); iter != vhosts.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << "vhosts list error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "== T2 =================" << std::endl;
      ok = mgr.add_vhost ("/foo", error);
      if (ok) {
         std::clog << "create vhost /foo" << std::endl;
      } else {
         std::cerr << "create vhost error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "== T1 =================" << std::endl;
      ok = mgr.list_vhosts (vhosts, error);
      if (ok) {
         std::clog << "vhosts list : " << std::endl;
         for (vhost::list::iterator iter = vhosts.begin(); iter != vhosts.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << "vhosts list error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "== T3 =================" << std::endl;
      ok = mgr.delete_vhost ("/foo", error);
      if (ok) {
         std::clog << "delete vhost /foo" << std::endl;
      } else {
         std::cerr << "delete vhost error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "== T1 =================" << std::endl;
      ok = mgr.list_vhosts (vhosts, error);
      if (ok) {
         std::clog << "vhosts list : " << std::endl;
         for (vhost::list::iterator iter = vhosts.begin(); iter != vhosts.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << "vhosts list error : " << error.error << "  " << error.reason << std::endl;
      }


      std::clog << "== T4 =================" << std::endl;
      ok = mgr.list_exchanges ("/", exchanges, error);
      if (ok) {
         std::clog << "/ exchanges list : " << std::endl;
         for (exchange::list::iterator iter = exchanges.begin(); iter != exchanges.end(); iter++) {
            std::clog << (*iter).name << "  " << (*iter).type << std::endl;
         }
      } else {
         std::cerr << "exchanges list error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "== T5 =================" << std::endl;
      ok = mgr.exchange_declare ("testex", "/", "direct", true, false, false, error);
      if (ok) {
         std::clog << "create exchange 'testex' in '/' " << std::endl;
      } else {
         std::cerr << "create exchange error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "== T4 =================" << std::endl;
      ok = mgr.list_exchanges ("/", exchanges, error);
      if (ok) {
         std::clog << "/ exchanges list : " << std::endl;
         for (exchange::list::iterator iter = exchanges.begin(); iter != exchanges.end(); iter++) {
            std::clog << (*iter).name << "  " << (*iter).type << std::endl;
         }
      } else {
         std::cerr << "exchanges list error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "== T6 =================" << std::endl;
      ok = mgr.delete_exchange ("testex", "/", error);
      if (ok) {
         std::clog << "delete exchange 'testex' in '/' " << std::endl;
      } else {
         std::cerr << "delete exchange error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "== T4 =================" << std::endl;
      ok = mgr.list_exchanges ("/", exchanges, error);
      if (ok) {
         std::clog << "/ exchanges list : " << std::endl;
         for (exchange::list::iterator iter = exchanges.begin(); iter != exchanges.end(); iter++) {
            std::clog << (*iter).name << "  " << (*iter).type << std::endl;
         }
      } else {
         std::cerr << "exchanges list error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "== T7 =================" << std::endl;
      ok = mgr.list_queues ("/", queues, error);
      if (ok) {
         std::clog << "/ queues list : " << std::endl;
         for (queue::list::iterator iter = queues.begin(); iter != queues.end(); iter++) {
            //std::clog << (*iter).name << "  " << (*iter).type << std::endl;
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << "queues list error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "== T8 =================" << std::endl;
      ok = mgr.queue_declare ("testQ", "/", true, false, error);
      if (ok) {
         std::clog << "create queue 'testQ' in '/' " << std::endl;
      } else {
         std::cerr << "create queue error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "== T7 =================" << std::endl;
      ok = mgr.list_queues ("/", queues, error);
      if (ok) {
         std::clog << "/ queues list : " << std::endl;
         for (queue::list::iterator iter = queues.begin(); iter != queues.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << "queues list error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "== T9 =================" << std::endl;
      ok = mgr.delete_queue ("testQ", "/", error);
      if (ok) {
         std::clog << "delete queue 'testQ' in '/' " << std::endl;
      } else {
         std::cerr << "delete queue error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "== T7 =================" << std::endl;
      ok = mgr.list_queues ("/", queues, error);
      if (ok) {
         std::clog << "/ queues list : " << std::endl;
         for (queue::list::iterator iter = queues.begin(); iter != queues.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << "queues list error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "== T10 =================" << std::endl;
      ok = mgr.list_users (users, error);
      if (ok) {
         std::clog << "users list : " << std::endl;
         for (user::list::iterator iter = users.begin(); iter != users.end(); iter++) {
            std::clog << (*iter).name << " - " << (*iter).tags << " - " << std::endl;
         }
      } else {
         std::cerr << "users list error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "== T11 =================" << std::endl;
      ok = mgr.add_user ("zappa", "freakout", error);
      if (ok) {
         std::clog << "add user 'Zappa' " << std::endl;
      } else {
         std::cerr << "add user error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "== T10 =================" << std::endl;
      ok = mgr.list_users (users, error);
      if (ok) {
         std::clog << "users list : " << std::endl;
         for (user::list::iterator iter = users.begin(); iter != users.end(); iter++) {
            std::clog << (*iter).name << " - " << (*iter).tags << " - " << std::endl;
         }
      } else {
         std::cerr << "users list error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "== T12 =================" << std::endl;
      ok = mgr.delete_user ("zappa", error);
      if (ok) {
         std::clog << "delete user 'Zappa' " << std::endl;
      } else {
         std::cerr << "delete user error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "== T10 =================" << std::endl;
      ok = mgr.list_users (users, error);
      if (ok) {
         std::clog << "users list : " << std::endl;
         for (user::list::iterator iter = users.begin(); iter != users.end(); iter++) {
            std::clog << (*iter).name << " - " << (*iter).tags << " - " << std::endl;
         }
      } else {
         std::cerr << "users list error : " << error.error << "  " << error.reason << std::endl;
      }

      return;
    }

  } // end of namespace testing

} // end of namespace rabbitmq
