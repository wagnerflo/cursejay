#ifndef CURSEJAY_BROKER_HH
#define CURSEJAY_BROKER_HH

#include <polym/Queue.hpp>
#include <map>

namespace cursejay {
  class broker;

  class talker {
    protected:
      const void* owner;
      class broker& broker;
      PolyM::Queue queue;

      void put();

    public:
      talker(const void*, class broker&);
      ~talker();
      void send();

      template <typename Payload>
      PolyM::DataMsg<Payload>& recv();
  };

  class broker {
    friend class talker;

    protected:
      std::map<const void*,PolyM::Queue&> talkers;
      void join(const void*, PolyM::Queue&);
      void leave(const void*);
      void broadcast(void*);
  };


}

#endif
