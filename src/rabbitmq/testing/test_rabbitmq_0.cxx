// Standard library:
#include <exception>
#include <cstdlib>
#include <iostream>

// This project:
#include <rabbitmq/testing/test.h>

int main (int argc, char** argv)
{
  int test_num   = 0;
  int error_code = EXIT_SUCCESS;
  try {

    if (argc > 1) {
       test_num = atoi (argv [1]);
    }

    rabbitmq::testing::test::run_test_0 ();
    rabbitmq::testing::test::run_test_1 (test_num);
    rabbitmq::testing::test::run_test_2 ();
    rabbitmq::testing::test::run_test_1 (test_num + 10);
    rabbitmq::testing::test::run_test_2 ();
    rabbitmq::testing::test::run_test_1 (test_num + 20);
    rabbitmq::testing::test::run_test_3 ();
    rabbitmq::testing::test::run_test_4 ();

  } catch (std::exception & x) {
    std::cerr << "ERROR: " << x.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "ERROR: " << "Unexpected exception!" << std::endl;
    error_code = EXIT_FAILURE;
  }
  return error_code;
}
