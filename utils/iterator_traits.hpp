#ifndef _ITERATOR_TRAITS_HPP_
#define _ITERATOR_TRAITS_HPP_

#include <cstddef> //ptrdiff_t

namespace ft
{
	// Bu etiketler c++11'den itibaren doğrudan(miras bağı olmadan) kullanıldığı için testerda bunların kullanılması sıkıntı çıkarıyor
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };
	//---------------------------

	template <class Iterator>
	struct iterator_traits {
	public:
		typedef typename Iterator::value_type								value_type;
		typedef typename Iterator::difference_type								difference_type;
		typedef typename Iterator::pointer									pointer;
		typedef typename Iterator::const_pointer								const_pointer;
		typedef typename Iterator::reference								reference;
		typedef typename Iterator::const_reference								const_reference;
		typedef typename Iterator::iterator_category							iterator_category;
	};

	template <typename T>
	struct iterator_traits<T*> {
	public:
		typedef T											value_type;
		typedef T*											pointer;
		typedef const T*										const_pointer;
		typedef T&											reference;
		typedef const T&										const_reference;
		typedef ptrdiff_t										difference_type;
		typedef std::random_access_iterator_tag								iterator_category;
	};
}

#endif