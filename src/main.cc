#include "broker.hh"
#include "conf.hh"
#include "db.hh"
#include "player.hh"
#include "ui.hh"

#include <array>
#include <fmt/core.h>
#include <thread>

using namespace cursejay;

int main() {
  // objects
  broker broker;
  conf conf;

  db db(conf, broker);
  ui ui(conf, broker);
  player player(conf, broker);

  for (auto& d : player.list_devices()) {
    fmt::print("[{}]\n", d);
  }

  ui.init();
  //player.init("Traktor Audio 2 MK2, USB Audio");
  player.init("sof-hda-dsp, ");
  //player.init("HDA Intel PCH, ALC671 Analog");

  // start threads
  std::array threads = {
    std::thread(&ui::run, &ui),
    std::thread(&db::run, &db),
    std::thread(&player::run, &player)
  };

  // and join them all
  for (auto& t : threads) {
    t.join();
  }

  return 0;
}
