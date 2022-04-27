#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.hh"
#include <stdexcept>

void cursejay::ma_throw(ma_result result, const std::string& msg) {
  if (result != MA_SUCCESS)
    throw std::runtime_error(msg);
}
