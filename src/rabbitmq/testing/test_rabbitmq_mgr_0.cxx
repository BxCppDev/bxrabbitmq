// Standard library:
#include <exception>
#include <cstdlib>
#include <iostream>

// This project:
#include <rabbitmq/testing/test_mgr.h>

int main (int argc, char** argv)
{
  int test_num   = 0;
  int error_code = EXIT_SUCCESS;
  try {

    if (argc > 1) {
       test_num = atoi (argv [1]);
    }
    rabbitmq::testing::test_mgr::run_test_0 ();

  } catch (std::exception & x) {
    std::cerr << "ERROR: " << x.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "ERROR: " << "Unexpected exception!" << std::endl;
    error_code = EXIT_FAILURE;
  }
  return error_code;
}
