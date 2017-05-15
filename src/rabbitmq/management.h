// -*- mode: c++; -*-

#ifndef BXRABBITMQ_MANAGEMENT_H
#define BXRABBITMQ_MANAGEMENT_H

// Standard library:
#include <string>
#include <list>

// Third party:
// - Bayeux/jsontools:
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
      std::string error;
      std::string reason;
   };


   /// \brief vhost
   struct vhost : public jsontools::i_jsonizable
   {
      typedef std::list <vhost> list;

      virtual void jsonize (jsontools::node & node_,
                            const unsigned long int version_ = 0);

      std::string                name;
      bool                       tracing = false;
   };


   /// \brief exchange
   struct exchange : public jsontools::i_jsonizable
   {
      typedef std::list <exchange> list;

      virtual void jsonize (jsontools::node & node_,
                            const unsigned long int version_ = 0);

      std::string name;
      std::string vhost;
      std::string type;
      bool        durable     = true;
      bool        auto_delete = false;
      bool        internal    = false;
   };


   /// \brief queue
   struct queue : public jsontools::i_jsonizable
   {
      typedef std::list <queue> list;

      virtual void jsonize (jsontools::node & node_,
                            const unsigned long int version_ = 0);

      std::string name;
      std::string vhost;
      bool        durable     = true;
      bool        auto_delete = false;
   };


   /// \brief user
   struct user : public jsontools::i_jsonizable
   {
      typedef std::list <user> list;

      virtual void jsonize (jsontools::node & node_,
                            const unsigned long int version_ = 0);

      std::string name;
      std::string tags;
   };


   /// \brief permission
   struct permissions : public jsontools::i_jsonizable
   {
      typedef std::list <permissions> list;

      virtual void jsonize (jsontools::node & node_,
                            const unsigned long int version_ = 0);

      std::string user;
      std::string vhost;
      std::string configure;
      std::string write;
      std::string read;
   };



} // end of namespace rabbitmq

#endif // BXRABBITMQ_MANAGEMENT_H
