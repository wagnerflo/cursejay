#include "obj.hh"
#include <polym/Msg.hpp>
#include <tuple>

#include <iostream>

using namespace cursejay;

obj::obj(class conf& c, class broker& b)
  : conf(c), talker(b) {
    /* empty */
}

void obj::_talk_forever(msgmap&& map) {
  while (true) {
    auto msg = talker.recv();
    auto [start, end] = map.equal_range(msg->getMsgId());
    for (auto it = start; it != end; it++)
      it->second(*msg);
  }
}
