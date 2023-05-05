#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_


#include <stdexcept>

#include "../utils/iterator.hpp"
#include "../utils/reverse_iterator.hpp"
#include "../utils/utility.hpp"
#include "../utils/type_traits.hpp"
#include "../utils/algorithm.hpp"


namespace ft {
	template < class T, class A = std::allocator<T> >
	class vector
	{
	public:

		typedef T											value_type;
		typedef A											allocator_type;
		typedef std::size_t 								size_type;
		typedef std::ptrdiff_t								difference_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef T*											pointer;
		typedef const T*									const_pointer;
		typedef ft::random_access_iterator<T*> 				iterator;
		typedef ft::random_access_iterator<const T*>		const_iterator;
		typedef ft::reverse_iterator<iterator> 				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	private:

		pointer												buffer;
		size_type 											_capacity;
		size_type 											_size;
		allocator_type										allocator;

	public:

		explicit vector(const A& alloc = A()) : buffer(0), _capacity(0), _size(0), allocator(alloc) {}

		vector(size_type count, const_reference value = value_type(), const A& alloc = A()) {
			if (count < 0)
				throw std::out_of_range("vector");
			allocator = alloc;
			_capacity = _size = count;
			buffer = allocator.allocate(_capacity);
			for (size_t i = 0; i < count; ++i)
				buffer[i] = value;
		};

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const A& alloc = A(),
			   typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0) : _capacity(0), _size(0), allocator(alloc) {
			buffer = allocator.allocate(_capacity);
			this->assign(first, last);
		};

		vector(const vector& other) : buffer(0), _capacity(other._capacity), _size(other._size), allocator(other.get_allocator()) {
			buffer = allocator.allocate(other._capacity);
			for (size_t i = 0; i < _size; i++)
				buffer[i] = other.buffer[i];
		};

		~vector() {
			this->clear();
			allocator.deallocate(buffer, _capacity);
		};

		vector& operator=(const vector& other) {
			if (this == &other)
				return *this;
			this->clear();
			allocator.deallocate(buffer, _capacity);
			_capacity = other._capacity;
			_size = other._size;
			buffer = allocator.allocate(_capacity);
			for (size_t i = 0; i < _size; ++i) {
				buffer[i] = other.buffer[i];
			}
			return *this;
		};

		void assign(size_type count, const_reference value ) {
			if (count < 0)
				throw std::out_of_range("vector");
			this->clear();
			this->reserve(count);
			for (size_t i = 0; i < count; ++i, _size++)
				buffer[i] = value;
		};


		template <class InputIterator>
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
		assign(InputIterator first, InputIterator last) {
			int range_size = last - first;
			if (range_size < 0) throw std::length_error("vector");
			this->clear();
			this->reserve(range_size);
			for (; first != last; ++first) {
				this->push_back(*first);
			}
		};

		allocator_type get_allocator() const { return this->allocator; };


		reference at( size_type pos ) {
			if (pos >= _size)
				throw std::out_of_range("vector");
			return buffer[pos];
		};

		const_reference at( size_type pos ) const {
			if (pos >= _size)
				throw std::out_of_range("vector");
			return buffer[pos];
		};

		reference       		operator[]( size_type pos )					{ return buffer[pos]; };
		const_reference 		operator[]( size_type pos ) const			{ return buffer[pos]; };
		reference				front()										{ return *buffer; };
		const_reference 		front() const								{ return *buffer; };
		reference				back()										{ return buffer[_size - 1]; };
		const_reference			back() const								{ return buffer[_size - 1]; };
		pointer 				data()										{ return buffer; };
		const_pointer			data() const								{ return buffer; };
		iterator 				begin()										{ return iterator(buffer); };
		const_iterator 			begin() const								{ return const_iterator(buffer); };
		iterator 				end()										{ return iterator(buffer + _size); };
		const_iterator 			end() const									{ return const_iterator(buffer + _size); };
		reverse_iterator 		rbegin()									{ return reverse_iterator(iterator(buffer + _size - 1)); };
		const_reverse_iterator 	rbegin() const								{ return const_reverse_iterator(const_iterator(buffer + _size - 1)); };
		reverse_iterator 		rend()										{ return reverse_iterator(iterator(buffer)); };
		const_reverse_iterator 	rend() const								{ return const_reverse_iterator(const_iterator(buffer - 1)); };
		bool 					empty() const								{ return _size <= 0; };
		size_type				size() const								{ return _size; };
		size_type				capacity() const							{ return _capacity; };
		size_type				max_size() const 							{ return value_type(-1); };


		void reserve(size_type size) {
			if (size > _capacity) {
				T* tmp = allocator.allocate(size);
				for (size_t i = 0; i < _size; ++i)
					tmp[i] = buffer[i];
				if (buffer) allocator.deallocate(buffer, _capacity);
				_capacity = size;
				buffer = tmp;
			}
		};

		void clear() {
			for (size_type i = 0; i < _size; i++) {
				allocator.destroy(buffer + i);
			}
			_size = 0;
		};

		void insert( iterator pos, size_type count, const T& value ) {
			unsigned long index = pos - begin();
			size_t max_size = _size + count;

			if (count >= _capacity) {
				reserve(_capacity + count);
				_size = max_size;
			} else {
				while (_size != max_size) {
					if (_size == _capacity)
						reserve(_capacity * 2);
					_size++;
				}
			}
			for (unsigned long i = _size; i >= 0; --i) {
				if (i == index + count - 1) {
					for (; count > 0; --count, --i) {
						buffer[i] = value;
					}
					return;
				}
				buffer[i] = buffer[i - count];
			}
		};

		iterator insert(iterator pos, const_reference value) {
			int index = pos - begin();
			this->insert(pos, 1, value);
			return iterator(buffer + index);
		};

		template <class InputIt>
		typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type
		insert( iterator pos, InputIt first, InputIt last) {
			size_t range_size = last - first;
			if (!validate_iterator_values(first, last, range_size))
				throw std::exception();
			size_t new_size = _size + range_size;

			int last_index = (pos - begin()) + range_size - 1;
			if (range_size >= _capacity) {
				reserve(_capacity + range_size);
				_size = new_size;
			} else {
				while (_size != new_size) {
					if (_size == _capacity)
						reserve(_capacity * 2);
					_size++;
				}
			}
			for (int i = _size - 1; i >= 0; --i) {
				if (i == last_index) {
					for (; range_size > 0; --range_size, --i) {
						buffer[i] = *--last;
					}
					return;
				}
				buffer[i] = buffer[i - range_size];
			}
		};

		iterator erase( iterator pos )
		{
			int index = pos - begin();
			for (size_t i = index; i < _size; ++i)
			{
				buffer[i] = buffer[i + 1];
			}
			if (_size > 0)
			 _size--;
			return pos;
		}

		iterator erase( iterator first, iterator last )
		{
			int start = first - begin();
			int end = last - begin();
			int offset = end - start;

			_size -= offset;
			for (size_t i = start; i < _size; ++i) {
				buffer[i] = buffer[i + offset];
			}
			return buffer + start;
		}

		void push_back( const_reference value ) {
			if (_size == _capacity)
				(!_capacity) ? this->reserve(1) : this->reserve(_capacity * 2);
			buffer[_size] = value;
			++_size;
		};

		void pop_back() {
			allocator.destroy(buffer + _size);
			_size--;
		}

		void resize( size_type count, T value = T() ) {
			if (count < _size) {
				while (_size != count)
					pop_back();
			} else {
				if (_capacity * 2 < count)
					reserve(count);
				while (_size != count)
					push_back(value);
			}
		}

		void swap( vector& other ) {
			std::swap(_size, other._size);
			std::swap(_capacity, other._capacity);
			std::swap(buffer, other.buffer);
			std::swap(allocator, other.allocator);
		}

	private:

		template<class InputIt>
		typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type
		validate_iterator_values(InputIt first, InputIt last, size_t range) {
			pointer reserved_buffer;
			reserved_buffer = allocator.allocate(range);
			bool result = true;
			size_t i = 0;

			for (;first != last; ++first, ++i) {
				try { reserved_buffer[i] = *first; }
				catch (...) { result = false; break; }
			}
			allocator.deallocate(reserved_buffer, range);
			return result;
		}
	};

	template <class T, class A>
	inline bool operator== (const vector<T, A> &lhs, const vector<T, A> &rhs)
	{ return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

	template <class T, class A>
	inline bool operator!= (const vector<T, A> &lhs, const vector<T, A> &rhs)
	{ return !(lhs == rhs); }

	template <class T, class A>
	inline bool operator< (const vector<T, A> &lhs, const vector<T, A> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class A>
	inline bool operator> (const vector<T, A> &lhs, const vector<T, A> &rhs) {
		return rhs < lhs;
	}

	template <class T, class A>
	inline bool operator<= (const vector<T, A> &lhs, const vector<T, A> &rhs) {
		return !(rhs < lhs);
	}

	template <class T, class A>
	inline bool operator>= (const vector<T, A> &lhs, const vector<T, A> &rhs) {
		return !(lhs < rhs);
	}

	template <class T, class A>
	void swap(const ft::vector<T, A> &v1, const ft::vector<T, A> &v2 )
	{
		v1.swap(v2);
	}
}


namespace std
{
	template <class T, class A>
	void swap(ft::vector<T, A> &v1, ft::vector<T, A> &v2 )
	{
		v1.swap(v2);
	}
}
#endif
