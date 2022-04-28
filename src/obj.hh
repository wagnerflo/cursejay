#ifndef CURSEJAY_OBJ_HH
#define CURSEJAY_OBJ_HH

#include "broker.hh"
#include "conf.hh"

namespace cursejay {
  class obj {
    protected:
      class conf& conf;
      class talker talker;

    public:
      obj(class conf&, class broker&);
      virtual void run() = 0;
  };
}

#endif
