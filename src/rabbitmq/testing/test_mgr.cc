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
      bool             ok;
      error_response   error;
      vhost::list      vhosts;
      exchange::list   exchanges;
      queue::list      queues;
      user::list       users;
      permission       user_perm;
      permission::list user_perms;

      std::clog << "\n== list vhosts =================" << std::endl;
      ok = mgr.list_vhosts (vhosts, error);
      if (ok) {
         for (vhost::list::iterator iter = vhosts.begin(); iter != vhosts.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== add vhost /foo =================\n" << std::endl;
      ok = mgr.add_vhost ("/foo", error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n= list vhosts =================" << std::endl;
      ok = mgr.list_vhosts (vhosts, error);
      if (ok) {
         for (vhost::list::iterator iter = vhosts.begin(); iter != vhosts.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== delete vhost /foo =================" << std::endl;
      ok = mgr.delete_vhost ("/foo", error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== list vhosts =================" << std::endl;
      ok = mgr.list_vhosts (vhosts, error);
      if (ok) {
         for (vhost::list::iterator iter = vhosts.begin(); iter != vhosts.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }


      std::clog << "\n== list exchanges on '/' =================" << std::endl;
      ok = mgr.list_exchanges ("/", exchanges, error);
      if (ok) {
         for (exchange::list::iterator iter = exchanges.begin(); iter != exchanges.end(); iter++) {
            std::clog << (*iter).name << "  " << (*iter).type << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== exchange declare 'testX' on '/' =================" << std::endl;
      ok = mgr.exchange_declare ("testX", "/", "direct", true, false, false, error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== list exchanges on '/' =================" << std::endl;
      ok = mgr.list_exchanges ("/", exchanges, error);
      if (ok) {
         for (exchange::list::iterator iter = exchanges.begin(); iter != exchanges.end(); iter++) {
            std::clog << (*iter).name << "  " << (*iter).type << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== delete exchange 'testX' on '/' =================" << std::endl;
      ok = mgr.delete_exchange ("testX", "/", error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== list exchanges on '/' =================" << std::endl;
      ok = mgr.list_exchanges ("/", exchanges, error);
      if (ok) {
         for (exchange::list::iterator iter = exchanges.begin(); iter != exchanges.end(); iter++) {
            std::clog << (*iter).name << "  " << (*iter).type << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== list queues on '/' =================" << std::endl;
      ok = mgr.list_queues ("/", queues, error);
      if (ok) {
         for (queue::list::iterator iter = queues.begin(); iter != queues.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== queue declare 'testQ' on '/' =================" << std::endl;
      ok = mgr.queue_declare ("testQ", "/", true, false, error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== list queues on '/' =================" << std::endl;
      ok = mgr.list_queues ("/", queues, error);
      if (ok) {
         for (queue::list::iterator iter = queues.begin(); iter != queues.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== delete queue 'testQ' on '/' =================" << std::endl;
      ok = mgr.delete_queue ("testQ", "/", error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== list queues on '/' =================" << std::endl;
      ok = mgr.list_queues ("/", queues, error);
      if (ok) {
         for (queue::list::iterator iter = queues.begin(); iter != queues.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== list users =================" << std::endl;
      ok = mgr.list_users (users, error);
      if (ok) {
         for (user::list::iterator iter = users.begin(); iter != users.end(); iter++) {
            std::clog << (*iter).name << "   [" << (*iter).tags << "]" << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== add user Zappa =================" << std::endl;
      ok = mgr.add_user ("Zappa", "Freakout", error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== list users =================" << std::endl;
      ok = mgr.list_users (users, error);
      if (ok) {
         for (user::list::iterator iter = users.begin(); iter != users.end(); iter++) {
            std::clog << (*iter).name << "   [" << (*iter).tags << "]" << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== delete user Zappa =================" << std::endl;
      ok = mgr.delete_user ("Zappa", error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== list users =================" << std::endl;
      ok = mgr.list_users (users, error);
      if (ok) {
         for (user::list::iterator iter = users.begin(); iter != users.end(); iter++) {
            std::clog << (*iter).name << "   [" << (*iter).tags << "]" << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== user 'guest' permissions =================" << std::endl;
      ok = mgr.user_permissions ("guest", user_perms, error);
      if (ok) {
         for (permission::list::iterator iter = user_perms.begin(); iter != user_perms.end(); iter++) {
            std::clog << (*iter).vhost << " =>  "  << (*iter).configure << "  " << (*iter).write << "  " << (*iter).read << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== user 'guest' permission on '/' =================" << std::endl;
      ok = mgr.user_permission ("guest", "/", user_perm, error);
      if (ok) {
         std::clog << "  " << user_perm.configure << "  " << user_perm.write << "  " << user_perm.read << std::endl;
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      return;
    }

  } // end of namespace testing

} // end of namespace rabbitmq
