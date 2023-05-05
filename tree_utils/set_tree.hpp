#ifndef _SET_TREE_HPP_
#define _SET_TREE_HPP_

#include "../utils/utility.hpp"
#include "tree_utils.hpp"

template<typename Key,
		typename Val,
		typename value_compare,
		typename Alloc = std::allocator<Rb_tree_node<Val> > >
class Rb_set_tree
{
	typedef typename Alloc::template rebind<Rb_tree_node<Val> >::other Node_allocator;

protected:
	typedef typename Rb_tree_node<Val>::node_ptr         node_ptr;
	typedef const node_ptr   const_node_ptr;
	typedef Rb_tree_node<Val>      i_node; //wtf

public:
	typedef Key                 key_type;
	typedef Val                 value_type;
	typedef value_type*         pointer;
	typedef const value_type*   const_pointer;
	typedef value_type&         reference;
	typedef const value_type&   const_reference;

	//bunlar silinebilir ya da ismi değişebilir
	typedef Rb_tree_node<Val>*       Link_type;
	typedef const Rb_tree_node<Val>* Const_Link_type;
	//--------

	typedef size_t              size_type;
	typedef ptrdiff_t           difference_type;
	typedef Alloc               allocator_type;

	typedef Rb_tree_iterator<value_type>       iterator;
	typedef Rb_tree_const_iterator<value_type> const_iterator;

	typedef ft::reverse_iterator<iterator>       reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;


	value_compare key_comp() const
	{ return _key_compare; }

	allocator_type  get_allocator() const
	{ return _alloc; }

	bool    empty() const
	{ return _size == 0; }

	size_type   size() const
	{ return _size; }

	//idk maybe it is not correct
	size_type   max_size()
	{ return size_type(-1); }


	//test Functiouns
	//---------------

	Link_type retNil() { return _NTREE; }

	//------------
protected:

	mutable node_ptr		_root;
	mutable node_ptr		_NTREE; //Nil node
	node_ptr 		_end_node;
	value_compare	_key_compare;
	size_type		_size;
	Node_allocator 	_alloc;

public:

	Rb_set_tree() : _root(NULL), _NTREE(NULL), _size(0)
	{
		_NTREE = newNode();
		_NTREE->color = S_black;
		_end_node = newNode();
		_end_node->left = _end_node->right = _NTREE;
		//in beginning root is end node;
		_root = _end_node;
		_size = 0;
	}

	Rb_set_tree(const value_compare& comp, const Alloc &alloc) :_key_compare(comp), _alloc(alloc)
	{
		_NTREE = newNode();
		_NTREE->color = S_black;
		_end_node = newNode();
		_end_node->left = _end_node->right = _NTREE;
		//in beginning root is end node;
		_root = _end_node;
		_size = 0;
	}

	Rb_set_tree(const Rb_set_tree& other) :_key_compare(other._key_compare), _alloc(other._alloc)
	{
		_NTREE = newNode();
		_NTREE->color = S_black;
		_end_node = newNode();
		_end_node->left = _end_node->right = _NTREE;
		//in beginning root is end node;
		_root = _end_node;
		_size = 0;
		insert(other.begin(), other.end());
	}

	~Rb_set_tree()
	{
		clear();
		delNode(_end_node);
		delNode(_NTREE);
	}

	Rb_set_tree &operator=(const Rb_set_tree &other)
	{
		if (this == &other)
		{
			return *this;
		}
		Rb_set_tree tmp(other);
		this->swap(tmp);
		return *this;
	}

private:

	//-------| Node creators and destructors | -----------

	//returns new NIL node
	node_ptr newNode()
	{
		node_ptr ret = _alloc.allocate(1);
		_alloc.construct(ret);
		return ret;
	}

	//returns new node with key and value
	node_ptr newNode(const value_type &mapped)
	{
		node_ptr ret = _alloc.allocate(1);
		_alloc.construct(ret, mapped);
		return ret;
	}

	void	delNode(node_ptr& to_del)
	{
		_alloc.destroy(to_del);
		_alloc.deallocate(to_del, 1);

	}

	void destroyTree(node_ptr& node)
	{
		if (node == NULL)
			return;
		if (node->right != _NTREE)
			destroyTree(node->right);
		if (node->left != _NTREE)
			destroyTree(node->left);
		if (node != _NTREE)
		{
			delNode(node);
			node = _NTREE;
		}
	}

	node_ptr minNode(node_ptr node) const
	{
		if (node == _NTREE)
			return node;
		while (node->left != _NTREE)
			node = node->left;
		return node;
	}

	node_ptr maxNode(node_ptr node) const
	{
		if (node == _NTREE)
			return node;
		while (node->right != _NTREE && node->right != _end_node)
			node = node->right;
		return node;
	}

	void addEnd()
	{
		node_ptr max = maxNode(_root);

		if (max == _root && _root == _NTREE)
		{
			_root = _end_node;
			_end_node->parent = NULL;
		}
		else if (max == _root && _root != _NTREE)
		{
			_root->right = _end_node;
			_end_node->parent = _root;
		}
		else
		{
			max->right = _end_node;
			_end_node->parent = max;
		}
	}

	void delEnd()
	{
		if (_end_node == _root) //root is endNode
		{
			_root = _NTREE;
			_end_node->parent = NULL;
		}
		else
		{
			_end_node->parent->right = _NTREE;
			_end_node->parent = NULL ;
		}
	}
	//-------| Algorithm base functions |-------------

	void	rotLeft(node_ptr node)
	{
		node_ptr rightN = node->right;
		node->right = rightN->left;

		if (rightN->left != _NTREE)
			rightN->left->parent = node;

		rightN->parent = node->parent;

		if(!node->parent)
			this->_root = rightN;
		else if(node == node->parent->left)
			node->parent->left = rightN;
		else
			node->parent->right = rightN;
		rightN->left = node;
		node->parent = rightN;
	}

	void rotRight(node_ptr node)
	{
		node_ptr leftN = node->left;
		node->left = leftN->right;

		if (leftN->right != _NTREE)
			leftN->right->parent = node;

		leftN->parent = node->parent;
		if (!node->parent)
			this->_root = leftN;
		else if(node == node->parent->right)
			node->parent->right = leftN;
		else
			node->parent->left = leftN;
		leftN->right = node;
		node->parent = leftN;
	}

	node_ptr searchNode(const Key& to_find) const
	{
		node_ptr ret = _root;

		while (ret != _NTREE && ret != _end_node)
		{
			if(ret->value_field == to_find)
				return (ret);
			if(_key_compare(ret->value_field , to_find))
				ret = ret->right;
			else
				ret = ret->left;
		}
		return (_NTREE);
	}

	bool searchNode(const node_ptr to_find) const
	{
		node_ptr temp = _root;
		while (temp != _NTREE && temp != _end_node)
		{
			if(temp == to_find)
				return true;
			if(_key_compare(temp->value_field , to_find->value_field))
				temp = temp->right;
			else
				temp = temp->left;
		}
		return false;
	}

	void	insertFix(node_ptr node)
	{
		node_ptr tempNode;
		//if node parents color equals to red, while block runs
		while (node->parent->color != S_black)
		{
			//if node parents not equals to node grandparents right child
			if (node->parent != node->parent->parent->right)
			{
				//tempNode equals to nodes uncle
				tempNode = node->parent->parent->right;
				//if nodes uncles color equals to red, its color become black, nodes parent color become black
				// and grandparents color become red
				if (tempNode->color == S_red)
				{

					tempNode->color = S_black;
					node->parent->color = S_black;
					node->parent->parent->color = S_red;
					node = node->parent->parent;
				}
				else //if nodes uncles color equals to black
				{
					if (node == node->parent->right)
					{
						node = node->parent;
						//rotate left node
						rotLeft(node);
					}
					node->parent->color = S_black;
					node->parent->parent->color = S_red;
					//rotate right node
					rotRight(node->parent->parent);
				}
			}
			else
			{
				//tempNode equals to nodes uncle
				tempNode = node->parent->parent->left;
				//if nodes uncles color equals to black
				if (tempNode->color == S_black)
				{
					if (node == node->parent->left)
					{
						node = node->parent;
						rotRight(node);
					}
					// case 3.2.1
					node->parent->color = S_black;
					node->parent->parent->color = S_red;
					rotLeft(node->parent->parent);

				}
				else //if nodes uncles color equals to red
				{
					tempNode->color = S_black;
					node->parent->color = S_black;
					node->parent->parent->color = S_red;
					node = node->parent->parent;
				}
			}
			if (node == _root)
				break;
		}
		_root->color = S_black;
	}

bool	deleteNodeFunc(node_ptr to_del)
{
	node_ptr node1;
	node_ptr node2;
	node_ptr nil;

	//if nil equals to _NTREE, node is not found
	nil = to_del;

	node2 = nil;
	bool YMainColor = node2->color;

	////case-1: if nils left child equals to _NTREE
	if (nil->left == _NTREE)
	{
		node1 = nil->right;
		//transplant processes
		if(nil->parent == NULL)
			_root = nil->right;
		else if(nil == nil->parent->left)
			nil->parent->left = nil->right;
		else
			nil->parent->right = nil->right;
		nil->right->parent = nil->parent;
	}
	else if(nil->right == _NTREE) //case-2: if nils right child equals to _NTREE
	{
		node1 = nil->left;
		//transplant processes
		if(nil->parent == NULL)
			_root = nil->left;
		else if(nil == nil->parent->left)
			nil->parent->left = nil->left;
		else
			nil->parent->right = nil->left;
		nil->left->parent = nil->parent;
	}
	else if (nil != _root) //case-3
	{
		node2 = minNode(nil->right);
		YMainColor = node2->color;
		node1 = node2->right;
		if(node2->parent == nil)
			node1->parent = node2;
		else
		{
			//transplant processes
			if(node2->parent == NULL)
				_root = node2->right;
			else if(node2 == node2->parent->left)
				node2->parent->left = node2->right;
			else
				node2->parent->right = node2->right;

			node2->right->parent = node2->parent;
			node2->right = nil->right;
			node2->right->parent = node2;
		}
		//transplant processes
		if(nil->parent == NULL)
			_root = node2;
		else if(nil == nil->parent->left)
			nil->parent->left = node2;
		else
			nil->parent->right = node2;
		node2->parent = nil->parent;
		node2->left = nil->left;
		node2->left->parent = node2;
		node2->color = nil->color;
	}
	else
	{
		node2 = maxNode(nil->left);
		YMainColor = node2->color;
		node1 = node2->right; //NTREE

		//transplant processes
		if(node2->parent == NULL)
			_root = node2->right;
		else if(node2 == node2->parent->left)
			node2->parent->left = node2->right;
		else
			node2->parent->right = node2->right;

		node2->right->parent = node2->parent;
		node2->right = nil->right;
		node2->right->parent = node2;
		//transplant processes
		if(nil->parent == NULL)
			_root = node2;
		else if(nil == nil->parent->left)
			nil->parent->left = node2;
		else
			nil->parent->right = node2;
		node2->parent = nil->parent;
		node2->left = nil->left;
		node2->left->parent = node2;
		node2->color = nil->color;
	}
	//delete nil node
	delNode(nil);
	//if y nodes first color is black, then deleteFix function call
	if (YMainColor == S_black)
		deleteFix(node1);
	_NTREE->parent = NULL;
	return (true);
}

void	deleteFix(node_ptr node)
	{
		node_ptr tempN;

		while (node->color == S_black && node != _root )
		{
			//if node is left child
			if (node == node->parent->left)
			{
				//temp node is sibling
				if(node->parent->right)
					tempN = node->parent->right;
				if(tempN)
				{
					//case-1
					//if sibling is red
					if (tempN->color == S_red)
					{

						tempN->color = S_black;
						node->parent->color = S_red;
						rotLeft(node->parent);
						tempN = node->parent->right;
					}
					//case-2
					//if sibling childs are black, its color become red
					if (tempN->left->color == S_black && tempN->right->color == S_black)
					{
						tempN->color = S_red;
						node = node->parent;
					}
					else //case-3
					{
						//if only siblings right child is black
						if(tempN->right->color == S_black)
						{
							tempN->left->color = S_black;
							tempN->color = S_red;
							rotRight(tempN);
							tempN = node->parent->right;
						}
						//case-4
						tempN->color = node->parent->color;
						node->parent->color = S_black;
						tempN->right->color = S_black;

						rotLeft(node->parent);
						node = _root;
					}
				}

			}
			else //if node is right child
			{
				if(node->parent->left)
					tempN = node->parent->left;
				if(tempN){
					//case-1
					//if sibling is red
					if(tempN->color == S_red)
					{
						tempN->color = S_black;
						node->parent->color = S_red;

						rotRight(node->parent);
						tempN = node->parent->left;
					}
					//case-2
					//if sibling childs are black, its color become red
					if (tempN->left->color == S_black && tempN->right->color == S_black)
					{
						tempN->color = S_red;
						node = node->parent;
					}
					else //case-3
					{
						//if sibling left childs is black
						if(tempN->left->color == S_black)
						{
							tempN->right->color = S_black;
							tempN->color = S_red;

							rotLeft(tempN);
							tempN = node->parent->left;
						}
						//case-4
						tempN->color = node->parent->color;
						node->parent->color = S_black;
						tempN->left->color = S_black;

						rotRight(node->parent);
						node = _root;
					}
				}
			}
		}
		node->color = S_black;
	}

	node_ptr insert_base(const value_type mapped)
	{
		// Ordinary Binary Search Insertion
		node_ptr node = newNode(mapped);
		node->left = _NTREE;
		node->right = _NTREE;
		_size++;
		node_ptr y = NULL;

		//firstly tempRoot equals to root
		node_ptr tempRoot = this->_root;

		//find appropriate place for new node
		while (tempRoot != _NTREE) {
			y = tempRoot;
			if (_key_compare(node->value_field, tempRoot->value_field))
				tempRoot = tempRoot->left;
			else
				tempRoot = tempRoot->right;
		}

		// y is parent of new node
		node->parent = y;
		// if parents of new node is null, the node will be root and its color become black, then return
		if (y == NULL)
		{
			_root = node;
			node->color = S_black;
			return node;
		}
		else if (_key_compare(node->value_field, y->value_field)) //new nodes data smaller than its parent's data, the new node become parents left child
			y->left = node;
		else //new nodes data smaller than its parents data, the new node become parents right child
			y->right = node;

		if (node->parent->parent == NULL) // if the new node parents of parents is null, then return
		{
			return node;
		}

		// call insertFix function
		insertFix(node);
		return node;
	}

	/*
	void print (node_ptr node, int indent) const
	{
		if 	(node != _NTREE)
		{
			print(node->right, indent + 4);
			if (indent)
				std::cout << std::setw(indent) << ' ';
			if 	(node->color == S_black) {
				std::cout <<	node->value_field << ":" <<	node->value_field << " (BLACK)" << std::endl;
			}
			else
			{
				std::cout <<	node->value_field << ":" <<	node->value_field << " (RED)" << std::endl;
			}
			print(node->left, indent + 4);
		}
	}

public:

	//It's for debugging.
	void	print() const
	{
		print(_root, 0);
	}
	 */

public:
	ft::pair<iterator, bool> insert(const value_type& x)
	{

		node_ptr fond = searchNode(x);
		if (fond != _NTREE)
		{
			return ft::make_pair(iterator(fond), 0);
		}
		delEnd();
		node_ptr ret_iter = insert_base(x);
		addEnd();
		return ft::make_pair(iterator(ret_iter), 1);
	}

	iterator insert(iterator pos, const value_type& value)
	{
		(void)pos;
		node_ptr node = searchNode(value);
		if (node != _NTREE)
			return iterator(node);
		delEnd();
		node = insert_base(value);
		addEnd();
		return iterator(node);
	}

	template<typename InputIt>
	void insert(InputIt first, InputIt last)
	{
		delEnd();
		while (first != last)
		{
			insert_base(*first);
			first++;
		}
		addEnd();
	}

	//if tree contain key, function erase it and returns 1. Else func returns 0
	size_type 	erase(const Key& key)
	{
		node_ptr to_del = searchNode(key);

		if (to_del  == _NTREE)
			return 0;
		delEnd();
		deleteNodeFunc(to_del);
		addEnd();
		_size--;
		return (1);
	}

	iterator	erase(iterator pos)
	{
		//if pos doesn't exits on tree, func does not erase. it returns the pos
		delEnd();
		bool is_in = searchNode(pos.getNode());
		if (is_in  == 0)
		{
			addEnd();
			//std::map gets segfault in some cases it's erase func. But mine func doesn't.
			return pos;
		}
		addEnd();
		iterator ret = ++(iterator(pos));
		delEnd();
		deleteNodeFunc(pos.getNode());

		addEnd();
		_size--;
		return (ret);
	}

	iterator	erase(iterator first, iterator last)
	{
		iterator next_iter;

		while(first != last)
		{
			bool is_in = searchNode(first.getNode());
			if (is_in == 0)
			{
				return first;
			}
			next_iter = ++(iterator(first.getNode()));
			delEnd();
			deleteNodeFunc(first.getNode());
			addEnd();
			_size--;
			first = next_iter;
		}
		return first;
	}

	iterator find(const Key& key)
	{
		node_ptr node = searchNode(key);
		return node == _NTREE ? end() : iterator(node);
	}

	//segfault. I cant understand why it gets seg.
	const_iterator find(const Key& key) const
	{
		node_ptr node = searchNode(key);
		return node == _NTREE ? end() : const_iterator(node);
	}

	iterator lower_bound(const Key& key)
	{
		node_ptr ptr = _root;
		node_ptr pos  = _end_node;

		while (ptr != _end_node && ptr != _NTREE)
		{
			if (!_key_compare(ptr->value_field, key))
			{
				pos = ptr;
				ptr = ptr->left;
			}
			else
				ptr = ptr->right;
		}

		return iterator(pos);
	}

	const_iterator lower_bound(const Key& key) const
	{

		node_ptr ptr = _root;
		node_ptr pos  = _end_node;

		while (ptr != _end_node && ptr != _NTREE)
		{
			if (!_key_compare(ptr->value_field, key))
			{
				pos = ptr;
				ptr = ptr->left;
			}
			else
				ptr = ptr->right;
		}
		return const_iterator(pos);
	}

	iterator upper_bound(const Key& key)
	{
		node_ptr ptr = _root;
		node_ptr pos  = _end_node;

		while (ptr != _end_node && ptr != _NTREE)
		{
			if (_key_compare(key, ptr->value_field))
			{
				pos = ptr;
				ptr = ptr->left;
			}
			else
				ptr = ptr->right;
		}
		return iterator(pos);
	}

	const_iterator upper_bound(const Key& key) const
	{
		node_ptr ptr = _root;
		node_ptr pos  = _end_node;

		while (ptr != _end_node && ptr != _NTREE)
		{
			if (_key_compare(key, ptr->value_field))
			{
				pos = ptr;
				ptr = ptr->left;
			}
			else
				ptr = ptr->right;
		}
		return const_iterator(pos);
	}

	ft::pair<iterator, iterator>
	equal_range(const Key& key)
	{
		return ft::make_pair(lower_bound(key), upper_bound(key));
	}

	void clear(void)
	{
		delEnd();
		destroyTree(_root);
		addEnd();
		_size = 0;
	}

	void swap(Rb_set_tree &other)
	{
		std::swap(_root, other._root);
		std::swap(_NTREE, other._NTREE);
		std::swap(_end_node, other._end_node);
		std::swap(_key_compare, other._key_compare);
		std::swap(_size, other._size);
		std::swap(_alloc, other._alloc);
	}

protected:


public:

	//------| Begin and End iterators |---------

	iterator        begin()
	{ return static_cast<iterator>(minNode(this->_root)); }
	const_iterator  begin() const
	{ return static_cast<const_iterator>(minNode(this->_root)); };

	iterator        end()
	{ return static_cast<iterator>(this->_end_node); }
	const_iterator  end() const
	{ return static_cast<const_iterator>(this->_end_node); }

	reverse_iterator		rbegin()
	{ return static_cast<reverse_iterator>(end()); }
	const_reverse_iterator	rbegin() const
	{ return static_cast<const_reverse_iterator>(end()); }

	reverse_iterator		rend()
	{ return static_cast<reverse_iterator>(begin()); }
	const_reverse_iterator	rend() const
	{ return static_cast<const_reverse_iterator>(begin()); }

	friend struct Rb_tree_iterator<value_type>;
};


#endif