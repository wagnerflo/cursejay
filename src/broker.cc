#include "broker.hh"

using namespace cursejay;

talker::talker(const void* o, class broker& b)
  : owner(o), broker(b) {
  broker.join(owner, queue);
}

talker::~talker() {
  broker.leave(owner);
}

template <typename Payload>
PolyM::DataMsg<Payload>& talker::recv() {
  return queue.get();
}

void broker::join(const void* owner, PolyM::Queue& queue) {
  talkers.emplace(owner, queue);
}

void broker::leave(const void* owner) {
  talkers.erase(owner);
}
