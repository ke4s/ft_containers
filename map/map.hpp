/*
 * ft::map<Key, T, Compare, Alloc>
 * -------------------------------
 * An associative container that stores key-value pairs in sorted order by key.
 *
 * Template Parameters:
 *   - Key: Key type.
 *   - T: Mapped value type.
 *   - Compare: Key comparison functor (default: std::less<Key>).
 *   - Alloc: Allocator (default: std::allocator<ft::pair<const Key, T>>).
 *
 * Features:
 *   - Unique keys
 *   - Logarithmic time insert, erase, find
 *   - Bidirectional iterators
 *   - STL-compatible interface
 *
 * Example Usage:
 *   ft::map<std::string, int> m;
 *   m["apple"] = 5;
 *   m["banana"] = 3;
 *   for (ft::map<std::string, int>::iterator it = m.begin(); it != m.end(); ++it) {
 *       std::cout << it->first << ": " << it->second << std::endl;
 *   }
 *
 * Methods:
 *   - Constructors: default, range, copy
 *   - operator=, get_allocator
 *   - at, operator[]
 *   - begin, end, rbegin, rend
 *   - empty, size, max_size
 *   - insert, erase, swap, clear
 *   - find, count, lower_bound, upper_bound, equal_range
 *   - key_comp, value_comp
 *   - Comparison operators
 *
 * Notes:
 *   - operator[] inserts a default value if key is not found.
 *   - Throws std::out_of_range in at() if key is not found.
 */
#ifndef _MAP_H_
#define _MAP_H_

#include "../tree_utils/map_tree.hpp"
#include "../utils/algorithm.hpp"

namespace ft
{
	template <typename Key,
			typename T,
			typename Compare = std::less<Key>,
			typename Alloc = std::allocator<ft::pair<const Key, T> > > //pair'in ilk elemanı const olmalı
	class map
	{
	public:
		typedef Key							key_type;
		typedef T							mapped_type;
		typedef ft::pair<const Key, T>		value_type;
		typedef	Compare						key_compare;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map<Key, T, Compare, Alloc>;
		protected:
			Compare	comp;

			value_compare(Compare c) : comp(c) {}
		
		public:
			bool	operator()(const value_type& _x, const value_type& _y) const
			{
				return comp(_x.first, _y.first);
			}
			value_compare() {}
		};

	private:

		typedef Rb_map_tree<key_type, value_type, Compare, Alloc>		Rep_type; //value_compare yollamak daha doğru olabilir

		// Tree object
		Rep_type	tree;

	public:
		typedef typename Rep_type::allocator_type           allocator_type;
		typedef typename Rep_type::reference                reference;
	    typedef typename Rep_type::const_reference          const_reference;
        typedef typename Rep_type::iterator                 iterator;
		typedef typename Rep_type::const_iterator           const_iterator;
	    typedef typename Rep_type::size_type                size_type;
	    typedef typename Rep_type::difference_type          difference_type;
        typedef typename Rep_type::pointer                  pointer;
	    typedef typename Rep_type::const_pointer            const_pointer;
		typedef typename Rep_type::reverse_iterator         reverse_iterator;
	    typedef typename Rep_type::const_reverse_iterator   const_reverse_iterator;

		//-------Constructors----
		map() : tree() {}

		explicit map(const Compare& comp, const allocator_type& a = allocator_type()) : tree(comp, a) {}

		map(const map& other) : tree(other.tree) {}

		template <typename InputIterator>
		map(InputIterator first, InputIterator last) : tree(Compare(), allocator_type())
		{
			tree.insert(first, last);
		}

		template <typename InputIterator>
		map(InputIterator first, InputIterator last, const Compare& comp, const allocator_type& a = allocator_type())
		: tree(comp, a)
		{
			tree.insert(first, last);
		}

		//------| assignment operator |--------
		map&	operator=(const map& other)
		{
			tree = other.tree;
			return *this;
		}

		~map()
		{

		}

		//returns Allocator
		allocator_type	get_allocator() const { return tree.get_allocator(); }

		//-------------| Iterator FUNCTIONS |-------

		//returns "Begin" iterator
		iterator		begin() { return tree.begin(); }

		//returns "Const Begin" iterator
		const_iterator	begin() const { return tree.begin(); }

		//returns "End" iterator
		iterator		end() { return tree.end(); }

		//returns "Const End" iterator
		const_iterator	end() const { return tree.end(); }

		//returns "Reverse Begin" iterator
		reverse_iterator		rbegin() { return tree.rbegin(); }

		//returns "Const Reverse Begin" iterator
		const_reverse_iterator	rbegin() const { return tree.rbegin(); }

		//returns "Reverse End" iterator
		reverse_iterator		rend() { return tree.rend(); }

		//returns "Const Reverse End" iterator
		const_reverse_iterator	rend() const { return tree.rend(); }


		bool	empty() const { return tree.empty(); }

		size_type	size() const { return tree.size(); }

		size_type	max_size()  { return tree.max_size(); }

		size_type	max_size() const { return tree.max_size(); }

		//if the Key is in the map, the operator will returns it. Otherwise it inserts the key
		mapped_type&	operator[](const key_type& key)
		{
			iterator it = tree.find(key);

			if (it != end())
				return it->second;
			else
				return (insert(value_type(key, T()))).first->second;
		}

		T& at( const Key& key )
		{
			iterator it = tree.find(key);

			if (it != end())
				return it->second;
			else
				throw std::out_of_range("No value with this key");
		}

		const T& at( const Key& key ) const
		{
			const_iterator it = tree.find(key);

			if (it != end())
				return it->second;
			else
				throw std::out_of_range("No value with this key");
		}


		ft::pair<iterator, bool>
		insert(const value_type& x)
		{ return tree.insert(x); }

		void	print(){ tree.print(); }


		iterator
		insert(iterator pos, const value_type& x)
	    { return tree.insert(pos, x); }

		template <typename InputIt>
		void	insert(InputIt first, InputIt last)
		{ tree.insert(first, last); }

		//Removes the element at pos.
		iterator	erase(iterator	pos)
		{ return tree.erase(pos); }

		//Removes the element (if one exists) with the key equivalent to key.
		size_type	erase(const Key&	key)
		{ return tree.erase(key); }


		//Removes the elements in the range [first, last), which must be a valid range in *this.
		iterator	erase (iterator first, iterator last)
		{ return tree.erase(first, last); }


		void	swap(map& other) { tree.swap(other.tree); }

		//deletes all node from tree
		void	clear() { tree.clear(); }


		//returns the function that compares keys
		key_compare	key_comp() const { return tree.key_comp(); }

		value_compare	value_comp() const { return value_compare(tree.key_comp()); }

		iterator	find(const Key& x) { return tree.find(x); }

		const_iterator	find(const Key& x) const { return tree.find(x); }

		size_type	count(const Key& x) const { return tree.end() == tree.find(x) ? 0 : 1; }

		iterator	lower_bound(const Key& key) { return tree.lower_bound(key); }

		const_iterator	lower_bound(const Key& key) const { return tree.lower_bound(key); }

		iterator	upper_bound(const Key& key) { return tree.upper_bound(key); }

		const_iterator	upper_bound(const Key& key) const { return tree.upper_bound(key); }

		pair<iterator, iterator>	equal_range(const key_type& x)
		{ return tree.equal_range(x); }

		pair<const_iterator, const_iterator>	equal_range(const key_type& x) const
		{
			ft::pair<iterator, iterator> duo = tree.equal_range(x);
			return ft::make_pair(const_iterator(duo.first), const_iterator(duo.second));
		}

	}; //map

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool	operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool	operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return !(lhs == rhs); }

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool	operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool	operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return rhs < lhs; }

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool	operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return !(rhs < lhs); } //!(lhs <= rhs) === rhs < lhs

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool	operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return !(lhs < rhs); }

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline void	swap(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ lhs.tree.swap(rhs.tree); }

} //namespace ft

namespace std
{
	template <class Key, class T, class Compare, class A>
	void swap(const ft::map<Key, T, Compare, A> &m1, const ft::map<Key, T, Compare, A> &m2 )
	{
		m1.swap(m2);
	}
}

#endif