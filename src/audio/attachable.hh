#ifndef CURSEJAY_ATTACHABLE_HH
#define CURSEJAY_ATTACHABLE_HH

#include "miniaudio.hh"

namespace cursejay {
  class attachable {
    protected:
      virtual ma_node* get_ma_node() = 0;

    public:
      void attach_output_bus(attachable& other, ma_uint32 out, ma_uint32 in) {
        attach_output_bus(other.get_ma_node(), out, in);
      }

      void attach_output_bus(ma_node* other, ma_uint32 out, ma_uint32 in) {
        ma_throw(
          ma_node_attach_output_bus(get_ma_node(), out, other, in),
          "Node output bus attach error."
        );
      }
  };
}

#endif
