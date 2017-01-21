#include <iostream>

// Ourselves:
#include "basic_properties.h"


namespace rabbitmq {

   const std::string & basic_properties::default_content_type ()   // static
   {
      static const std::string def = "text/plain";
      return def;
   }

   const basic_properties & basic_properties::default_basic_properties ()   // static
   {
      static const basic_properties def;
      return def;
   }

   basic_properties::basic_properties ()
   {
      set_content_type (default_content_type ());
      return;
   }

   void basic_properties::set_content_type (const std::string & content_type_)
   {
      _content_type_ = content_type_;
      return;
   }

   bool basic_properties::has_content_type () const
   {
      return !!_content_type_;
   }

   const std::string & basic_properties::get_content_type () const
   {
      return *_content_type_;
   }

   void basic_properties::set_content_encoding (const std::string & content_encoding_)
   {
      _content_encoding_ = content_encoding_;
      return;
   }

   bool basic_properties::has_content_encoding () const
   {
      return !!_content_encoding_;
   }

   const std::string & basic_properties::get_content_encoding () const
   {
      return *_content_encoding_;
   }

   //void basic_properties::set_headers (const std::string & headers_)
   //{
   //   _headers_ = headers_;
   //   return;
   //}

   bool basic_properties::has_headers () const
   {
   //   return !!_headers_;
      return false;
   }

   //const std::string & basic_properties::get_headers ()
   //{
   //   return *_headers_;
   //}

   void basic_properties::set_delivery_mode (const uint8_t delivery_mode_)
   {
      _delivery_mode_ = delivery_mode_;
      return;
   }

   bool basic_properties::has_delivery_mode () const
   {
      return !!_delivery_mode_;
   }

   const uint8_t basic_properties::get_delivery_mode () const
   {
      return *_delivery_mode_;
   }

   void basic_properties::set_priority (const uint8_t priority_)
   {
      _priority_ = priority_;
      return;
   }

   bool basic_properties::has_priority () const
   {
      return !!_priority_;
   }

   const uint8_t basic_properties::get_priority () const
   {
      return *_priority_;
   }

   void basic_properties::set_correlation_id (const std::string & correlation_id_)
   {
      _correlation_id_ = correlation_id_;
      return;
   }

   bool basic_properties::has_correlation_id () const
   {
      return !!_correlation_id_;
   }

   const std::string & basic_properties::get_correlation_id () const
   {
      return *_correlation_id_;
   }

   void basic_properties::set_reply_to (const std::string & reply_to_)
   {
      _reply_to_ = reply_to_;
      return;
   }

   bool basic_properties::has_reply_to () const
   {
      return !!_reply_to_;
   }

   const std::string & basic_properties::get_reply_to () const
   {
      return *_reply_to_;
   }

   void basic_properties::set_expiration (const std::string & expiration_)
   {
      _expiration_ = expiration_;
      return;
   }

   bool basic_properties::has_expiration () const
   {
      return !!_expiration_;
   }

   const std::string & basic_properties::get_expiration () const
   {
      return *_expiration_;
   }

   void basic_properties::set_message_id (const std::string & message_id_)
   {
      _message_id_ = message_id_;
      return;
   }

   bool basic_properties::has_message_id () const
   {
      return !!_message_id_;
   }

   const std::string & basic_properties::get_message_id () const
   {
      return *_message_id_;
   }

   void basic_properties::set_timestamp (const uint64_t timestamp_)
   {
      _timestamp_ = timestamp_;
      return;
   }

   bool basic_properties::has_timestamp () const
   {
      return !!_timestamp_;
   }

   const uint64_t basic_properties::get_timestamp () const
   {
      return *_timestamp_;
   }

   void basic_properties::set_type (const std::string & type_)
   {
      _type_ = type_;
      return;
   }

   bool basic_properties::has_type () const
   {
      return !!_type_;
   }

   const std::string & basic_properties::get_type () const
   {
      return *_type_;
   }

   void basic_properties::set_user_id (const std::string & user_id_)
   {
      _user_id_ = user_id_;
      return;
   }

   bool basic_properties::has_user_id () const
   {
      return !!_user_id_;
   }

   const std::string & basic_properties::get_user_id () const
   {
      return *_user_id_;
   }

   void basic_properties::set_app_id (const std::string & app_id_)
   {
      _app_id_  = app_id_;
      return;
   }

   bool basic_properties::has_app_id () const
   {
      return !!_app_id_;
   }

   const std::string & basic_properties::get_app_id () const
   {
      return *_app_id_;
   }

   void basic_properties::set_cluster_id (const std::string & cluster_id_)
   {
      _cluster_id_ = cluster_id_;
      return;
   }

   bool basic_properties::has_cluster_id () const
   {
      return !!_cluster_id_;
   }

   const std::string & basic_properties::get_cluster_id () const
   {
      return *_cluster_id_;
   }

   const std::string basic_properties::to_string () const
   {
      std::string str;
      if (has_content_type ())   str += get_content_type ()   + " " ;
      if (has_correlation_id ()) str += get_correlation_id () + " " ;
      if (has_reply_to ())       str += get_reply_to ();
      return str;
   }


} // end of namespace rabbitmq
