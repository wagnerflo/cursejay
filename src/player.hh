#ifndef CURSEJAY_PLAYER_HH
#define CURSEJAY_PLAYER_HH

#include "obj.hh"

#include <list>
#include <miniaudio.h>
#include <string>

namespace cursejay {
  class player : public obj {
    friend class player_adaptor;

    protected:
      ma_context ctx;
      ma_node_graph graph;

      std::list<ma_device_info> device_infos();
      void data_callback(ma_device*, void*, const void*, ma_uint32);

    public:
      player(class conf&, class broker&);
      ~player();

      std::list<std::string> list_devices();

      void init(const std::string&);
      void run();
  };
}

#endif
