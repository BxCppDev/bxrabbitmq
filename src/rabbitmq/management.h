// -*- mode: c++; -*-

#ifndef BXRABBITMQ_MANAGEMENT_H
#define BXRABBITMQ_MANAGEMENT_H

// Standard library:
#include <string>
//#include <boost/optional.hpp>

// Bayeux/jsontools:
#include "jsontools/i_jsonizable.h"

namespace rabbitmq {


   /// \brief error
   struct error_response : public jsontools::i_jsonizable
   {
      static const std::string &    no_error    ();
      static const std::string &    no_problem  ();
      static const error_response & response_ok ();

      error_response ();

      virtual void jsonize (jsontools::node & node_,
                            const unsigned long int version_ = 0);
      std::string what;
      std::string why;
   };


   /// \brief vhost
   struct vhost : public jsontools::i_jsonizable
   {
      typedef std::list <vhost> list;

      vhost ();
      vhost (const std::string & name_);
      virtual ~vhost ();

      virtual void jsonize (jsontools::node & node_,
                            const unsigned long int version_ = 0);

      std::string                name;
      bool                       tracing = false;
      //boost::optional <uint32_t> messages;
      //boost::optional <uint32_t> messages_ready;
      //boost::optional <uint32_t> messages_unaknowledged;
   };


   /// \brief exchange
   struct exchange : public jsontools::i_jsonizable
   {
      typedef std::list <exchange> list;

      exchange ();
      exchange (const std::string & name_,
                const std::string & vhost_,
                const std::string & type_);
      virtual ~exchange ();

      virtual void jsonize (jsontools::node & node_,
                            const unsigned long int version_ = 0);

      std::string name;
      std::string vhost;
      std::string type;
      bool        durable     = true;
      bool        auto_delete = false;
      bool        internal    = false;
   };



} // end of namespace rabbitmq

#endif // BXRABBITMQ_RABBIT_MGR_H
