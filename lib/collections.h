#ifndef UNDERSCORE_COLLECTIONS_H_
#define UNDERSCORE_COLLECTIONS_H_

#include <algorithm>
#include <iterator>

namespace _ {

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

}  // namespace _

#endif  // UNDERSCORE_COLLECTIONS_H_
