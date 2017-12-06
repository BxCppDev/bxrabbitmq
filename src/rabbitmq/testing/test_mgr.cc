// Ourselves:
#include <rabbitmq/testing/test_mgr.h>

// Standard library:
#include <unistd.h>
#include <iostream>

// This project:
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
      permissions      vh_user_perms;
      permissions::list user_perms;

      std::clog << "\n== list vhosts ==" << std::endl;
      ok = mgr.list_vhosts (vhosts, error);
      if (ok) {
         for (vhost::list::iterator iter = vhosts.begin(); iter != vhosts.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== add vhost /foo ==\n" << std::endl;
      ok = mgr.add_vhost ("/foo", error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n= list vhosts ==" << std::endl;
      ok = mgr.list_vhosts (vhosts, error);
      if (ok) {
         for (vhost::list::iterator iter = vhosts.begin(); iter != vhosts.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }


      std::clog << "\n== list exchanges on '/foo' ==" << std::endl;
      ok = mgr.list_exchanges ("/foo", exchanges, error);
      if (ok) {
         for (exchange::list::iterator iter = exchanges.begin(); iter != exchanges.end(); iter++) {
            std::clog << (*iter).name << "  " << (*iter).type << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== exchange declare 'testX' on '/foo' ==" << std::endl;
      ok = mgr.exchange_declare ("testX", "/foo", "direct", true, false, false, error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== list exchanges on '/foo' ==" << std::endl;
      ok = mgr.list_exchanges ("/foo", exchanges, error);
      if (ok) {
         for (exchange::list::iterator iter = exchanges.begin(); iter != exchanges.end(); iter++) {
            std::clog << (*iter).name << "  " << (*iter).type << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== list queues on '/foo' ==" << std::endl;
      ok = mgr.list_queues ("/foo", queues, error);
      if (ok) {
         for (queue::list::iterator iter = queues.begin(); iter != queues.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== queue declare 'testQ' on '/foo' ==" << std::endl;
      ok = mgr.queue_declare ("testQ", "/foo", true, false, error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== list queues on '/foo' ==" << std::endl;
      ok = mgr.list_queues ("/foo", queues, error);
      if (ok) {
         for (queue::list::iterator iter = queues.begin(); iter != queues.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== list users ==" << std::endl;
      ok = mgr.list_users (users, error);
      if (ok) {
         for (user::list::iterator iter = users.begin(); iter != users.end(); iter++) {
            std::clog << (*iter).name << "   [" << (*iter).tags << "]" << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== add user hommet ==" << std::endl;
      ok = mgr.add_user ("hommet", "BOBOB", error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== add user Zappa ==" << std::endl;
      ok = mgr.add_user ("Zappa", "Freakout", error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== list users ==" << std::endl;
      ok = mgr.list_users (users, error);
      if (ok) {
         for (user::list::iterator iter = users.begin(); iter != users.end(); iter++) {
            std::clog << (*iter).name << "   [" << (*iter).tags << "]" << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== set permissions 'conf_p' 'write_p' 'read_p' to 'Zappa' on '/' ==" << std::endl;
      ok = mgr.set_permissions ("Zappa", "/", "conf_p", "write_p", "read_p", error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== set permissions '.*' '.*' '.*' to 'Zappa' on '/foo' ==" << std::endl;
      ok = mgr.set_permissions ("Zappa", "/foo", ".*", ".*", ".*", error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== change Vistemboir password ==" << std::endl;
      ok = mgr.change_user_password ("Vistemboir", "Kseksa", error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== change Zappa password ==" << std::endl;
      ok = mgr.change_user_password ("Zappa", "Mothers", error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== change hommet password ==" << std::endl;
      ok = mgr.change_user_password ("hommet", "BOBOB", error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== user 'Zappa' permissions on '/foo' ==" << std::endl;
      ok = mgr.user_permissions ("Zappa", "/foo", vh_user_perms, error);
      if (ok) {
         std::clog << "  " << vh_user_perms.configure << "  " << vh_user_perms.write << "  " << vh_user_perms.read << std::endl;
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== user 'Zappa' permissions ==" << std::endl;
      ok = mgr.user_permissions ("Zappa", user_perms, error);
      if (ok) {
         for (permissions::list::iterator iter = user_perms.begin(); iter != user_perms.end(); iter++) {
            std::clog << (*iter).vhost << " =>  "  << (*iter).configure << "  " << (*iter).write << "  " << (*iter).read << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== delete user Zappa ==" << std::endl;
      ok = mgr.delete_user ("Zappa", error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== list users ==" << std::endl;
      ok = mgr.list_users (users, error);
      if (ok) {
         for (user::list::iterator iter = users.begin(); iter != users.end(); iter++) {
            std::clog << (*iter).name << "   [" << (*iter).tags << "]" << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== delete queue 'testQ' on '/foo' ==" << std::endl;
      ok = mgr.delete_queue ("testQ", "/foo", error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== list queues on '/foo' ==" << std::endl;
      ok = mgr.list_queues ("/foo", queues, error);
      if (ok) {
         for (queue::list::iterator iter = queues.begin(); iter != queues.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== delete exchange 'testX' on '/foo' ==" << std::endl;
      ok = mgr.delete_exchange ("testX", "/foo", error);
      if (!ok) {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== list exchanges on '/foo' ==" << std::endl;
      ok = mgr.list_exchanges ("/foo", exchanges, error);
      if (ok) {
         for (exchange::list::iterator iter = exchanges.begin(); iter != exchanges.end(); iter++) {
            std::clog << (*iter).name << "  " << (*iter).type << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      // std::clog << "\n== delete vhost /foo ==" << std::endl;
      // ok = mgr.delete_vhost ("/foo", error);
      // if (!ok) {
      //    std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      // }

      std::clog << "\n== list vhosts ==" << std::endl;
      ok = mgr.list_vhosts (vhosts, error);
      if (ok) {
         for (vhost::list::iterator iter = vhosts.begin(); iter != vhosts.end(); iter++) {
            std::clog << (*iter).name << std::endl;
         }
      } else {
         std::cerr << " Error : " << error.error << "  " << error.reason << std::endl;
      }

      std::clog << "\n== TEST ==" << std::endl;
      std::string tst;
      ok = mgr.test (tst);
      if (ok) {
         std::clog << "TEST : " << tst << std::endl;
      } else {
         std::cerr << "TEST Error : " << tst << std::endl;
      }

      return;
    }

  } // end of namespace testing

} // end of namespace rabbitmq
