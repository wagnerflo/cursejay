#ifndef CURSEJAY_CHANNEL_MAP_HH
#define CURSEJAY_CHANNEL_MAP_HH

#include "class_node.hh"
#include "miniaudio.hh"
#include <span>

namespace cursejay {
  typedef std::span<const std::size_t> channel_map_t;

  class channel_map_node : public class_node<channel_map_node> {
    friend class class_node::adaptor;

    protected:
      ma_uint32 out_channel_cnt;
      channel_map_t channel_map;

      void process(ma_node*, const float**, ma_uint32*, float**, ma_uint32*);

    public:
      void init(ma_node_graph&, ma_uint32);
  };
}

#endif
