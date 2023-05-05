#ifndef _TREE_UTILS_HPP
#define _TREE_UTILS_HPP

#include "../utils/reverse_iterator.hpp"
#include "../utils/iterator_traits.hpp"

enum Rb_tree_color { S_red = false, S_black = true };

template<typename value_type>
struct Rb_tree_node
{
	typedef Rb_tree_node<value_type>*				node_ptr;

	Rb_tree_color   color;
	node_ptr        parent;
	node_ptr        left;
	node_ptr        right;
	value_type		value_field;
	Rb_tree_node() : color(S_red), parent(NULL), left(NULL), right(NULL),value_field() {};
	Rb_tree_node(value_type mapped) : color(S_red), parent(NULL), left(NULL), right(NULL),value_field(mapped) {};
	Rb_tree_node(const Rb_tree_node &other) : value_field(other.value_field), parent(other.parent),
											  left(other.left), right(other.right), color(other.color) {};
};


template< typename value_type>
inline bool is_nilNode(Rb_tree_node<value_type>* node)
{
	if (node == NULL)
		return (true);
	else if (node->parent == NULL && node->left == NULL && node->right == NULL)
		return (true);
	return (false);
}

template<typename value_type>
Rb_tree_node<value_type>* Rb_tree_increment(Rb_tree_node<value_type>* x)
{
	if (!is_nilNode(x->right))
	{
		x = x->right;
		while (!is_nilNode(x->left))
			x = x->left;
	}
	else
	{
		Rb_tree_node<value_type>* y = x->parent;

		while (x == y->right)
		{
			x = y;
			y = y->parent;
		}
		if (x->right != y)
			x = y;
	}
	return x;
}

template<typename value_type>
const Rb_tree_node<value_type>* Rb_tree_increment(const Rb_tree_node<value_type>* x)
{
	return Rb_tree_increment(const_cast<Rb_tree_node<value_type>* >(x));
}

template<typename value_type>
Rb_tree_node<value_type>* Rb_tree_decrement(Rb_tree_node<value_type>* x)
{
	if (x->color == S_red && x->parent->parent == x)
		x = x->right;
	else if (!is_nilNode(x->left))
	{
		Rb_tree_node<value_type>* y = x->left;
		while (!is_nilNode(y->right))
			y = y->right;
		x = y;
	}
	else
	{
		Rb_tree_node<value_type>* y = x->parent;
		while (x == y->left)
		{
			x = y;
			y = y->parent;
		}
		x = y;
	}
	return x;
}

template<typename value_type>
const Rb_tree_node<value_type>* Rb_tree_decrement(const Rb_tree_node<value_type>* x)
{
	return Rb_tree_decrement(const_cast<Rb_tree_node<value_type>* >(x));
}

template<typename T>
struct Rb_tree_iterator
{
	typedef T   value_type;
	typedef T&  reference;
	typedef T&  const_reference;
	typedef T*  pointer;
	typedef T*  const_pointer;

	typedef Rb_tree_iterator<T>     iterator;

	typedef ft::bidirectional_iterator_tag  iterator_category;
	typedef ptrdiff_t                       difference_type;

	typedef Rb_tree_iterator<T>             self;
	typedef Rb_tree_node<T>*                link_type;


protected:
	link_type   node;
public:
	Rb_tree_iterator() : node(){}

	explicit    Rb_tree_iterator(link_type x) : node(x) {}

	Rb_tree_iterator(const iterator& it) : node(it.getNode()) {};

	reference   operator*() const
	{ return static_cast<link_type>(node)->value_field; }

	pointer     operator->() const
	{ return &static_cast<link_type>(node)->value_field; }

	self&       operator++()
	{
		node = Rb_tree_increment(node);
		return *this;
	}

	self    operator++(int)
	{
		self    tmp = *this;

		node = Rb_tree_increment(node);
		return tmp;
	}

	self&       operator--()
	{
		node = Rb_tree_decrement(node);
		return *this;
	}

	self    operator--(int)
	{
		self    tmp = *this;

		node = Rb_tree_decrement(node);
		return tmp;
	}

	bool    operator==(const self& x) const
	{ return node == x.getNode(); }

	const link_type getNode(void) const
	{
		return node;
	}

	bool    operator!=(const self& x) const
	{ return node != x.getNode(); }

}; // Rb_tree_iterator



template<typename T>
struct Rb_tree_const_iterator
{
	typedef T           value_type;
	typedef const T&    reference;
	typedef const T*    pointer;

	typedef Rb_tree_iterator<T>     iterator;

	typedef ft::bidirectional_iterator_tag  iterator_category;
	typedef ptrdiff_t                       difference_type;

	typedef Rb_tree_const_iterator<T>             self;
	typedef const Rb_tree_node<T>*                link_type;

protected:
	link_type   node;

public:
	Rb_tree_const_iterator() : node() {}

	explicit    Rb_tree_const_iterator(link_type x) : node(x) {}

	Rb_tree_const_iterator(const iterator& it) : node(it.getNode()) {}

	reference   operator*() const
	{ return static_cast<link_type>(node)->value_field; }

	pointer     operator->() const
	{ return &static_cast<link_type>(node)->value_field; }

	self&       operator++()
	{
		node = Rb_tree_increment(node);
		return *this;
	}

	self    operator++(int)
	{
		self    tmp = *this;

		node = Rb_tree_increment(node);
		return tmp;
	}

	self&       operator--()
	{
		node = Rb_tree_decrement(node);
		return *this;
	}


	self    operator--(int)
	{
		self    tmp = *this;

		node = Rb_tree_decrement(node);
		return tmp;
	}

	const link_type getNode(void) const
	{
		return node;
	}

	bool    operator==(const self& x) const
	{ return node == x.getNode(); }

	bool    operator!=(const self& x) const
	{ return node != x.getNode(); }

}; // Rb_const_iterator


template<typename Val>
inline bool operator==(const Rb_tree_iterator<Val>& x, const Rb_tree_const_iterator<Val>& y)
{ return x.getNode() == y.getNode(); }

template<typename Val>
inline bool operator==(const Rb_tree_const_iterator<Val>& x, const Rb_tree_iterator<Val>& y)
{ return x.getNode() == y.getNode(); }

template<typename Val>
inline bool operator!=(const Rb_tree_iterator<Val>& x, const Rb_tree_const_iterator<Val>& y)
{ return x.getNode() != y.getNode(); }

template<typename Val>
inline bool operator!=(const Rb_tree_const_iterator<Val>& x, const Rb_tree_iterator<Val>& y)
{ return x.getNode() != y.getNode(); }

#endif