#include "channel_merge.hh"
#include <stdexcept>

using namespace cursejay;

static ma_node_vtable channel_merge_vtable = {
  channel_merge_node::adaptor::process,
  NULL,
  2, // input buses
  1, // output buses
  MA_NODE_FLAG_ALLOW_NULL_INPUT
};

//    INPUT            OUTPUT
// <bus>.<channel> -> <channel>
//     0.0         -> 0
//     0.0         -> 1
//     1.0         -> 2
//     1.0         -> 3
// OR
//     0.0         -> 0
//     1.0         -> 1

channel_merge_node::channel_merge_node(ma_node_graph& graph) {
  node_base.obj = this;

  ma_uint32 inputChannels[2] = { 1, 1 };
  ma_uint32 outputChannels[1];

  outputChannels[0] = 4;

  auto node_conf = ma_node_config_init();
  node_conf.vtable          = &channel_merge_vtable;
  node_conf.pInputChannels  = inputChannels;
  node_conf.pOutputChannels = outputChannels;

  init_node_base(graph, node_conf);
}

channel_merge_node::~channel_merge_node() {
  ma_node_uninit(&node_base, NULL);
}

void channel_merge_node::process(ma_node*, const float**, ma_uint32*,
                                 float**, ma_uint32*) {

}
