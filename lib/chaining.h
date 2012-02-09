#ifndef UNDERSCORE_CHAINING_H_
#define UNDERSCORE_CHAINING_H_

namespace _ {

template<typename Container>
class Wrapper;

// chain
template<typename Container>
Wrapper<Container> chain(Container container) {
  return Wrapper<Container>(container);
}

// value
template<typename Container>
typename Container::value_type value(Wrapper<Container>& wrapper) {
  return wrapper.value();
}

template<typename Container>
class Wrapper
{
 public:
  typedef Container value_type;
  Wrapper(Container container) : container_(container) {
  }

  Container value() {
    return container_;
  }

  template<typename Function>
  Wrapper& each(Function function) {
    _::each(container_, function);
    return *this;
  }

  template<typename ResultContainer, typename Function>
  Wrapper<ResultContainer> map(Function function) {
    return chain(
        _::map<ResultContainer>(container_, function));
  }

  template<typename Function, typename Memo>
  Wrapper<Memo> reduce(Function function, Memo memo) {
    return chain(_::reduce(container_, function, memo));
  }
 private:
  Container container_;
};

}  // namespace _

#endif  // UNDERSCORE_CHAINING_H_
