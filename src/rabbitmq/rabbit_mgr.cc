
// std
#include <exception>
#include <iostream>
#include <sstream>

// json, cURLpp
#include <json/json.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <jsontools/io.h>
#include <jsontools/std_type_converters.h>
//#include <jsontools/node.h>

// Ourselves:
#include "rabbit_mgr.h"
#include "management.h"

namespace rabbitmq {


   /***  local  ************************************************************/

   template <typename T>
   bool _request_perform_   (curlpp::Easy      & request_,
                             T                 & response_,
                             error_response    & error_);

   bool _request_perform_   (curlpp::Easy      & request_,
                             error_response    & error_);

   std::string _vhost_name_ (const std::string & vhost_code_);

   std::string _vhost_code_ (const std::string & vhost_name_);

   std::string _to_string_  (const bool          b);

   /************************************************************************/


   rabbit_mgr::rabbit_mgr  (const std::string & server_host_,
                            const uint16_t      server_port_,
                            const std::string & user_login_,
                            const std::string & user_passwd_)
   {
      _server_host_ = server_host_;
      _server_port_ = server_port_;
      _user_login_  = user_login_;
      _user_passwd_ = user_passwd_;
      return;
   }


   rabbit_mgr::~rabbit_mgr ()
   {
      return;
   }


   bool rabbit_mgr::list_vhosts (vhost::list    & vhosts_,
                                 error_response & error_)
   {
      curlpp::Cleanup cleaner;
      curlpp::Easy    request;
      _request_setBaseOpts_  (request, "vhosts");
      return _request_perform_<vhost::list> (request, vhosts_, error_);
   }


   bool rabbit_mgr::add_vhost (const std::string & name_,
                               error_response    & error_)
   {
      curlpp::Cleanup cleaner;
      curlpp::Easy    request;
      _request_setBaseOpts_ (request, "vhosts/" + _vhost_code_ (name_), "PUT", true);
      return _request_perform_ (request, error_);
   }


   bool rabbit_mgr::delete_vhost (const std::string & name_,
                                  error_response    & error_)
   {
      curlpp::Cleanup cleaner;
      curlpp::Easy    request;
      _request_setBaseOpts_ (request, "vhosts/" + _vhost_code_ (name_), "DELETE", true);
      return _request_perform_ (request, error_);
   }


   bool rabbit_mgr::list_exchanges (const std::string & vhost_name_,
                                    exchange::list    & exchanges_,
                                    error_response    & error_)
   {
      curlpp::Cleanup        cleaner;
      curlpp::Easy           request;
      _request_setBaseOpts_ (request, "exchanges/" + _vhost_code_ (vhost_name_));
      return _request_perform_<exchange::list> (request, exchanges_, error_);
   }


   bool rabbit_mgr::exchange_declare (const std::string & name_,
                                      const std::string & vhost_,
                                      const std::string & type_,
                                      const bool          durable_,
                                      const bool          auto_delete_,
                                      const bool          internal_,
                                      error_response    & error_)
   {
      curlpp::Cleanup cleaner;
      curlpp::Easy    request;
      std::string     options;
      options = options + "{";
      options = options + "\"type\""        + ": " + "\"" + type_ + "\"";
      options = options + ", ";
      options = options + "\"durable\""     + ": " + _to_string_ (durable_);
      options = options + ", ";
      options = options + "\"auto_delete\"" + ": " + _to_string_ (auto_delete_);
      options = options + ", ";
      options = options + "\"internal\""    + ": " + _to_string_ (internal_);
      options = options + "}";
      _request_setBaseOpts_ (request, "exchanges/" + _vhost_code_ (vhost_) + "/" + name_, "PUT", true);
      request.setOpt (new curlpp::options::PostFields (options));
      return _request_perform_ (request, error_);
   }


   bool rabbit_mgr::delete_exchange (const std::string & name_,
                                     const std::string & vhost_,
                                     error_response    & error_)
   {
      curlpp::Cleanup cleaner;
      curlpp::Easy    request;
      _request_setBaseOpts_ (request, "exchanges/" + _vhost_code_ (vhost_) + "/" + name_, "DELETE", true);
      return _request_perform_ (request, error_);
   }


   bool rabbit_mgr::list_queues (const std::string & vhost_name_,
                                    queue::list    & queues_,
                                    error_response    & error_)
   {
      curlpp::Cleanup        cleaner;
      curlpp::Easy           request;
      _request_setBaseOpts_ (request, "queues/" + _vhost_code_ (vhost_name_));
      return _request_perform_<queue::list> (request, queues_, error_);
   }


   bool rabbit_mgr::queue_declare (const std::string & name_,
                                   const std::string & vhost_,
                                   const bool          durable_,
                                   const bool          auto_delete_,
                                   error_response    & error_)
   {
      curlpp::Cleanup cleaner;
      curlpp::Easy    request;
      std::string     options;
      options = options + "{";
      options = options + "\"durable\""     + ": " + _to_string_ (durable_);
      options = options + ", ";
      options = options + "\"auto_delete\"" + ": " + _to_string_ (auto_delete_);
      options = options + "}";
      _request_setBaseOpts_ (request, "queues/" + _vhost_code_ (vhost_) + "/" + name_, "PUT", true);
      request.setOpt (new curlpp::options::PostFields (options));
      return _request_perform_ (request, error_);
   }


   bool rabbit_mgr::delete_queue (const std::string & name_,
                                  const std::string & vhost_,
                                  error_response    & error_)
   {
      curlpp::Cleanup cleaner;
      curlpp::Easy    request;
      _request_setBaseOpts_ (request, "queues/" + _vhost_code_ (vhost_) + "/" + name_, "DELETE", true);
      return _request_perform_ (request, error_);
   }


   bool rabbit_mgr::list_users (user::list     & users_,
                                error_response & error_)
   {
      curlpp::Cleanup cleaner;
      curlpp::Easy    request;
      _request_setBaseOpts_  (request, "users");
      return _request_perform_<user::list> (request, users_, error_);
   }


   bool rabbit_mgr::add_user (const std::string & name_,
                              const std::string & passwd_,
                              error_response    & error_)
   {
      curlpp::Cleanup cleaner;
      curlpp::Easy    request;
      std::string     options;
      options = options + "{";
      options = options + "\"password\"" + ": " + "\"" + passwd_ + "\"";
      options = options + ", ";
      options = options + "\"tags\""     + ": " + "\"" +           "\"";   //  TODO tags ...
      options = options + "}";
      _request_setBaseOpts_ (request, "users/" + name_, "PUT", true);
      request.setOpt (new curlpp::options::PostFields (options));
      return _request_perform_ (request, error_);
   }


   bool rabbit_mgr::delete_user (const std::string & name_,
                                 error_response    & error_)
   {
      curlpp::Cleanup cleaner;
      curlpp::Easy    request;
      _request_setBaseOpts_ (request, "users/" + name_, "DELETE", true);
      return _request_perform_ (request, error_);
   }


   /***  private  ************************************************************************/


   void rabbit_mgr::_request_setBaseOpts_ (curlpp::Easy      & request_,
                                           const std::string & cmd_,
                                           const std::string & custom_,
                                           const bool          appli_)
   {
      std::string url  = _server_host_ + ":" + std::to_string (_server_port_) + "/api/" + cmd_;
      std::string upwd = _user_login_ + ":" + _user_passwd_;
      if (_server_port_  == SSL_PORT) {
         url = "https://" + url;
      } else {
         url =  "http://" + url;
      }
      request_.setOpt (new curlpp::options::Url     (url));
      request_.setOpt (new curlpp::options::UserPwd (upwd));
      if (_server_port_ == SSL_PORT) {
         request_.setOpt (new curlpp::options::SslEngineDefault ());
         request_.setOpt (new curlpp::options::SslVerifyPeer (false));
         request_.setOpt (new curlpp::options::SslVerifyHost (0));
      }
      if (custom_ != "GET") {
         request_.setOpt (new curlpp::options::CustomRequest (custom_));
      }
      if (appli_) {
         std::list <std::string> header;
         header.push_back ("Content-Type: application/json");
         request_.setOpt (new curlpp::options::HttpHeader (header));
         request_.setOpt (new curlpp::options::Header (true));
      }
   }


   /***  local  ***************************************************************************/


   template <typename T>
   bool _request_perform_ (curlpp::Easy   & request_,
                           T              & response_,
                           error_response & error_)
   {
      std::string str_response;
      try {
         std::stringstream ss;
         ss << request_;
         str_response = ss.str ();
         error_       = error_response::response_ok ();
      } catch (std::exception & x) {
         std::cerr << "ERROR: " << x.what() << std::endl;
         error_.error  = x.what ();
         error_.reason = "_request_perform_ <T>";
         return false;
      }
      try {
         std::stringstream ss (str_response);
         jsontools::load (ss, response_);
         return true;
      } catch (...) {
         //std::clog << "\n== ERROR RESPONSE ==> " << str_response << std::endl;
         std::stringstream ss (str_response);
         jsontools::load (ss, error_);
         return false;
      }
   }


   bool _request_perform_ (curlpp::Easy   & request_,
                           error_response & error_)
   {
      std::stringstream ss;
      std::string       str_response;
      std::string       line;
      size_t            pos;
      size_t            jsize = 0;
      try {
         ss << request_;
         str_response = ss.str ();
         error_       = error_response::response_ok ();
         while (std::getline (ss, line)) {
            pos = line.find ("Content-Length:");
            if (pos != std::string::npos) {
               jsize = std::stoi (line.substr (pos+15));
               break;
            }
         }
         if (jsize != 0) {
            jsontools::load (ss, error_);
            return false;
         }
      } catch (std::exception & x) {
         std::cerr << "ERROR: " << x.what() << std::endl;
         error_.error  = x.what ();
         error_.reason = "_request_perform_";
         return false;
      }
   }


   std::string _vhost_name_ (const std::string & vhost_code_)
   {
      std::string name (vhost_code_);
      size_t      pos  = name.find ("%2f");
      if (pos != std::string::npos) {
         name.replace (pos, 3, "/");
      }
      return name;
   }


   std::string _vhost_code_ (const std::string & vhost_name_)
   {
      std::string code (vhost_name_);
      if (code [0] == '/') {
         code.replace (0, 1, "%2f");
      }
      return code;
   }


   std::string _to_string_ (const bool b)
   {
      if (b) return "true";
      return "false";
   }



} // end of namespace rabbitmq
