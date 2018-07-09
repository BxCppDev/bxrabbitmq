// -*- mode: c++; -*-

#ifndef BXRABBITMQ_CORE_H
#define BXRABBITMQ_CORE_H

// Standard library:
// #include <string>
// #include <memory>

namespace rabbitmq {

  class core
  {
  public:
    
    enum logging_level_type {
      LOGGING_MUTE = 0,
      LOGGING_FATAL = 1,
      LOGGING_ERROR = 2,
      LOGGING_WARNING = 3,
      LOGGING_NOTICE = 4,
      LOGGING_DEBUG = 5
    };

    bool is_debug() const;

    bool is_notice() const;

    bool is_warning() const;
    
    logging_level_type logging_level = LOGGING_MUTE;

    static const core & const_instance();
 
    static core & instance();
     
  private:

    core();
   
    static core & _instance_();
    
  };

} // end of namespace rabbitmq

#endif // BXRABBITMQ_CORE_H
