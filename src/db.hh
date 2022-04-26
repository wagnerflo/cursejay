#ifndef CURSEJAY_DB_HH
#define CURSEJAY_DB_HH

#include "obj.hh"

namespace cursejay {
  class db : public obj {
    public:
      using obj::obj;
      void run();
  };
}

#endif
