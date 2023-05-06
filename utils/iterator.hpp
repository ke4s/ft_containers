#ifndef _ITERATOR_HPP_
#define _ITERATOR_HPP_

#include "iterator_traits.hpp"
#include "type_traits.hpp"

//#include <type_traits> // for std::is_convertible

namespace ft
{
	template <class Iterator>
	class random_access_iterator {
	private:
		Iterator value;
	public:
		typedef Iterator																iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::value_type					value_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer					pointer;
		typedef typename ft::iterator_traits<iterator_type>::const_pointer				const_pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference					reference;
		typedef typename ft::iterator_traits<iterator_type>::const_reference			const_reference;
		typedef typename ft::iterator_traits<iterator_type>::difference_type			difference_type;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category			iterator_category;

		random_access_iterator(Iterator value = NULL) : value(value) {}
		~random_access_iterator() {};

        /*
		template <class U> random_access_iterator(const random_access_iterator<U>& other,
		typename ft::enable_if<std::is_convertible<U, iterator_type>::value>::type* = 0) : value(other.base()) {};
        */

        template <class U> random_access_iterator(const random_access_iterator<U>& other
        /*, typename ft::enable_if<std::is_convertible<U, iterator_type>::value>::type* = 0 */) : value(other.base()) {};


        Iterator		base() const { return value; }

		random_access_iterator	&operator=(const random_access_iterator &obj)
		{
			if (this == &obj)
				return *this;

			this->value = obj.value;
			return *this;
		}

		random_access_iterator	operator++(int)
		{
			random_access_iterator tmp(*this);
			value++;
			return tmp;
		}

		random_access_iterator	operator--(int)
		{
			random_access_iterator tmp(*this);
			value--;
			return tmp;
		}

		random_access_iterator	&operator++()
		{
			value++;
			return *this;
		}

		random_access_iterator	&operator--()
		{
			value--;
			return *this;
		}


		int		operator-(random_access_iterator const &obj) const
		{ return value - obj.value; }
		int		operator+(random_access_iterator const &obj) const
		{ return value + obj.value; }

		random_access_iterator	operator-(int n) const
		{ return random_access_iterator(this->value - n); }
		random_access_iterator	operator+(int n) const
		{ return random_access_iterator(this->value + n); }

		random_access_iterator	&operator-=(int n)
		{ this->value -= n; return (*this); }

		random_access_iterator	&operator+=(int n)
		{ this->value += n; return (*this); }

		reference 	operator*() const 								{ return *value; }
		pointer 	operator->() const 								{ return &(*value); }
		reference 	operator[](const unsigned int index) 			{ return *this->value[index]; }

		bool		operator==(random_access_iterator const &obj) const 						{ return value == obj.value; };
		bool		operator!=(random_access_iterator const &obj) const 						{ return value != obj.value; };
		bool 		operator<=(random_access_iterator const &obj) const 						{ return value <= obj.value; };
		bool 		operator>=(random_access_iterator const &obj) const 						{ return value >= obj.value; };
		bool 		operator<(random_access_iterator const &obj) const 							{ return value < obj.value; };
		bool 		operator>(random_access_iterator const &obj) const 							{ return value > obj.value; };
	};

}

#endif