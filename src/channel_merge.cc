#include "channel_merge.hh"
#include <stdexcept>

using namespace cursejay;

void channel_merge_node::process(ma_node* node_base,
                                 const float** in, ma_uint32* in_cnt,
                                 float** out, ma_uint32* out_cnt) {
  auto cmn = static_cast<decltype(channel_merge_node::node_base)*>(node_base)->obj;
}

static ma_node_vtable channel_merge_vtable = {
  channel_merge_node::process,
  NULL,
  2, // input buses
  1, // output bus.
  MA_NODE_FLAG_ALLOW_NULL_INPUT
};

//    INPUT            OUTPUT
// <bus>.<channel> -> <channel>
//     0.0         -> 0
//     0.1         -> 1
//     1.0         -> 2
//     1.1         -> 3

//     0.0         -> 0
//     0.

channel_merge_node::channel_merge_node(ma_node_graph& graph) {
  node_base.obj = this;

  ma_uint32 inputChannels[2] = { 1, 1 };
  ma_uint32 outputChannels[1];

  outputChannels[0] = 4;

  auto node_conf = ma_node_config_init();
  node_conf.vtable          = &channel_merge_vtable;
  node_conf.pInputChannels  = inputChannels;
  node_conf.pOutputChannels = outputChannels;

  if (ma_node_init(&graph, &node_conf, NULL, &node_base) != MA_SUCCESS)
    throw std::runtime_error("channel_merge init error");
}

channel_merge_node::~channel_merge_node() {
  ma_node_uninit(&node_base, NULL);
}
