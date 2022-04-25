#ifndef CURSEJAY_OBJ_HH
#define CURSEJAY_OBJ_HH

#include "conf.hh"
#include <polym/Queue.hpp>

namespace cursejay {
  class obj {
    protected:
      cursejay::conf& conf;
      PolyM::Queue& q;

    public:
      obj(class conf&, class PolyM::Queue&);
      virtual void start() = 0;
  };
}

#endif
