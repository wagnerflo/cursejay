#ifndef CURSEJAY_CHANNEL_MERGE_HH
#define CURSEJAY_CHANNEL_MERGE_HH

#include "class_node.hh"
#include <miniaudio.h>

namespace cursejay {
  class channel_merge_node : public class_node<channel_merge_node> {
    friend class class_node::adaptor;

    protected:
      static void process(ma_node*, const float**, ma_uint32*, float**, ma_uint32*);

    public:
      channel_merge_node(ma_node_graph&);
      ~channel_merge_node();
  };
}

#endif
