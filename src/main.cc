#include "conf.hh"
#include "db.hh"
#include "ui.hh"
#include "player.hh"

#include <array>
#include <thread>

#include "polym/Queue.hpp"

using namespace cursejay;

int main() {
  player::list_devices();

  // // objects
  // PolyM::Queue q;
  // cursejay::conf conf;

  // cursejay::db db(conf, q);
  // cursejay::ui ui(conf, q);
  // // cursejay::player player(conf, broker);

  // // start threads
  // std::array threads = {
  //   std::thread(&cursejay::db::start, &db)
  // };

  // // and join them all
  // for (auto& t : threads) {
  //   t.join();
  // }

  return 0;
}
