// -*- mode: c++; -*-

#ifndef BXRABBITMQ_TESTING_TEST_H
#define BXRABBITMQ_TESTING_TEST_H

// This project:
#include <rabbitmq/config.h>

namespace rabbitmq {

  namespace testing {

    class test
    {
    public:

      static void run_test_0 ();

      static void run_test_1 (int num);

      static void run_test_2 ();

      static void run_test_3 ();
#if BXRABBITMQ_WITH_MANAGER == 1
      static void run_test_4 ();
#endif // BXRABBITMQ_WITH_MANAGER == 1

//
//      static void run_test_5 ();

    };

  } // end of namespace testing

} // end of namespace rabbitmq

#endif // BXRABBITMQ_TESTING_TEST_H
