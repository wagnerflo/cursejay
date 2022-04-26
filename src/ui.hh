#ifndef CURSEJAY_UI_HH
#define CURSEJAY_UI_HH

#include "obj.hh"

namespace cursejay {
  class ui : public obj {
    public:
      using obj::obj;
      void run();
  };
}

#endif
