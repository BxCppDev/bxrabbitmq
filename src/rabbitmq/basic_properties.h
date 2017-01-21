// -*- mode: c++; -*-

#ifndef BXRABBITMQ_BASIC_PROPERTIES_H
#define BXRABBITMQ_BASIC_PROPERTIES_H


#include <boost/optional.hpp>

namespace rabbitmq {

  /// \brief RabbitMQ queue parameters
  class basic_properties
  {

     public:
        static const std::string      & default_content_type     ();
        static const basic_properties & default_basic_properties ();

     public:
        basic_properties ();
        void                set_content_type     (const std::string &);
        bool                has_content_type     () const;
        const std::string & get_content_type     () const;
        void                set_content_encoding (const std::string &);
        bool                has_content_encoding () const;
        const std::string & get_content_encoding () const;
        //void                set_headers          (const std::string &);
        bool                has_headers          () const;
        //const std::string & get_headers          () const;
        void                set_delivery_mode    (const uint8_t);
        bool                has_delivery_mode    () const;
        const uint8_t       get_delivery_mode    () const;
        void                set_priority         (const uint8_t);
        bool                has_priority         () const;
        const uint8_t       get_priority         () const;
        void                set_correlation_id   (const std::string &);
        bool                has_correlation_id   () const;
        const std::string & get_correlation_id   () const;
        void                set_reply_to         (const std::string &);
        bool                has_reply_to         () const;
        const std::string & get_reply_to         () const;
        void                set_expiration       (const std::string &);
        bool                has_expiration       () const;
        const std::string & get_expiration       () const;
        void                set_message_id       (const std::string &);
        bool                has_message_id       () const;
        const std::string & get_message_id       () const;
        void                set_timestamp        (const uint64_t);
        bool                has_timestamp        () const;
        const uint64_t      get_timestamp        () const;
        void                set_type             (const std::string &);
        bool                has_type             () const;
        const std::string & get_type             () const;
        void                set_user_id          (const std::string &);
        bool                has_user_id          () const;
        const std::string & get_user_id          () const;
        void                set_app_id           (const std::string &);
        bool                has_app_id           () const;
        const std::string & get_app_id           () const;
        void                set_cluster_id       (const std::string &);
        bool                has_cluster_id       () const;
        const std::string & get_cluster_id       () const;
        const std::string   to_string            () const;

     private :
        boost::optional <std::string> _content_type_;
        boost::optional <std::string> _content_encoding_;
        //todo table headers
        boost::optional <uint8_t>     _delivery_mode_;
        boost::optional <uint8_t>     _priority_;
        boost::optional <std::string> _correlation_id_;
        boost::optional <std::string> _reply_to_;
        boost::optional <std::string> _expiration_;
        boost::optional <std::string> _message_id_;
        boost::optional <uint64_t>    _timestamp_;
        boost::optional <std::string> _type_;
        boost::optional <std::string> _user_id_;
        boost::optional <std::string> _app_id_;
        boost::optional <std::string> _cluster_id_;
  };

} // end of namespace rabbitmq

#endif // BXRABBITMQ_BASIC_PROPERTIES_H
