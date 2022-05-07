#include "ui.hh"
#include "msg.hh"

#include <cxxcurses/cxxcurses.hpp>

using namespace cursejay;
using namespace cxxcurses;

void ui::init() {

}

void ui::run() {
  talk_forever(
      MSG::UI_GETCH >> this >> &ui::handle_char
  );
}

void ui::handle_char(char) {

}
