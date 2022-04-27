#ifndef CURSEJAY_DATASRC_HH
#define CURSEJAY_DATASRC_HH

#include "audio/attachable.hh"
#include "audio/miniaudio.hh"
#include <string>

namespace cursejay {
  class datasrc : public attachable {
    protected:
      const std::string filename;
      ma_resource_manager_data_source data_src;
      ma_data_source_node node;

      ma_node* get_ma_node();

    public:
      datasrc(ma_node_graph&, ma_resource_manager&, const std::string&);
      ~datasrc();
  };
}

#endif
