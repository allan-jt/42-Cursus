/* ************************************************************************** */
/*																			  */
/*   Project:	ft_containers                             :::      ::::::::   */
/*   File:		map.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 by athekkep 		           #+#    #+#             */
/*   Updated: 2022/01/18 by athekkep                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "../algorithm/equal.hpp"
#include "../algorithm/lexicographical_compare.hpp"
#include "../type_traits/is_integral.hpp"
#include "../type_traits/enable_if.hpp"
#include "../utilities/rbt.hpp"
#include "../utilities/pair.hpp"

#define MAP_TYPE	map<Key,T,Compare,Alloc>
namespace ft {

template< class Key, class T,
		  class Compare = std::less<Key>,
		  class Alloc = std::allocator< ft::pair< const Key, T > >
> class map {
	public:
/* 		Types_________________________________________________________________*/		
		typedef Key								key_type;
		typedef T								mapped_type;
		typedef ft::pair<const Key, T>			value_type;
		typedef size_t							size_type;
		typedef ptrdiff_t						difference_type;
		typedef Compare							key_compare;
		typedef Alloc							allocator_type;
		typedef typename Alloc::reference		reference;
		typedef typename Alloc::const_reference	const_reference;
		typedef typename Alloc::pointer			pointer;
		typedef typename Alloc::const_pointer	const_pointer;
		
/*		Member class__________________________________________________________*/	
		class value_compare 
			: public std::binary_function<value_type, value_type, bool> {
			protected:
				key_compare	comp;
				value_compare(key_compare c) : comp(c) {}
			
			public:
				friend class map;				
				bool operator() (const value_type &lhs,
								 const value_type &rhs) const {
					return comp(lhs.first, rhs.first);
				}
		};

/*		RBT types_____________________________________________________________*/
		typedef ft::RBT<value_type, value_compare, allocator_type>	tree;
		typedef typename tree::iterator					iterator;
		typedef typename tree::const_iterator			const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef typename tree::pointer					node_pointer;

	private:
/*		Attributes____________________________________________________________*/	
		value_compare	_val_comp;
		allocator_type	_alloc;
		tree			_data;

	public:
/* 		Constructors, destructors, & assignment operator overload_____________*/
		explicit map(const key_compare& comp = key_compare(),
					 const allocator_type& alloc = allocator_type()) 
				: _val_comp(comp), _alloc(alloc), _data(tree(_val_comp)) {}
		
		template<class InputIterator>
		map(InputIterator first, InputIterator last, 
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type())
			: _val_comp(comp), _alloc(alloc), _data(tree(_val_comp)) {

			insert(first, last);
		}
	
		map(const map &x) : _val_comp(x._val_comp), _alloc(x._alloc),
							_data(x._data) {}

		~map() {}

		map &operator= (const map &x) {
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

/* 		Element access________________________________________________________*/
		allocator_type	get_allocator() const {return _alloc;}

		mapped_type &at(const key_type& k) {
			value_type	empty(k, mapped_type());
			return _data.get_value(empty).second;
		}

		const mapped_type &at(const key_type& k) const {
			value_type	empty(k, mapped_type());
			return _data.get_value(empty).second;
		}

		mapped_type &operator[] (const key_type& k) {
			value_type	empty(k, mapped_type());
			try {
				return _data.get_value(empty).second;
			} catch (std::exception &e) {
				return (*(insert(empty).first)).second;
			}
		}

/* 		Modifiers_____________________________________________________________*/
		void	erase(iterator position) 				{_data.erase(position);}
		void	erase(iterator first, iterator last) {_data.erase(first, last);}

		size_type	erase(const key_type& k) {
			value_type	empty(k, mapped_type());
			return _data.delete_value(empty);
		}
		
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

		void swap(map &x)	{_data.swap(x._data);}
		void clear()		{_data.clear();}

/* 		Observers_____________________________________________________________*/
		key_compare		key_comp() const 	{return _val_comp.comp;}
		value_compare	value_comp() const	{return _val_comp;}

/* 		Operations____________________________________________________________*/
		iterator	find(const key_type& k) {
			value_type	empty(k, mapped_type());
			return _data.find(empty);
		}

		const_iterator	find(const key_type& k) const {
			value_type	empty(k, mapped_type());
			return _data.find(empty);
		}

		size_type	count(const key_type& k) const {
			value_type	empty(k, mapped_type());
			return _data.count(empty);
		}

		iterator	lower_bound(const key_type& k) {
			value_type	empty(k, mapped_type());
			return _data.lower_bound(empty);
		}

		const_iterator	lower_bound(const key_type& k) const {
			value_type	empty(k, mapped_type());
			return _data.lower_bound(empty);
		}

		iterator	upper_bound(const key_type& k) {
			value_type	empty(k, mapped_type());
			return _data.upper_bound(empty);
		}

		const_iterator	upper_bound(const key_type& k) const {
			value_type	empty(k, mapped_type());
			return _data.upper_bound(empty);
		}

		ft::pair<iterator, iterator> equal_range(const key_type& k) {
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

		ft::pair<const_iterator, const_iterator>
			equal_range(const key_type& k) const {
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

/*		Non-member function overloads_________________________________________*/
		friend bool operator== (const map &lhs, const map &rhs) {
			return lhs._data.is_equal(rhs._data);
		}
};

template<class Key, class T, class Compare, class Alloc>
bool operator!= (const MAP_TYPE &lhs, const MAP_TYPE &rhs) {
	return !(lhs == rhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator< (const MAP_TYPE &lhs, const MAP_TYPE &rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(),
		rhs.begin(), rhs.end());
}

template<class Key, class T, class Compare, class Alloc>
bool operator<= (const MAP_TYPE &lhs, const MAP_TYPE &rhs) {
	return !(rhs < lhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator> (const MAP_TYPE &lhs, const MAP_TYPE &rhs) {
	return rhs < lhs;
}

template<class Key, class T, class Compare, class Alloc>
bool operator>= (const MAP_TYPE &lhs, const MAP_TYPE &rhs) {
	return !(lhs < rhs);
}

template<class Key, class T, class Compare, class Alloc>
void swap(MAP_TYPE &lhs, MAP_TYPE &rhs) {lhs.swap(rhs);}

};

/*

MAP TESTERS

void	print_in_order() {
	_data.print_order();
}

void print_level_order() {
	_data.print_level_order();
}

void print_visual() {
	_data.print2D();
}

*/

#endif