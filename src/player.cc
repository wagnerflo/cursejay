#include "datasrc.hh"
#include "player.hh"

#include <fmt/core.h>
#include <stdexcept>

using namespace cursejay;

#define FORMAT ma_format_f32

namespace cursejay {
  class player_adaptor {
    public:
      static void callback(ma_device* dev, void* out, const void* in, ma_uint32 cnt) {
        static_cast<player*>(dev->pUserData)->data_callback(dev, out, in, cnt);
      }
  };
}

void player::data_callback(ma_device*, void* out, const void*, ma_uint32 cnt) {
  ma_node_graph_read_pcm_frames(&graph, out, cnt, NULL);
}

player::player(class conf& c, class broker& b) : obj(c, b) {
  ma_throw(
    ma_context_init(NULL, 0, NULL, &ctx),
    "Failed to initialize miniaudio context."
  );
}

player::~player() {
  ma_device_stop(&dev);
  channel_map.uninit();
  ma_node_graph_uninit(&graph, NULL);
  ma_resource_manager_uninit(&res);
  ma_device_uninit(&dev);
  ma_context_uninit(&ctx);
}

std::list<std::string> player::list_devices() {
  std::list<std::string> devices;
  for (auto& info : device_infos()) {
    devices.push_back(std::string(info.name));
  }
  return devices;
}

std::list<ma_device_info> player::device_infos() {
  ma_device_info* infos;
  ma_uint32 cnt;
  ma_throw(
    ma_context_get_devices(&ctx, &infos, &cnt, NULL, NULL),
    "Failed to retrieve device information."
  );
  return std::list<ma_device_info>(infos, infos + cnt);
}

void player::init(const std::string& device_name, ma_uint32 sample_rate) {
  // find the requested device
  auto infos = device_infos();
  auto dev_config = ma_device_config_init(ma_device_type_playback);

  for (auto& info : infos) {
    if (device_name == info.name) {
      dev_config.playback.pDeviceID = &info.id;
      break;
    }
  }

  if (dev_config.playback.pDeviceID == NULL) {
    throw std::runtime_error("Device not found");
  }

  // try to initialize device with the config we need
  dev_config.playback.format = FORMAT;
  dev_config.sampleRate      = sample_rate;
  dev_config.dataCallback    = &player_adaptor::callback;
  dev_config.pUserData       = this;

  ma_throw(
    ma_device_init(&ctx, &dev_config, &dev),
    "Failed to initialize audio device"
  );

  // get playback device channel count
  auto channel_cnt = dev.playback.channels;

  if (channel_cnt != 2 && channel_cnt != 4) {
    throw std::runtime_error(fmt::format(
      "The selected output device has {} channel(s). Only 2 and 4 channels supported.",
      channel_cnt
    ));
  }

  // build a resource manager
  auto res_conf = ma_resource_manager_config_init();
  res_conf.decodedFormat     = FORMAT;
  res_conf.decodedChannels   = 1;
  res_conf.decodedSampleRate = sample_rate;

  ma_throw(
    ma_resource_manager_init(&res_conf, &res),
    "Failed to initialize resource manager."
  );

  // start building the node graph: endpoint
  auto ng_conf = ma_node_graph_config_init(channel_cnt);

  ma_throw(
    ma_node_graph_init(&ng_conf, NULL, &graph),
    "Failed to initialize node graph."
  );

  // next node maps two inputs to channels of the single endpoint output
  channel_map.init(graph, channel_cnt);
  channel_map.attach_output_bus(ma_node_graph_get_endpoint(&graph), 0, 0);

  ma_device_start(&dev);
}

void player::run() {
  while (true) {
    // broker.recv();

  }

  
  

  // play something
  datasrc ds(graph, res, "/home/wagner/Downloads/file_example_MP3_1MG.mp3");
  ds.attach_output_bus(channel_map, 0, 0);

  printf("Press Enter to quit...\n");
  getchar();
}
