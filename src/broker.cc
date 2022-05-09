#include "broker.hh"

using namespace cursejay;

talker::talker(class broker& b)
  : broker(b), queue(std::make_unique<PolyM::Queue>()) {
  broker.join(*this);
}

talker::~talker() {
  broker.leave(*this);
}

std::unique_ptr<PolyM::Msg> talker::recv() {
  return queue->get();
}

void broker::join(talker& t) {
  talkers.push_front(&t);
}

void broker::leave(talker& t) {
  talkers.remove(&t);
}
