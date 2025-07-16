/*
 * ft::stack<T, Container>
 * ----------------------
 * A container adapter that gives the functionality of a stack (LIFO structure).
 *
 * Template Parameters:
 *   - T: Type of elements.
 *   - Container: Underlying container type (default: ft::vector<T>).
 *
 * Features:
 *   - LIFO semantics (push, pop, top)
 *   - Uses any container with back(), push_back(), pop_back(), etc.
 *   - STL-compatible interface
 *
 * Example Usage:
 *   ft::stack<int> s;
 *   s.push(1);
 *   s.push(2);
 *   std::cout << s.top() << std::endl; // 2
 *   s.pop();
 *   std::cout << s.top() << std::endl; // 1
 *
 * Methods:
 *   - Constructors: default, copy
 *   - top, push, pop
 *   - empty, size
 *   - Comparison operators
 *
 * Notes:
 *   - Underlying container can be customized.
 */
#ifndef STACK_HPP
#define STACK_HPP

#include "../vector/vector.hpp"

namespace ft
{

	template<class T, class Container = ft::vector<T> >
	class stack
	{
	public:

		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

		explicit stack(const Container& cont = Container()) : c(cont) { }

		value_type& top()
		{
			return c.back();
		}

		const value_type& top() const
		{
			return c.back();
		}

		void push(const value_type& val)
		{
			c.push_back(val);
		}

		void pop()
		{
			c.pop_back();
		}

		bool empty() const
		{
			return c.empty();
		}

		size_type size() const
		{
			return c.size();
		}


	protected:

		Container c;

		friend bool	operator==(const stack &lhs, const stack &rhs)
		{
			return lhs.c == rhs.c;
		}
		friend bool	operator!=(const stack &lhs, const stack &rhs)
		{
			return !(lhs == rhs);
		}
		friend bool	operator<(const stack &lhs, const stack &rhs)
		{
			return lhs.c < rhs.c;
		}
		friend bool	operator>(const stack &lhs, const stack &rhs)
		{
			return rhs < lhs;
		}
		friend bool	operator<=(const stack &lhs, const stack &rhs)
		{
			return !(lhs > rhs);
		}
		friend bool	operator>=(const stack &lhs, const stack &rhs)
		{
			return !(lhs < rhs);
		}
	};
}

#endif