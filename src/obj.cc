#include "conf.hh"
#include "db.hh"

cursejay::obj::obj(cursejay::conf& c, PolyM::Queue& q)
  : conf(c), q(q) {
  /* empty */
}
