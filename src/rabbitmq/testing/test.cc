// Ourselves:
#include <rabbitmq/testing/test.h>

// Standard library:
#include <unistd.h>
#include <iostream>

// This project:
#include <rabbitmq/connection.h>
#include <rabbitmq/channel.h>
#include <rabbitmq/parameters.h>

namespace rabbitmq {

  namespace testing {

    // static
    void test::run_test_0 ()         //  queue declare - exchange declare
    {
      std::clog << "\ntest::run_test_0: \n" ;
      connection_parameters c_par;
      connection            con (c_par);
      std::clog << "connection ..." << std::endl;
      if (con.is_ok ()) {

         channel& chan = con.grab_channel ();

         queue_parameters q_par;
         q_par.name    = "q_hello";
         //q_par.durable = true;
         chan.queue_declare (q_par);
         std::clog << "hello queue declare ..." << std::endl;

         q_par.name        = "";
         q_par.auto_delete = true;
         chan.queue_declare (q_par);
         std::clog << "anonym queue declare ..." << std::endl;
         std::clog << "name choosen by rabbit is " << q_par.name << std::endl;

         exchange_parameters x_par;
         x_par.name = "x_hello";
         x_par.type = "direct";
         chan.exchange_declare (x_par);
         std::clog << "x_hello exchange declare ..." << std::endl;

      } else {
         std::cerr << "fail to declare ..." << std::endl;
      }
      return;
    }

    // static
    void test::run_test_1 (int num = 0)    //  direct plublish to queue
    {
      std::clog << "\ntest::run_test_0: \n" ;
      std::clog << "\n test num = " << num << "\n" ;
      connection_parameters c_par;
      connection            con (c_par);
      std::clog << "connection ..." << std::endl;
      if (con.is_ok ()) {
         channel& chan = con.grab_channel ();
         basic_properties props;
         props.set_content_type  ("text/plain");
         props.set_delivery_mode (2); // persistant
         for (int i=0; i<10; i++) {
            chan.basic_publish ("", "q_hello", "Hello_World_" + std::to_string (num + i), props, false, false);
         }
         std::clog << "publish to q_hello ..." << std::endl;
      } else {
         std::cerr << "fail to publish ..." << std::endl;
      }
      return;
    }

    // static
    void test::run_test_2 ()    //  listen a queue 5 time
    {
      std::clog << "\ntest::run_test_2: \n" ;
      connection_parameters c_par;
      connection            con (c_par);
      std::clog << "connection ..." << std::endl;
      if (con.is_ok ()) {
         std::string      routing_key;
         std::string      message;
         basic_properties props;
         uint64_t         delivery;
         channel& chan = con.grab_channel ();
         chan.basic_consume ("q_hello");
         std::clog << "listening to 5 time to q_hello ..." << std::endl;
         for (int i=0; i<5; i++) {
            chan.consume_message (message, routing_key, props, delivery);
            std::clog << "received :" << message << std::endl;
         }
      } else {
         std::cerr << "fail to listen ..." << std::endl;
      }
      return;
    }

    void my_callback (std::string & msg_, std::string & rkey_, basic_properties & props_) {
         std::clog << "callback : " << msg_ << std::endl;
    }

    // static
    void test::run_test_3 ()  // listen a queue during 2 sec (with callback)
    {
      std::clog << "\ntest::run_test_3: \n" ;
      connection_parameters c_par;
      connection            con (c_par);
      std::clog << "connection ..." << std::endl;
      if (con.is_ok ()) {
         std::string      routing_key;
         std::string      message;
         basic_properties props;
         channel& chan = con.grab_channel ();
         chan.basic_consume ("q_hello");
         std::clog << "listening during 2s to q_hello with a callback ..." << std::endl;
         chan.start_consuming (&my_callback);
         sleep (2.0);
         chan.stop_consuming  ();
      } else {
         std::cerr << "fail to listen ..." << std::endl;
      }
      return;
    }

  } // end of namespace testing

} // end of namespace rabbitmq
