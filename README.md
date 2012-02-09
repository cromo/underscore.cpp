Underscore.cpp
==============

Underscore.cpp is an effort to bring as much of the functionality of Underscore.js to C++ as possible.


Installation
------------

Unlike it's name would suggests, Underscore.cpp is a header only library. That means that you just have to add it to your include path to begin using it.

Usage
-----

```cpp
std::vector<int> numbers;
for (int i = 0; i < 10; i++) {
  numbers.push_back(i);
}

// Display is a function that takes one argument of type int.
_::each(numbers, display);
```

A number of the Underscore functions have yet to be implemented. The functions that have been implemented in some capacity are:

* each
* map
* reduce
* reduce_right
* find
* filter
* reject
* all
* any
* include
* max
* min
* zip
* chain
* value
