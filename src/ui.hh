#ifndef CURSEJAY_UI_HH
#define CURSEJAY_UI_HH

#include "obj.hh"
#include "msg.hh"

namespace cursejay {
  enum class KEYMOD {
    NONE,
    ALT_LEFT,
    ALT_RIGHT,
  };

  class ui : public obj {
    public:
      class MSG {
        public:
          inline static const msg<KEYMOD,int> INPUT;
      };

      using obj::obj;
      ~ui();

      void init();
      void run();
      void read_input();

    protected:
      void handle_input(KEYMOD, int);
  };
}

#endif
