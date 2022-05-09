#include "ui.hh"
#include "msg.hh"

#include <fmt/core.h>
#include <ncurses.h>

using namespace cursejay;

void ui::init() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
}

ui::~ui() {
  endwin();
}

void ui::run() {
  talk_forever(
      MSG::INPUT >> this >> &ui::handle_input
  );
}

void ui::read_input() {
  while (true) {
    auto mod = KEYMOD::NONE;
    auto ch = ::getch();
    switch (ch) {
      // left Alt
      case 27:
        mod = KEYMOD::ALT_LEFT;
        ch = ::getch();
        break;

      // right Alt Gr
      case 195:
        mod = KEYMOD::ALT_RIGHT;
        ch = ::getch();
        break;
    }
    talker.send(MSG::INPUT, mod, ch);
  }
}

void ui::handle_input(KEYMOD, int) {
  ::printw("XXX");
  ::refresh();
}
