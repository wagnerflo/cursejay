#include "channel_map.hh"
#include "player.hh"

#include <fmt/core.h>
#include <stdexcept>

using namespace cursejay;

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
  if (ma_context_init(NULL, 0, NULL, &ctx) != MA_SUCCESS) {
    throw std::runtime_error("");
  }
}

player::~player() {
  ma_context_uninit(&ctx);
}

std::list<std::string> player::list_devices() {
  std::list<std::string> devices;
  for (auto& info : device_infos()) {
    devices.push_back(std::string(info.name));
  }
  return devices;
}

void player::init(const std::string& device_name) {
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

  dev_config.playback.format = ma_format_f32;
  dev_config.sampleRate = 48000;
  dev_config.dataCallback = &player_adaptor::callback;
  dev_config.pUserData = this;

  ma_device dev;
  if (ma_device_init(&ctx, &dev_config, &dev) != MA_SUCCESS) {
    throw std::runtime_error("Failed to initialize audio device");
  }

  auto channels = dev.playback.channels;

  if (channels != 2 && channels != 4) {
    throw std::runtime_error(fmt::format(
      "The selected output device has {} channel(s). Only 2 and 4 channels supported.",
      channels
    ));
  }

  // start building the node graph: endpoint
  auto ng_conf = ma_node_graph_config_init(channels);

  if (ma_node_graph_init(&ng_conf, NULL, &graph) != MA_SUCCESS) {
    throw std::runtime_error("Failed to initialize node graph.");
  }

  // next node maps two inputs to channels of the single endpoint output
  channel_map_node channel_map(graph, channels);
  channel_map.attach_output_bus(ma_node_graph_get_endpoint(&graph), 0, 0);

  // ...
  auto dec_conf = ma_decoder_config_init(
    dev_config.playback.format, 1, dev_config.sampleRate
  );

  ma_decoder decoder;
  ma_decoder_init_file(
    "/home/wagnerflo/file_example_MP3_1MG.mp3",
    &dec_conf,
    &decoder
  );

  auto data_src_conf = ma_data_source_node_config_init(&decoder);

  ma_data_source_node data_src_node;
  ma_data_source_node_init(&graph, &data_src_conf, NULL, &data_src_node);

  // ma_node_attach_output_bus(&data_src_node, 0, channel_map.node_base, 0);
  // channel_map.attach_input_bus(&data_src_node, 0, 0);
  channel_map.attach_input_bus(&data_src_node, 0, 1);

  ma_device_start(&dev);

  printf("Press Enter to quit...\n");
  getchar();

}

void player::run() {
  // std::cout << "PLAYER RUNNING" << std::endl;

  // ma_sound sound;
  // ma_sound_init_from_file(
  //   &engine,
  //   "/home/wagnerflo/file_example_MP3_1MG.mp3",
  //   MA_SOUND_FLAG_STREAM | MA_SOUND_FLAG_NO_SPATIALIZATION,
  //   NULL,
  //   NULL,
  //   &sound
  // );

  // ma_sound_start(&sound);
  // printf("Press Enter to quit...\n");
  // getchar();
  // ma_sound_uninit(&sound);
}

std::list<ma_device_info> player::device_infos() {
  ma_device_info* infos;
  ma_uint32 cnt;
  if (ma_context_get_devices(&ctx, &infos, &cnt, NULL, NULL) != MA_SUCCESS) {
    throw std::runtime_error("Failed to retrieve device information.");
  }
  return std::list<ma_device_info>(infos, infos + cnt);
}
