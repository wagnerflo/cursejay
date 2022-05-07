#ifndef CURSEJAY_MSGID_HH
#define CURSEJAY_MSGID_HH

#include <functional>
#include <map>
#include <memory>
#include <polym/Queue.hpp>
#include <type_traits>

namespace cursejay {
  namespace detail {
    static int msg_counter = 0;
  }

  template <typename... Args>
  class msg {
    public:
      const int id = []() { return ++detail::msg_counter; }();

      template <typename Cls>
      auto operator>>(Cls& obj) const {
        static_assert(std::is_class<Cls>::value, "LOL");
        class helper {
          public:
            Cls& obj;
            int id;
            helper(Cls& o, int i) : obj(o), id(i) { }
            auto operator>>(void(Cls::*memfn)(Args...)) {
              auto& objref = obj;
              return std::make_pair(id, [&objref,memfn](PolyM::Msg& msg) {
                auto& dm = dynamic_cast<PolyM::DataMsg<std::tuple<Args...>>&>(msg);
                auto args = dm.getPayload();
                std::apply(memfn, std::tuple_cat(std::make_tuple(&objref), args));
              });
            }
        };
        return helper(obj, id);
      }

      template <typename Cls>
      auto operator>>(Cls* obj) const {
        return *this >> *obj;
      }
  };

  typedef std::multimap<int,std::function<void(PolyM::Msg&)>> msgmap;

  class MSG {
    public:
      inline static const  msg<>                 EXIT;
      inline static const  msg<char>             UI_GETCH;
  };
}

#endif
