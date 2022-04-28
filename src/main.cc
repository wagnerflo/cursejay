#include "broker.hh"
#include "conf.hh"
#include "db.hh"
#include "player.hh"
#include "ui.hh"

#include <array>
#include <fmt/core.h>
#include <thread>

int main() {
  // objects
  cursejay::broker broker;
  cursejay::conf conf;

  cursejay::db db(conf, broker);
  cursejay::ui ui(conf, broker);
  cursejay::player player(conf, broker);

  for (auto& d : player.list_devices()) {
    fmt::print("[{}]\n", d);
  }

  //player.init("Traktor Audio 2 MK2, USB Audio");
  player.init("sof-hda-dsp, ");
  //player.init("HDA Intel PCH, ALC671 Analog");

  // start threads
  std::array threads = {
    std::thread(&cursejay::db::run, &db),
    std::thread(&cursejay::player::run, &player)
  };

  // and join them all
  for (auto& t : threads) {
    t.join();
  }

  return 0;
}
