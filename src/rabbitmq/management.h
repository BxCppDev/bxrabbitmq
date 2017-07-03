// -*- mode: c++; -*-

#ifndef BXRABBITMQ_MANAGEMENT_H
#define BXRABBITMQ_MANAGEMENT_H

// Standard library:
#include <string>
#include <list>

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

      void clear ();

      //  VIRE Permissions setup (TODO move this to a better place)
      void vire_add_exchange_request_perms        (const std::string exchange_name);
      void vire_add_exchange_service_perms        (const std::string exchange_name);
      void vire_add_exchange_event_producer_perms (const std::string exchange_name);
      void vire_add_exchange_event_listener_perms (const std::string exchange_name);
      void vire_add_direct_request_perms          ();
      void vire_add_direct_service_perms          (const std::string queue_name);
      void vire_add_direct_event_producer_perms   ();
      void vire_add_direct_event_listener_perms   (const std::string queue_name);

      //  Single permission modifiers  (single perm is conf, writ or read)
      static void add_amqgen_to   (std::string & single_perm);
      static void add_amqdef_to   (std::string & single_perm);
      static void add_queue_to    (std::string & single_perm, const std::string queue_name);
      static void add_exchange_to (std::string & single_perm, const std::string exchange_name);

      private :
         //  Mailbox name and single perm tools
         static void        add_mbox_to    (std::string & single_perm, const std::string mbox_name);
         static void        add_regexp_to  (std::string & single_perm, const std::string regexp);
         static std::string mbox_to_regexp (const std::string & mbox);  //  mbox is a queue or an exchange

   };



} // end of namespace rabbitmq

#endif // BXRABBITMQ_MANAGEMENT_H
