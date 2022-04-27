#ifndef CURSEJAY_PLAYER_HH
#define CURSEJAY_PLAYER_HH

#include "audio/channel_map.hh"
#include "audio/miniaudio.hh"
#include "obj.hh"

#include <list>
#include <string>

namespace cursejay {
  class player : public obj {
    friend class player_adaptor;

    protected:
      ma_context ctx;
      ma_device dev;
      ma_resource_manager res;
      ma_node_graph graph;
      channel_map_node channel_map;

      std::list<ma_device_info> device_infos();
      void data_callback(ma_device*, void*, const void*, ma_uint32);

    public:
      player(class conf&, class broker&);
      ~player();

      std::list<std::string> list_devices();

      void init(const std::string&, ma_uint32 = 48000);
      void run();
  };
}

#endif
