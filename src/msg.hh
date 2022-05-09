#ifndef CURSEJAY_MSG_HH
#define CURSEJAY_MSG_HH

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
      using payload_type = std::tuple<Args...>;
      using data_msg_type = PolyM::DataMsg<payload_type>;
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
                auto& dm = dynamic_cast<data_msg_type&>(msg);
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

      auto make_data_msg(Args... args) const {
        return data_msg_type(id, std::make_tuple(std::forward<Args>(args)...));
      }
  };

  typedef std::multimap<int,std::function<void(PolyM::Msg&)>> msgmap;
}

#endif
