#include <iostream>

// Ourselves:
#include "connection.h"
#include "channel.h"


namespace rabbitmq {


   connection::connection (const connection_parameters & params_)
   {
       _params_ = params_;
       _chan1_.reset (new channel (*this, 1));
      return;
   }


   bool connection::is_ok () const
   {
      return _chan1_->is_ok ();
   }


   const connection_parameters & connection::get_connection_parameters () const
   {
      return _params_;
   }


   const channel & connection::get_channel () const
   {
      return *_chan1_;
   }


   channel & connection::grab_channel ()
   {
      return *_chan1_;
   }


} // end of namespace rabbitmq
