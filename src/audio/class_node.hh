#ifndef CURSEJAY_CLASS_NODE_HH
#define CURSEJAY_CLASS_NODE_HH

#include "attachable.hh"
#include "miniaudio.hh"
#include <stdexcept>

namespace cursejay {
  template <typename T>
  class class_node : public attachable {
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

      class_node() : node_base { {}, static_cast<T*>(this) } { /* empty */ }
      ~class_node() { /* empty */ }

      ma_node* get_ma_node() {
        return &node_base;
      }

      void uninit() {
        ma_node_uninit(&node_base, NULL);
      }

    protected:
      struct {
          ma_node_base base;
          T* obj;
      } node_base;

      void init_node_base(ma_node_graph& graph, ma_node_config& node_conf) {
        ma_throw(
          ma_node_init(&graph, &node_conf, NULL, &node_base),
          "Failed to initialize node."
        );
      }
  };
}

#endif
