/* ************************************************************************** */
/*																			  */
/*   Project:	ft_containers                             :::      ::::::::   */
/*   File:		set.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 by athekkep 		           #+#    #+#             */
/*   Updated: 2023/01/18 by athekkep                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

#include "../algorithm/equal.hpp"
#include "../algorithm/lexicographical_compare.hpp"
#include "../utilities/rbt.hpp"
#include "../utilities/pair.hpp"

#define SET_TYPE	set<T,Compare,Alloc>

namespace ft {

template< class T, class Compare = std::less<T>,
		  class Alloc = std::allocator<T>
> class set {
	public:
/* 		Types_________________________________________________________________*/
		typedef T					key_type;
		typedef T					value_type;
		typedef size_t				size_type;
		typedef ptrdiff_t			difference_type;
		typedef Compare				key_compare;
		typedef Compare				value_compare;
		
		typedef Alloc							allocator_type;
		typedef typename Alloc::reference		reference;
		typedef typename Alloc::const_reference	const_reference;
		typedef typename Alloc::pointer			pointer;
		typedef typename Alloc::const_pointer	const_pointer;

		typedef ft::RBT<const T, value_compare, allocator_type>	tree;
		typedef typename tree::iterator					iterator;
		typedef typename tree::const_iterator			const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef typename tree::pointer					node_pointer;
	
	private:
/*		Attributes____________________________________________________________*/	
		value_compare	_comp;
		allocator_type	_alloc;
		tree			_data;

	public:
/* 		Constructors, destructors, & assignment operator overload_____________*/
		explicit set(const key_compare& comp = key_compare(),
					 const allocator_type& alloc = allocator_type()) 
			: _comp(comp), _alloc(alloc), _data(tree(_comp)) {}
		
		template<class InputIterator>
		set(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
			: _comp(comp), _alloc(alloc), _data(tree(_comp)) {

			insert(first, last);
		}

		set(const set& x) : _comp(x._comp), _alloc(x._alloc), _data(x._data) {}

		~set() {}

		set &operator= (const set &x) {
			if (this != &x)
				_data = x._data;
			return *this;
		}

/* 		Iterators_____________________________________________________________*/
		iterator		begin() 		{return _data.begin();}
		const_iterator	begin() const 	{return _data.begin();}
		
		iterator		end() 		{return _data.end();}
		const_iterator	end() const {return _data.end();}

		reverse_iterator		rbegin() 		{return _data.rbegin();}
		const_reverse_iterator	rbegin() const	{return _data.rbegin();}
		
		reverse_iterator		rend()			{return _data.rend();}
		const_reverse_iterator	rend() const 	{return _data.rend();}		

/* 		Capacity______________________________________________________________*/
		bool		empty() const		{return _data.empty();}
		size_type	size() const 		{return _data.size();}
		size_type	max_size() const	{return _data.max_size();}

/* 		Modifiers_____________________________________________________________*/
		template<class InputIterator>
		void insert(InputIterator first, InputIterator last) {
			_data.insert(first, last);
		}

		iterator	insert(iterator position, const value_type& val) {
			return _data.insert(position, val);
		}

		ft::pair<iterator, bool>	insert(const value_type& val) {
			return _data.insert(val);
		}

		void	erase(iterator position)				{_data.erase(position);}
		void	erase(iterator first, iterator last) {_data.erase(first, last);}
		
		size_type	erase(const value_type &val) {
			return _data.delete_value(val);
		}

		void swap(set &x)	{_data.swap(x._data);}
		void clear()		{_data.clear();}

/* 		Observers_____________________________________________________________*/
		key_compare		key_comp() const 		{return _comp;}
		value_compare	value_comp() const		{return _comp;}
		allocator_type	get_allocator() const 	{return _alloc;}

/* 		Operations____________________________________________________________*/
		iterator		find(const key_type &k) 		{return _data.find(k);}
		const_iterator	find(const key_type &k) const 	{return _data.find(k);}
		size_type		count(const key_type &k ) const {return _data.count(k);}

		iterator	lower_bound(const key_type& k) {
			return _data.lower_bound(k);
		}

		const_iterator	lower_bound(const key_type& k) const {
			return _data.lower_bound(k);
		}

		iterator	upper_bound(const key_type& k) {
			return _data.upper_bound(k);
		}

		const_iterator	upper_bound(const key_type& k) const {
			return _data.upper_bound(k);
		}

		ft::pair<iterator, iterator> equal_range(const key_type& k) {
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

		ft::pair<const_iterator, const_iterator> 
			equal_range(const key_type& k) const {
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

/*		Non-member function overloads_________________________________________*/
		friend bool operator== (const set &lhs, const set &rhs) {
			return lhs._data.is_equal(rhs._data);
		}
};

template<class T, class Compare, class Alloc>
bool operator!= (const SET_TYPE &lhs, const SET_TYPE &rhs) {
	return !(lhs == rhs);
}

template<class T, class Compare, class Alloc>
bool operator< (const SET_TYPE &lhs, const SET_TYPE &rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(),
		rhs.begin(), rhs.end());
}

template<class T, class Compare, class Alloc>
bool operator<= (const SET_TYPE &lhs, const SET_TYPE &rhs) {
	return !(rhs < lhs);
}

template<class T, class Compare, class Alloc>
bool operator> (const SET_TYPE &lhs, const SET_TYPE &rhs) {
	return rhs < lhs;
}

template<class T, class Compare, class Alloc>
bool operator>= (const SET_TYPE &lhs, const SET_TYPE &rhs) {
	return !(lhs < rhs);
}

template<class T, class Compare, class Alloc>
void swap(SET_TYPE &lhs, SET_TYPE &rhs) {lhs.swap(rhs);}

};

#endif