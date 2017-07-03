
// std
#include <iostream>
#include <sstream>

// Bayeux/jsontools:
#include <json/json.h>
#include <jsontools/base_type_converters.h>
#include <jsontools/std_type_converters.h>
#include <jsontools/boost_type_converters.h>

// Ourselves:
#include "management.h"

namespace rabbitmq {

  /***  ERROR RESPONSE  *****************************************************/

  const std::string & error_response::no_error ()   // static
  {
    static const std::string no_err = "no error";
    return no_err;
  }

  const std::string & error_response::no_problem ()   // static
  {
    static const std::string no_pb = "no problem";
    return no_pb;
  }

  const error_response & error_response::response_ok ()   // static
  {
    static const error_response ok;
    return ok;
  }

  error_response::error_response ()
  {
    this->error  = no_error ();
    this->reason = no_problem ();
    return;
  }

  void error_response::jsonize (jsontools::node & node_,
                                const unsigned long int /* version_ */)
  {
    node_ ["error"]  % error;
    node_ ["reason"] % reason;
    return;
  }


  /***  VHOST  **************************************************************/

  void vhost::jsonize (jsontools::node & node_,
                       const unsigned long int /* version_ */)
  {
    node_ ["name"]                   % name;
    node_ ["tracing"]                % tracing;
    return;
  }


  /***  EXCHANGE  **********************************************************/

  void exchange::jsonize (jsontools::node &   node_,
                          const unsigned long int /* version_ */)
  {
    node_ ["name"]        % name;
    node_ ["vhost"]       % vhost;
    node_ ["type"]        % type;
    node_ ["durable"]     % durable;
    node_ ["auto_delete"] % auto_delete;
    node_ ["internal"]    % internal;
    return;
  }


  /***  QUEUE  **************************************************************/

  void queue::jsonize (jsontools::node &   node_,
                       const unsigned long int /* version_ */)
  {
    node_ ["name"]        % name;
    node_ ["vhost"]       % vhost;
    node_ ["durable"]     % durable;
    node_ ["auto_delete"] % auto_delete;
    return;
  }


  /***  USER  ****************************************************************/

  void user::jsonize (jsontools::node &   node_,
                      const unsigned long int /* version_ */)
  {
    node_ ["name"]          % name;
    node_ ["tags"]          % tags;
    return;
  }


  /***  PERMISSIONS  **********************************************************/

  void permissions::jsonize (jsontools::node &   node_,
                             const unsigned long int /* version_ */)
  {
    node_ ["user"]      % user;
    node_ ["vhost"]     % vhost;
    node_ ["configure"] % configure;
    node_ ["write"]     % write;
    node_ ["read"]      % read;
    return;
  }

  void permissions::clear () {
     user      = "";
     vhost     = "";
     configure = "";
     write     = "";
     read      = "";
  }

  void permissions::vire_add_exchange_request_perms (const std::string exchange_name) {
     add_amqgen_to   (configure);
     add_exchange_to (write, exchange_name);
     add_amqgen_to   (read);
  }

  void permissions::vire_add_exchange_service_perms (const std::string exchange_name) {
     add_amqgen_to   (configure);
     add_amqdef_to   (write);
     add_amqgen_to   (write);
     add_exchange_to (read, exchange_name);
     add_amqgen_to   (read);
  }

  void permissions::vire_add_exchange_event_producer_perms (const std::string exchange_name) {
     add_exchange_to (write, exchange_name);
  }

  void permissions::vire_add_exchange_event_listener_perms (const std::string exchange_name) {
     add_amqgen_to   (configure);
     add_amqgen_to   (write);
     add_exchange_to (read, exchange_name);
     add_amqgen_to   (read);
  }

  void permissions::vire_add_direct_request_perms () {
     add_amqgen_to   (configure);
     add_amqdef_to   (write);
     add_amqgen_to   (read);
  }

  void permissions::vire_add_direct_service_perms (const std::string queue_name) {
     add_amqdef_to   (write);
     add_queue_to    (read, queue_name);
  }

  void permissions::vire_add_direct_event_producer_perms () {
     add_amqdef_to (write);
  }

  void permissions::vire_add_direct_event_listener_perms (const std::string queue_name) {
     add_queue_to  (read, queue_name);
  }

  void permissions::add_amqgen_to (std::string & single_perm) {
     const std::string AMQGEN_PERM ("^amq\\.gen*");
     add_regexp_to (single_perm, AMQGEN_PERM);
  }

  void permissions::add_amqdef_to (std::string & single_perm) {
     const std::string AMQDEF_PERM ("^amq\\.default$");
     add_regexp_to (single_perm, AMQDEF_PERM);
  }

  void permissions::add_queue_to (std::string & single_perm, const std::string queue_name) {
     add_mbox_to (single_perm, queue_name);
  }

  void permissions::add_exchange_to (std::string & single_perm, const std::string exchange_name) {
     add_mbox_to (single_perm, exchange_name);
  }

  void permissions::add_mbox_to (std::string & single_perm, const std::string mbox) {
     const std::string mbox_perm = mbox_to_regexp (mbox);
     add_regexp_to (single_perm, mbox_perm);
  }

  void permissions::add_regexp_to (std::string & single_perm, const std::string regexp) {
     if (single_perm == "") {
        single_perm = regexp;
     } else if (single_perm.find (regexp) == std::string::npos) {
        single_perm = single_perm + "|" + regexp;
     }
  }

  std::string permissions::mbox_to_regexp (const std::string & mbox) {
     size_t pos = 0;
     std::string reg_mbox (mbox);
     while ((pos = reg_mbox.find (".", pos)) != std::string::npos) {
        reg_mbox.replace (pos, 1, "\\.");
        pos = pos + 2;
     }
     reg_mbox = "^" + reg_mbox;
     reg_mbox = reg_mbox + "$";
     return reg_mbox;
  }


} // end of namespace rabbitmq
