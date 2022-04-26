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

      void attach_output_bus(ma_node* other, ma_uint32 out_idx, ma_uint32 inp_idx) {
        if (ma_node_attach_output_bus(&node_base, out_idx, other, inp_idx) != MA_SUCCESS)
          throw std::runtime_error("node output bus attach error");
      }

      void attach_input_bus(ma_node* other, ma_uint32 out_idx, ma_uint32 inp_idx) {
        if (ma_node_attach_output_bus(other, out_idx, &node_base, inp_idx) != MA_SUCCESS)
          throw std::runtime_error("node input bus attach error");
      }

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
