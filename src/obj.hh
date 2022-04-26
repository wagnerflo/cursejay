#ifndef CURSEJAY_OBJ_HH
#define CURSEJAY_OBJ_HH

#include "broker.hh"
#include "conf.hh"

namespace cursejay {
  class obj {
    protected:
      cursejay::conf& conf;
      cursejay::broker& broker;

    public:
      obj(class conf&, class broker&);
      virtual void run() = 0;
  };
}

#endif
