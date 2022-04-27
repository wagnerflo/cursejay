#include "datasrc.hh"

using namespace cursejay;

#define DATA_SOURCE_FLAGS \
  MA_RESOURCE_MANAGER_DATA_SOURCE_FLAG_DECODE | \
  MA_RESOURCE_MANAGER_DATA_SOURCE_FLAG_ASYNC  | \
  MA_RESOURCE_MANAGER_DATA_SOURCE_FLAG_STREAM | \
  MA_RESOURCE_MANAGER_DATA_SOURCE_FLAG_WAIT_INIT

datasrc::datasrc(ma_node_graph& graph, ma_resource_manager& res, const std::string& f)
  : filename(f) {
  ma_throw(
    ma_resource_manager_data_source_init(
      &res, filename.c_str(), DATA_SOURCE_FLAGS, NULL, &data_src
    ),
    "Failed to initialize data source."
  );

  auto node_conf = ma_data_source_node_config_init(&data_src);
  ma_throw(
    ma_data_source_node_init(&graph, &node_conf, NULL, &node),
    "Failed to initialize data source node."
  );
}

datasrc::~datasrc() {
  ma_data_source_node_uninit(&node, NULL);
  ma_resource_manager_data_source_uninit(&data_src);
}

ma_node* datasrc::get_ma_node() {
  return &node;
}
