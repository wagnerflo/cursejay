#ifndef CURSEJAY_BROKER_HH
#define CURSEJAY_BROKER_HH

#include <map>
#include <polym/Queue.hpp>

namespace cursejay {
  class broker;

  class talker {
    friend class broker;

    protected:
      talker(const void*, class broker&);

      const void* owner;
      class broker& broker;
      std::unique_ptr<PolyM::Queue> queue;

      void put();

    public:
      talker(talker&&) = default;
      talker(const talker&) = delete;
      ~talker();
      void send();
      std::unique_ptr<PolyM::Msg> recv();
  };

  class broker {
    friend class talker;

    protected:
      std::map<const void*,talker&> talkers;

      void leave(const void*);
      void broadcast(void*);

    public:
      broker() = default;
      broker(const broker&) = delete;
      broker(broker&&) = default;

      talker join(const void*);
  };
}

#endif
