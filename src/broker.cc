#include "broker.hh"

using namespace cursejay;

talker::talker(const void* o, class broker& b)
  : owner(o), broker(b), queue(std::make_unique<PolyM::Queue>()) {
  /* empty */
}

talker::~talker() {
  broker.leave(owner);
}

// template <typename Payload>
// PolyM::DataMsg<Payload>& talker::recv() {
//   return queue.get();
// }

std::unique_ptr<PolyM::Msg> talker::recv() {
  return queue->get();
}

talker broker::join(const void* owner) {
  talker t(owner, *this);
  talkers.emplace(owner, t);
  return t;
}

void broker::leave(const void* owner) {
  talkers.erase(owner);
}
