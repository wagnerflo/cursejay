#ifndef CURSEJAY_BROKER_HH
#define CURSEJAY_BROKER_HH

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

      template <typename Msg, typename... Args>
      void put(const Msg& msg, Args... args);

    public:
      talker(class broker&);
      talker(talker&&) = default;
      talker(const talker&) = delete;
      ~talker();

      std::unique_ptr<PolyM::Msg> recv();

      template <typename Msg, typename... Args>
      void send(const Msg& msg, Args... args);
  };

  class broker {
    friend class talker;

    protected:
      std::forward_list<talker*> talkers;

      template <typename Msg, typename...Args>
      void broadcast(const Msg& msg, Args... args);

    public:
      broker() = default;
      broker(const broker&) = delete;
      broker(broker&&) = default;

      void join(talker&);
      void leave(talker&);
  };

  template <typename Msg, typename...Args>
  void talker::put(const Msg& msg, Args... args) {
    queue->put(msg.make_data_msg(args...));
  }

  template <typename Msg, typename...Args>
  void talker::send(const Msg& msg, Args... args) {
    broker.broadcast(msg, args...);
  }

  template <typename Msg, typename...Args>
  void broker::broadcast(const Msg& msg, Args... args) {
    for (const auto& talker : talkers)
      talker->put(msg, args...);
  }
}

#endif
