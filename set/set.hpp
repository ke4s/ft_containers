/*
 * ft::set<Key, Compare, Allocator>
 * -------------------------------
 * An associative container that contains a sorted set of unique keys.
 *
 * Template Parameters:
 *   - Key: Key type.
 *   - Compare: Key comparison functor (default: std::less<Key>).
 *   - Allocator: Allocator (default: std::allocator<Key>).
 *
 * Features:
 *   - Unique keys
 *   - Logarithmic time insert, erase, find
 *   - Bidirectional iterators
 *   - STL-compatible interface
 *
 * Example Usage:
 *   ft::set<int> s;
 *   s.insert(3);
 *   s.insert(1);
 *   s.insert(2);
 *   for (ft::set<int>::iterator it = s.begin(); it != s.end(); ++it) {
 *       std::cout << *it << std::endl;
 *   }
 *
 * Methods:
 *   - Constructors: default, range, copy
 *   - operator=, get_allocator
 *   - begin, end, rbegin, rend
 *   - empty, size, max_size
 *   - insert, erase, swap, clear
 *   - find, count, lower_bound, upper_bound, equal_range
 *   - key_comp, value_comp
 *   - Comparison operators
 *
 * Notes:
 *   - All elements are unique and sorted by key.
 */
//
// Created by Kerim Sancakoglu on 2/2/23.
//

#ifndef _SET_HPP_
#define _SET_HPP_

#include "../tree_utils/set_tree.hpp"
#include "../utils/algorithm.hpp"

namespace ft
{
	template< class Key,
	        class Compare = std::less<Key>,
	        class Allocator = std::allocator<Key> >
	class set
	{
	public:
		//types
		typedef Key										key_type;
		typedef Key										value_type;
		typedef std::size_t								size_type;
		typedef std::ptrdiff_t							difference_type;
		typedef Compare									key_compare;
		typedef Compare 								value_compare;
		typedef Allocator 								allocator_type;
		typedef value_type& 							reference;
		typedef const value_type& 						const_reference;


	private:

		typedef Rb_set_tree<key_type, value_type , value_compare, allocator_type>		Rep_type;


		Rep_type tree;

	public:

		typedef typename Allocator::pointer						pointer;
		typedef typename Allocator::const_pointer 				const_pointer;
		typedef typename Rep_type::iterator										iterator;
		typedef typename Rep_type::const_iterator								const_iterator;
		typedef ft::reverse_iterator<iterator> 			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> 	const_reverse_iterator;


		//Member functions
		//bir yapılandırıcı "explicit" olarak bildirilirse, o yapılandırıcı sadece doğrudan bir değerle kullanılabilir
		//örneğin "MyClass obj(5);" ama "MyClass obj = 5;" gibi kapalı tip dönüşümü için kullanılamaz.

		set() : tree() {}

		explicit set(const Compare& comp, const Allocator& a = allocator_type()) : tree(comp, a) {}

		template<class InputIterator>
		set(InputIterator first, InputIterator last, const key_compare &comp = Compare(), const allocator_type& alloc = allocator_type()) : tree(comp, alloc)
		{
			tree.insert(first, last);
		}

		set(const set &obj): tree(obj.tree) {}

		~set() {}

		allocator_type get_allocator() const
		{
			return tree.get_allocator();
		}

		//something happend. Look cppreference
		set&	operator=(const set& other)
		{
			tree = other.tree;
			return *this;
		}

		void clear()
		{
			tree.clear();
		}

		//Modifiers
		template<class InputIt>
		void insert(InputIt first, InputIt last)
		{ tree.insert(first, last); }

		ft::pair<iterator, bool>
		insert(const value_type &val)
		{ return tree.insert(val); }

		iterator insert(iterator pos, const value_type &val)
		{ return tree.insert(pos, val); }



		iterator erase(iterator pos )
		{ return tree.erase(pos); }

		iterator erase(iterator first, iterator last)
		{ return tree.erase(first, last);}

		size_type erase( const Key& key ) // rbtde key verilen eleman silme
		{ return tree.erase(key); }


		void swap(set& other)
		{ tree.swap(other.tree); }


		size_type count(const key_type &key) const
		{ return tree.find(key) == tree.end() ? 0 : 1; }


		iterator find(const key_type &key)
		{ return tree.find(key); }

		const_iterator find(const key_type &key) const
		{ return tree.find(key); }


		ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
		{
			ft::pair<iterator, iterator> duo = tree.equal_range(key);
			return (ft::make_pair(const_iterator(duo.first), const_iterator(duo.second)));
		}

		ft::pair<iterator, iterator> equal_range(const key_type& key)
		{
			return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
		}

		iterator lower_bound( const Key& key )
		{ return tree.lower_bound(key); }

		const_iterator lower_bound( const Key& key ) const
		{ return tree.lower_bound(key); }

		iterator upper_bound( const Key& key )
		{ return tree.upper_bound(key); }

		const_iterator upper_bound( const Key& key ) const
		{ return tree.upper_bound(key); }


		//Iterators
		iterator begin()
		{
			return tree.begin();
		}

		const_iterator begin() const
		{
			return tree.begin();
		}

		iterator end()
		{
			return tree.end();
		}

		const_iterator end()const
		{
			return tree.end();
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		//Capacity
		bool empty() const	{ return tree.empty(); }

		size_type size() const { return tree.size(); }

		size_type max_size() { return tree.max_size(); }

		size_type max_size() const { return tree.max_size(); }


		//Observers
		key_compare key_comp() const
		{
			return tree.key_comp();
		}

		value_compare value_comp() const
		{
			return value_compare(this->_comp);
		}
	};

	//std::swap specializes

	template <typename Key, typename Compare, typename Alloc>
	inline bool	operator==(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{ return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

	template <typename Key, typename Compare, typename Alloc>
	inline bool	operator!=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{ return !(lhs == rhs); }

	template <typename Key, typename Compare, typename Alloc>
	inline bool	operator<(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template <typename Key, typename Compare, typename Alloc>
	inline bool	operator>(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{ return rhs < lhs; }

	template <typename Key, typename Compare, typename Alloc>
	inline bool	operator<=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{ return !(rhs < lhs); } //!(lhs <= rhs) === rhs < lhs

	template <typename Key, typename Compare, typename Alloc>
	inline bool	operator>=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{ return !(lhs < rhs); }

	template <typename Key, typename Compare, typename Alloc>
	inline bool	swap(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{ lhs.tree.swap(rhs.tree); }
}


namespace std
{
	template <typename Key, typename Compare, typename Alloc>
	void swap(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs)
	{ lhs.tree.swap(rhs.tree); }
}

#endif
