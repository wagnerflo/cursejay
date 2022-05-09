#ifndef CURSEJAY_BROKER_HH
#define CURSEJAY_BROKER_HH

#include "msg.hh"
#include <forward_list>
#include <polym/Queue.hpp>

namespace cursejay {
  class talker;
  class broker;

  class talker {
    friend class broker;

    protected:
      class broker& broker;
      std::unique_ptr<PolyM::Queue> queue;

      void put(PolyM::Msg&& m);

    public:
      talker(class broker&);
      talker(talker&&) = default;
      ~talker();

      std::unique_ptr<PolyM::Msg> recv();

      template <typename... Args>
      void send(const msg<Args...>&, Args...);
  };

  class broker {
    friend class talker;

    protected:
      std::forward_list<talker*> talkers;

      template <typename...Args>
      void broadcast(const msg<Args...>& msg, Args... args);

    public:
      broker() = default;
      broker(broker&&) = default;

      void join(talker&);
      void leave(talker&);
  };

  template <typename...Args>
  void talker::send(const msg<Args...>& m, Args... args) {
    broker.broadcast(m, std::forward<Args>(args)...);
  }

  template <typename...Args>
  void broker::broadcast(const msg<Args...>& msg, Args... args) {
    for (const auto& talker : talkers)
      talker->put(msg.make_data_msg(args...));
  }
}

#endif
