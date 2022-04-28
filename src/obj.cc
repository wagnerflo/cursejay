#include "obj.hh"

using namespace cursejay;

obj::obj(class conf& c, class broker& b)
  : conf(c), talker(this, b) {
  /* empty */
}
