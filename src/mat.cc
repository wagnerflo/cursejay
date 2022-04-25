#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include <stdio.h>

int main(int argc, char** argv) {
  ma_result result;
  ma_engine engine;
  ma_sound sound;

  if (argc < 2) {
    printf("No input file.\n");
    return -1;
  }

  result = ma_engine_init(NULL, &engine);
  if (result != MA_SUCCESS) {
    printf("Failed to initialize audio engine.\n");
    return -1;
  }

  // ma_engine_play_sound(&engine, argv[1], NULL);

  result = ma_sound_init_from_file(
    &engine,
    argv[1],
    MA_SOUND_FLAG_STREAM | MA_SOUND_FLAG_NO_SPATIALIZATION,
    NULL,
    NULL,
    &sound
  );
  if (result != MA_SUCCESS) {
    printf("Failed to initialize sound.\n");
    return -1;
  }

  ma_sound_set_pan(&sound, -1);
  ma_sound_start(&sound);

  printf("Press Enter to quit...\n");
  getchar();

  ma_engine_uninit(&engine);

  return 0;
}
