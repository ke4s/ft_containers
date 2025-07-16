# Project Documentation

## Table of Contents
- [Vector](#vector)
- [Map](#map)
- [Set](#set)
- [Stack](#stack)
- [Utilities](#utilities)

---

## Vector

### `ft::vector<T, Allocator>`
A dynamic array implementation similar to `std::vector`.

**Template Parameters:**
- `T`: Type of elements.
- `Allocator`: Memory allocator (default: `std::allocator<T>`).

**Features:**
- Dynamic resizing
- Random access iterators
- Efficient insertion/removal at the end
- STL-compatible interface

**Example Usage:**
```cpp
ft::vector<int> v;
v.push_back(1);
v.push_back(2);
for (ft::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << std::endl;
}
```

**Key Methods:**
- Constructors: default, fill, range, copy
- `operator=`, `assign`
- `at`, `operator[]`, `front`, `back`, `data`
- `begin`, `end`, `rbegin`, `rend`
- `empty`, `size`, `capacity`, `max_size`
- `reserve`, `clear`, `insert`, `erase`, `push_back`, `pop_back`, `resize`, `swap`
- Comparison operators

**Notes:**
- Throws `std::out_of_range` on invalid access in `at()`.
- Uses doubling strategy for capacity growth.

---

## Map

### `ft::map<Key, T, Compare, Alloc>`
An associative container that stores key-value pairs in sorted order by key.

**Template Parameters:**
- `Key`: Key type.
- `T`: Mapped value type.
- `Compare`: Key comparison functor (default: `std::less<Key>`).
- `Alloc`: Allocator (default: `std::allocator<ft::pair<const Key, T>>`).

**Features:**
- Unique keys
- Logarithmic time insert, erase, find
- Bidirectional iterators
- STL-compatible interface

**Example Usage:**
```cpp
ft::map<std::string, int> m;
m["apple"] = 5;
m["banana"] = 3;
for (ft::map<std::string, int>::iterator it = m.begin(); it != m.end(); ++it) {
    std::cout << it->first << ": " << it->second << std::endl;
}
```

**Key Methods:**
- Constructors: default, range, copy
- `operator=`, `get_allocator`
- `at`, `operator[]`
- `begin`, `end`, `rbegin`, `rend`
- `empty`, `size`, `max_size`
- `insert`, `erase`, `swap`, `clear`
- `find`, `count`, `lower_bound`, `upper_bound`, `equal_range`
- `key_comp`, `value_comp`
- Comparison operators

**Notes:**
- `operator[]` inserts a default value if key is not found.
- Throws `std::out_of_range` in `at()` if key is not found.

---

## Set

### `ft::set<Key, Compare, Allocator>`
An associative container that contains a sorted set of unique keys.

**Template Parameters:**
- `Key`: Key type.
- `Compare`: Key comparison functor (default: `std::less<Key>`).
- `Allocator`: Allocator (default: `std::allocator<Key>`).

**Features:**
- Unique keys
- Logarithmic time insert, erase, find
- Bidirectional iterators
- STL-compatible interface

**Example Usage:**
```cpp
ft::set<int> s;
s.insert(3);
s.insert(1);
s.insert(2);
for (ft::set<int>::iterator it = s.begin(); it != s.end(); ++it) {
    std::cout << *it << std::endl;
}
```

**Key Methods:**
- Constructors: default, range, copy
- `operator=`, `get_allocator`
- `begin`, `end`, `rbegin`, `rend`
- `empty`, `size`, `max_size`
- `insert`, `erase`, `swap`, `clear`
- `find`, `count`, `lower_bound`, `upper_bound`, `equal_range`
- `key_comp`, `value_comp`
- Comparison operators

**Notes:**
- All elements are unique and sorted by key.

---

## Stack

### `ft::stack<T, Container>`
A container adapter that gives the functionality of a stack (LIFO structure).

**Template Parameters:**
- `T`: Type of elements.
- `Container`: Underlying container type (default: `ft::vector<T>`).

**Features:**
- LIFO semantics (push, pop, top)
- Uses any container with `back()`, `push_back()`, `pop_back()`, etc.
- STL-compatible interface

**Example Usage:**
```cpp
ft::stack<int> s;
s.push(1);
s.push(2);
std::cout << s.top() << std::endl; // 2
s.pop();
std::cout << s.top() << std::endl; // 1
```

**Key Methods:**
- Constructors: default, copy
- `top`, `push`, `pop`
- `empty`, `size`
- Comparison operators

**Notes:**
- Underlying container can be customized.

---

## Utilities

### Iterators
- `random_access_iterator`, `reverse_iterator`, `iterator_traits`, etc. provide STL-compatible iterator support for containers.

### Algorithms
- `equal`, `lexicographical_compare`: Basic algorithms for comparing ranges.

### Type Traits
- `enable_if`, `is_integral`, `integral_constant`: SFINAE and type trait utilities for template metaprogramming.

### Pair Utility
- `ft::pair<T1, T2>`: Simple struct for holding two values, with comparison operators and `make_pair` helper.

---

For more details, see the comments in each header file.