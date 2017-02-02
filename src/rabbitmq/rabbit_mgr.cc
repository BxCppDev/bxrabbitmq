
// std
#include <iostream>
#include <sstream>

// json, cURLpp
#include <json/json.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

// Ourselves:
#include "rabbit_mgr.h"

namespace rabbitmq {

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

   void rabbit_mgr::test ()
   {
      std::clog << "\nrabbit_mgr::test\n\n";

      curlpp::Cleanup        cleaner;
      curlpp::Easy           request;
      std::string            url  = "http://" + _server_host_ + ":" + std::to_string (_server_port_) + "/api/vhosts";
      std::string            upwd = _user_login_ + ":" + _user_passwd_;
      std::ostringstream     oss;
      std::string            response;
      //std::list<std::string> header;
      //header.push_back ("Content-Type: application/octet-stream");
      //request.setOpt   (new curlpp::options::HttpHeader (header));
      //request.setOpt   (new curlpp::options::Verbose (true));
      request.setOpt   (new curlpp::options::Url     (url));
      request.setOpt   (new curlpp::options::UserPwd (upwd));

      //request.perform  ();
      oss << request;
      response = oss.str ();
      std::clog << response << std::endl;

      Json::Value        jresp;
      const Json::Value  nib = "NIB";
      Json::Reader       readr;
      const std::string  str = response;
      bool ok   = readr.parse (str, jresp, false);
      std::clog << "-----------------------------------------------" << std::endl;
      std::clog << "jresp =>\n " << jresp << std::endl;
      std::clog << "-----------------------------------------------" << std::endl;
      std::clog << "jresp [0] =>\n " << jresp [0] << std::endl;
      std::clog << "-----------------------------------------------" << std::endl;
      std::clog << "jresp [0] ['name']  =>\n " << jresp [0] ["name"] << std::endl;
      std::clog << "-----------------------------------------------" << std::endl;
   }


} // end of namespace rabbitmq
