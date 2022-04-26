#ifndef CURSEJAY_CHANNEL_MERGE_HH
#define CURSEJAY_CHANNEL_MERGE_HH

#include <miniaudio.h>

namespace cursejay {
  class channel_merge_node {
    protected:
      struct {
          ::ma_node_base base;
          channel_merge_node* obj;
      } node_base;

    public:
      channel_merge_node(ma_node_graph&);
      ~channel_merge_node();
      static void process(ma_node*, const float**, ma_uint32*, float**, ma_uint32*);
  };
}

#endif
