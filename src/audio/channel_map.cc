#include "channel_map.hh"
#include <stdexcept>

#include <fmt/core.h>

using namespace cursejay;

static ma_node_vtable channel_map_vtable = {
  channel_map_node::adaptor::process,
  NULL,
  2, // input buses
  1, // output buses
  MA_NODE_FLAG_ALLOW_NULL_INPUT
};

//    INPUT            OUTPUT
// <bus>.<channel> -> <bus>.<channel>
//     0.0         ->     0.0
//     0.0         ->     0.1
//     1.0         ->     0.2
//     1.0         ->     0.3
// OR
//     0.0         ->     0.0
//     1.0         ->     0.1

const std::size_t cmap2[] = {
  0, /* -> 0 */
  1  /* -> 1 */
};

const std::size_t cmap4[] = {
  0, /* -> 0 */
  0, /* -> 1 */
  1, /* -> 2 */
  1  /* -> 3 */
};

void channel_map_node::init(ma_node_graph& graph, ma_uint32 c) {
  out_channel_cnt = c;
  channel_map = cmap2;

  ma_uint32 inputChannels[2] = { 1, 1 };
  ma_uint32 outputChannels[1] = { out_channel_cnt };

  auto node_conf = ma_node_config_init();
  node_conf.vtable          = &channel_map_vtable;
  node_conf.pInputChannels  = inputChannels;
  node_conf.pOutputChannels = outputChannels;

  init_node_base(graph, node_conf);
}

void channel_map_node::process(ma_node*, const float** in, ma_uint32* in_cnt,
                               float** out, ma_uint32*) {
  ma_uint32 frame_cnt = *in_cnt;
  float* out_bus = out[0];

  for (std::size_t f = 0; f < frame_cnt; ++f) {
    for(std::size_t i = 0; i < out_channel_cnt; ++i) {
      out_bus[i] = in[channel_map[i]][f];
    }
    out_bus += out_channel_cnt;
  }
}
