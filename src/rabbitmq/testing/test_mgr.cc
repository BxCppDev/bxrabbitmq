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
      mgr.test ();
      return;
    }

  } // end of namespace testing

} // end of namespace rabbitmq
