
# ft_container

### Description

ft_container is a project that aims to implement some of the standard C++ containers and their associated algorithms, as specified in the C++98 standard. This project is part of the curriculum at 42 School.

#### The following containers should be implemented:\
vector\
stack\
map\
set

#### Additionally, the following non-member functions must also be implemented:
algorithm (std::equal & std::lexicographical_compare)\
iterators\
reverse_iterator\
enable_if\
is_integral\
pair

## vector
The vector container is a dynamic array that can resize itself automatically as elements are inserted or deleted. It supports random access iterators and is similar to a traditional C-style array.

## stack
The stack container is a container adapter that provides a LIFO (last-in first-out) stack. It only allows insertion and deletion of elements from the top of the stack.

## map
The map container is an associative container that stores key-value pairs. It is implemented using a self-balancing binary search tree, which allows for fast lookup times.

## set
The set container is an associative container that stores unique elements in a sorted order. It is also implemented using a self-balancing binary search tree.

## iterators
The iterator library provides a collection of iterator types for iterating over ranges of elements in containers. Iterators are used to access and manipulate the elements in a container.

## reverse_iterator
The reverse_iterator library provides an iterator adapter that iterates over a range of elements in reverse order.





The implementation of ft_container should be based on the C++ standard template library (STL) and must pass a series of tests in order to be considered complete.