#ifndef CURSEJAY_OBJ_HH
#define CURSEJAY_OBJ_HH

#include "broker.hh"
#include "conf.hh"
#include "msg.hh"

#include <iostream>

namespace cursejay {
  class obj {
    protected:
      class conf& conf;
      class talker talker;

      void _talk_forever(msgmap&&);

    public:
      obj(class conf&, class broker&);

      template <typename... Args> void talk_forever(Args... args) {
        _talk_forever({ args... });
      }

      void talk_forever(msgmap&& map) {
        _talk_forever(std::move(map));
      }
  };
}

#endif
