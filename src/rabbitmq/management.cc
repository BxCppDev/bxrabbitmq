
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

  vhost::vhost ()
  {
    return;
  }

  vhost::vhost (const std::string & name_)
    : name (name_)
  {
    return;
  }

  vhost::~vhost ()
  {
  }

  void vhost::jsonize (jsontools::node & node_,
                       const unsigned long int /* version_ */)
  {
    node_ ["name"]                   % name;
    node_ ["tracing"]                % tracing;
//    node_ ["messages"]               % messages;
//    node_ ["messages_ready"]         % messages_ready;
//    node_ ["messages_unaknowledged"] % messages_unaknowledged;
    return;
  }


  /***  EXCHANGE  **********************************************************/

  exchange::exchange ()
  {
    return;
  }

  exchange::exchange (const std::string & name_,
                      const std::string & vhost_,
                      const std::string & type_)
    : name (name_), vhost (vhost_), type (type_)
  {
    return;
  }

  exchange::~exchange ()
  {
  }

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

  queue::queue ()
  {
    return;
  }

  queue::queue (const std::string & name_,
                const std::string & vhost_)
    : name (name_), vhost (vhost_)
  {
    return;
  }

  queue::~queue ()
  {
  }

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
    node_ ["password_hash"] % password_hash;
    node_ ["tags"]          % tags;
    return;
  }


} // end of namespace rabbitmq
