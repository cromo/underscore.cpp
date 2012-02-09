#ifndef UNDERSCORE_ARRAYS_H_
#define UNDERSCORE_ARRAYS_H_

#include <vector>
#include <utility>

namespace _ {

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

}  // namespace _

#endif  // UNDERSCORE_ARRAYS_H_
