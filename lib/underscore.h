#ifndef UNDERSCORE_UNDERSCORE_H_
#define UNDERSCORE_UNDERSCORE_H_

#include <algorithm>
#include <iterator>
#include <vector>
#include <utility>

namespace underscore {

// Collections

// each
template<typename Container, typename Function>
void each(Container container, Function function) {
  std::for_each(container.begin(), container.end(), function);
}

// map
// TODO(Cristian): make this not rely on back_inserter
template<typename ResultContainer, typename Container, typename Function>
ResultContainer map(Container container, Function function) {
  ResultContainer result;
  std::transform(container.begin(), 
      container.end(), 
      std::back_inserter(result), 
      function);
  return result;
}

// reduce
template<typename Container, typename Function, typename Memo>
Memo reduce(const Container container, Function function, Memo memo) {
  for (typename Container::const_iterator i = container.begin();
      i != container.end();
      ++i) {
    memo = function(memo, *i);
  }
  return memo;
}

// reduce_right
template<typename Container, typename Function, typename Memo>
Memo reduce_right(const Container container, 
    Function function, 
    Memo memo) {
  for (typename Container::const_reverse_iterator i = container.rbegin();
      i != container.rend();
      ++i) {
    memo = function(memo, *i);
  }
  return memo;
}

// find
template<typename Container, typename Predicate>
typename Container::iterator find(Container container, 
    Predicate predicate) {
  return find_if(container.begin(), container.end(), predicate);
}

// filter
// TODO(Cristian): make this not rely on push_back.
template<typename Container, typename Predicate>
Container filter(Container container, Predicate predicate) {
  Container result;
  for (typename Container::const_iterator i = container.begin();
      i != container.end();
      ++i) {
    if (predicate(*i)) {
      result.push_back(*i);
    }
  }
  return result;
}

// reject
// TODO(Cristian): make this not rely on push_back.
template<typename Container, typename Predicate>
Container reject(Container container, Predicate predicate) {
  Container result;
  for (typename Container::const_iterator i = container.begin();
      i != container.end();
      ++i) {
    if (!predicate(*i)) {
      result.push_back(*i);
    }
  }
  return result;
}

// all
template<typename Container, typename Predicate>
bool all(Container container, Predicate predicate) {
  for (typename Container::const_iterator i = container.begin();
      i != container.end();
      ++i) {
    if (!predicate(*i)) {
      return false;
    }
  }
  return true;
}

// any
template<typename Container, typename Predicate>
bool any(Container container, Predicate predicate) {
  for (typename Container::const_iterator i = container.begin();
      i != container.end();
      ++i) {
    if (predicate(*i)) {
      return true;
    }
  }
  return false;
}

// include
template<typename Container>
bool include(Container container, typename Container::value_type value) {
  return std::find(container.begin(), container.end(), value) !=
      container.end();
}

// invoke (Can be done with map and functors)
// pluck (same as above)

// max
// TODO(Cristian): make this accept a functor.
template<typename Container>
typename Container::iterator max(Container container) {
  typename Container::iterator max = container.begin();
  for (typename Container::iterator i = container.begin();
      i != container.end();
      ++i) {
    if (*i > *max) {
      max = i;
    }
  }
  return max;
}

// min
// TODO(Cristian): make this accept a functor.
template<typename Container>
typename Container::iterator min(Container container) {
  typename Container::iterator min = container.begin();
  for (typename Container::iterator i = container.begin();
      i != container.end();
      ++i) {
    if (*i < *min) {
      min = i;
    }
  }
  return min;
}

// sort_by
template<typename Container, typename Function>
Container sort_by(Container container, Function function) {
  std::vector<typename Container::value_type> to_sort(container.begin(),
      container.end());
  std::sort(to_sort.begin(), to_sort.end(), function);
  return Container(to_sort.begin(), to_sort.end());
}

// group_by
// sorted_index
// shuffle

// to_array
template<typename Container>
typename Container::value_type* to_array(Container container) {
  typename Container::value_type* array =
      new typename Container::value_type[container.size()];
  struct {
    int numeric;
    typename Container::iterator iterator;
  } i;
  for (i.numeric = 0, i.iterator = container.begin();
      i.iterator != container.end();
      ++i.numeric, ++i.iterator) {
    array[i.numeric] = *i.iterator;
  }

  return array;
}

// size
template<typename Container>
int size(Container container) {
  return container.size();
}

// Arrays

// first
// initial
// last
// rest
// compact
// flatten
// without
// union
// intersection
// difference
// uniq
// zip
// indexOf
// lastIndexOf
// range

// zip
template<typename Collection1, typename Collection2>
std::vector<
  std::pair<typename Collection1::value_type, 
            typename Collection2::value_type> > zip(
    const Collection1& collection1,
    const Collection2& collection2) {
  std::vector<
    std::pair<typename Collection1::value_type,
              typename Collection2::value_type> > result;
  typename Collection1::const_iterator left = collection1.begin();
  typename Collection2::const_iterator right = collection2.begin();
  while (left != collection1.end() && right != collection2.end()) {
    result.push_back(std::make_pair(*left++, *right++));
  }
  return result;
}

// Functions

// bind
// bindAll
// memoize
// delay
// defer
// throttle
// debounce
// once
// after
// wrap
// compose

// Objects

// keys
// values
// functions
// extend
// defaults
// clone
// tap
// has
// isEqual
// isEmpty
// isElement
// isArray
// isArguments
// isFunction
// isString
// isNumber
// isBoolean
// isDate
// isRegExp
// isNaN
// isNull
// isUndefined

// Utility

// noConflict
// identity
// times
// mixin
// uniqueId
// escape
// template

// Chaining

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
    underscore::each(container_, function);
    return *this;
  }

  template<typename ResultContainer, typename Function>
  Wrapper<ResultContainer> map(Function function) {
    return chain(
        underscore::map<ResultContainer>(container_, function));
  }

  template<typename Function, typename Memo>
  Wrapper<Memo> reduce(Function function, Memo memo) {
    return chain(underscore::reduce(container_, function, memo));
  }
 private:
  Container container_;
};

}  // namespace underscore

namespace _ = underscore;

#endif  // UNDERSCORE_UNDERSCORE_H_
