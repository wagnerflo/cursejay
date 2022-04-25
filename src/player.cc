#include "player.hh"
#include <miniaudio.h>

void cursejay::player::list_devices() {
  ma_result result;
  ma_context context;
  ma_device_info* pPlaybackDeviceInfos;
  ma_uint32 playbackDeviceCount;
  ma_device_info* pCaptureDeviceInfos;
  ma_uint32 captureDeviceCount;
  ma_uint32 iDevice;

  if (ma_context_init(NULL, 0, NULL, &context) != MA_SUCCESS) {
    printf("Failed to initialize context.\n");
    return;
  }

  result = ma_context_get_devices(&context, &pPlaybackDeviceInfos, &playbackDeviceCount, &pCaptureDeviceInfos, &captureDeviceCount);
  if (result != MA_SUCCESS) {
    printf("Failed to retrieve device information.\n");
    return;
  }

  printf("Playback Devices\n");
  for (iDevice = 0; iDevice < playbackDeviceCount; ++iDevice) {
    printf("    %u: %s\n", iDevice, pPlaybackDeviceInfos[iDevice].name);
  }

  printf("\n");

  printf("Capture Devices\n");
  for (iDevice = 0; iDevice < captureDeviceCount; ++iDevice) {
    printf("    %u: %s\n", iDevice, pCaptureDeviceInfos[iDevice].name);
  }

  ma_context_uninit(&context);
}
