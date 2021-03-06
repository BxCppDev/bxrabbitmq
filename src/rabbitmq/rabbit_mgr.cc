
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

   bool _request_test_      (const curlpp::Easy & request_,
                             std::string        & response_);

   bool _request_perform_   (const curlpp::Easy & request_,
                             error_response     & error_);

   template <typename T>
   bool _request_perform_   (const curlpp::Easy & request_,
                             T                  & response_,
                             error_response     & error_);

   std::string _vhost_name_ (const std::string  & vhost_code_);

   std::string _vhost_code_ (const std::string  & vhost_name_);

   std::string _to_string_  (const bool           b);

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


   bool rabbit_mgr::test (std::string & response_)
   {
      curlpp::Cleanup cleaner;
      curlpp::Easy    request;
      _request_setBaseOpts_ (request, "policies");
      return _request_test_ (request, response_);
   }


   bool rabbit_mgr::list_vhosts (vhost::list    & vhosts_,
                                 error_response & error_) const
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
      bool            ok;
      error_response  err;
      _request_setBaseOpts_ (request, "vhosts/" + _vhost_code_ (name_), "PUT", true);
      ok = _request_perform_ (request, error_);
      if (ok) set_permissions (_user_login_, name_, ".*", ".*", ".*", err);
      return ok;
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
                                    error_response    & error_) const
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
                                    error_response    & error_) const
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
                                error_response & error_) const
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
      user::list users;
      bool       ok = list_users (users, error_);
      if (ok) {
         for (user::list::iterator iter = users.begin(); iter != users.end(); iter++) {
            if ((*iter).name == name_) {
               error_.error  = "user "+ name_ + " not added";
               error_.reason = "user already exists";
               ok            = false;
               break;
            }
         }
         if (ok) ok = _raw_add_user_ (name_, "" , passwd_, error_);
      };
      return ok;
   }


   bool rabbit_mgr::change_user_password (const std::string & name_,
                                          const std::string & passwd_,
                                          error_response    & error_)
   {
      user       usr;
      user::list users;
      bool       ok = list_users (users, error_);
      if (ok) {
         ok = false;
         for (user::list::iterator iter = users.begin(); iter != users.end(); iter++) {
            if ((*iter).name == name_) {
               usr = *iter;
               ok  = true;
               break;
            }
         }
         if (ok) {
            ok = _raw_add_user_ (name_, usr.tags, passwd_, error_);
         } else {
            error_.error  = "password not changed";
            error_.reason = "user "+ name_ + " doesn't exist";
         }
      };
      return ok;
   }


   bool rabbit_mgr::delete_user (const std::string & name_,
                                 error_response    & error_)
   {
      curlpp::Cleanup cleaner;
      curlpp::Easy    request;
      _request_setBaseOpts_ (request, "users/" + name_, "DELETE", true);
      return _request_perform_ (request, error_);
   }


   bool rabbit_mgr::user_permissions (const std::string & username_,
                                      permissions::list & permissions_,
                                      error_response    & error_) const
   {
      curlpp::Cleanup cleaner;
      curlpp::Easy    request;
      _request_setBaseOpts_ (request, "users/" + username_ + "/permissions");
      return _request_perform_<permissions::list> (request, permissions_, error_);
   }


   bool rabbit_mgr::user_permissions (const std::string & username_,
                                      const std::string & vhost_,
                                      permissions       & permissions_,
                                      error_response    & error_) const
   {
      curlpp::Cleanup cleaner;
      curlpp::Easy    request;
      _request_setBaseOpts_ (request, "permissions/" + _vhost_code_ (vhost_) + "/" + username_);
      return _request_perform_<permissions> (request, permissions_, error_);
   }

   bool rabbit_mgr::set_permissions (const std::string & username_,
                                     const std::string & vhost_,
                                     const std::string & configure_,
                                     const std::string & write_,
                                     const std::string & read_,
                                     error_response    & error_)
   {
      curlpp::Cleanup cleaner;
      curlpp::Easy    request;
      std::string     options;
      options = options + "{";
      options = options + "\"configure\"" + ": " + "\"" + configure_ + "\"";
      options = options + ", ";
      options = options + "\"write\""     + ": " + "\"" + write_     + "\"";
      options = options + ", ";
      options = options + "\"read\""      + ": " + "\"" + read_      + "\"";
      options = options + "}";
      _request_setBaseOpts_ (request, "permissions/" + _vhost_code_ (vhost_) + "/" + username_, "PUT", true);
      request.setOpt (new curlpp::options::PostFields (options));
      return _request_perform_ (request, error_);
   }

   bool rabbit_mgr::set_permissions (const permissions & perms_,
                                     error_response    & error_)
   {
      return set_permissions (perms_.user, perms_.vhost, perms_.configure, perms_.write, perms_.read, error_);
   }


   /***  private  ************************************************************************/


   void rabbit_mgr::_request_setBaseOpts_ (curlpp::Easy      & request_,
                                           const std::string & cmd_,
                                           const std::string & custom_,
                                           const bool          appli_) const
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


   bool rabbit_mgr::_raw_add_user_ (const std::string & name_,
                                    const std::string & tags_,
                                    const std::string & passwd_,
                                    error_response    & error_)
   {
      curlpp::Cleanup cleaner;
      curlpp::Easy    request;
      std::string     options;
      options = options + "{";
      options = options + "\"password\"" + ": " + "\"" + passwd_ + "\"";
      options = options + ", ";
      options = options + "\"tags\""     + ": " + "\"" + tags_   + "\"";
      options = options + "}";
      _request_setBaseOpts_ (request, "users/" + name_, "PUT", true);
      request.setOpt (new curlpp::options::PostFields (options));
      return _request_perform_ (request, error_);
   }


   /***  local  ***************************************************************************/

   bool _request_test_ (const curlpp::Easy & request_,
                        std::string  & response_)
   {
      std::ostringstream os;
      try {
         os << request_;
         response_ = os.str ();
         return true;
      } catch (std::exception & x) {
         response_ = x.what ();
         return false;
      }
   }


   bool _request_perform_ (const curlpp::Easy   & request_,
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
         error_  = error_response::response_ok ();
         return true;
      } catch (std::exception & x) {
         error_.error  = x.what ();
         error_.reason = "_request_perform_";
         return false;
      }
   }


   template <typename T>
   bool _request_perform_ (const curlpp::Easy & request_,
                           T                  & response_,
                           error_response     & error_)
   {
      std::string str_response;
      try {
         std::ostringstream os;
         os << request_;
         str_response = os.str ();
         error_       = error_response::response_ok ();
      } catch (std::exception & x) {
         std::cerr << "ERROR: " << x.what() << std::endl;
         error_.error  = x.what ();
         error_.reason = "_request_perform_ <T>";
         return false;
      }
      try {
         std::istringstream is (str_response);
         jsontools::load (is, response_);
         return true;
      } catch (...) {
         //std::clog << "\n== ERROR RESPONSE ==> " << str_response << std::endl;
         std::istringstream is (str_response);
         jsontools::load (is, error_);
         return false;
      }
   }


   std::string _vhost_name_ (const std::string & vhost_code_)
   {
      std::string name (vhost_code_);
      size_t      pos;
      while ((pos = name.find ("%2f")) != std::string::npos) {
         name.replace (pos, 3, "/");
      }
      return name;
   }


   std::string _vhost_code_ (const std::string & vhost_name_)
   {
      std::string code (vhost_name_);
      size_t      pos;
      while ((pos = code.find ("/")) != std::string::npos) {
         code.replace (pos, 1, "%2f");
      }
      return code;
   }


   std::string _to_string_ (const bool b)
   {
      if (b) return "true";
      return "false";
   }



} // end of namespace rabbitmq
