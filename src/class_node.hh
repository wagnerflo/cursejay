#ifndef CURSEJAY_CLASS_NODE_HH
#define CURSEJAY_CLASS_NODE_HH

#include <miniaudio.h>
#include <stdexcept>

namespace cursejay {
  template <typename T>
  class class_node {
    public:
      class adaptor {
        public:
          static void process(ma_node* node_base,
                              const float** in, ma_uint32* in_cnt,
                              float** out, ma_uint32* out_cnt) {
            auto obj = static_cast<decltype(T::node_base)*>(node_base)->obj;
            obj->process(node_base, in, in_cnt, out, out_cnt);
          }
      };

    protected:
      struct {
          ma_node_base base;
          T* obj;
      } node_base;

      void init_node_base(ma_node_graph& graph, ma_node_config& node_conf) {
        if (ma_node_init(&graph, &node_conf, NULL, &node_base) != MA_SUCCESS)
          throw std::runtime_error("node init error");
      }
  };
}

#endif
