/* ************************************************************************** */
/*																			  */
/*   Project:	ft_containers                             :::      ::::::::   */
/*   File:		vector_iterator.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 by athekkep 		           #+#    #+#             */
/*   Updated: 2022/12/27 by athekkep                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator_traits.hpp"

#define VEC_TRAITS	iterator_traits<T*>
#define VEC_ITER1	vector_iterator<T1>
#define VEC_ITER2	vector_iterator<T2>

namespace ft {

template< class T > class vector_iterator {
	public:
/* 		Types_________________________________________________________________*/
		typedef typename VEC_TRAITS::difference_type	difference_type;
		typedef typename VEC_TRAITS::value_type			value_type;
		typedef typename VEC_TRAITS::pointer			pointer;
		typedef typename VEC_TRAITS::reference			reference;
		typedef typename VEC_TRAITS::iterator_category	iterator_category;
	
	private:
		pointer	base_ptr;
	
	public:
/* 		Constructors, destructors, & assignment operator overload_____________*/
		vector_iterator() : base_ptr(NULL) {}
		
		explicit vector_iterator(pointer val_ptr) : base_ptr(val_ptr) {}
		
		template<class type> vector_iterator(const vector_iterator<type>& it)
			: base_ptr(it.base()) {}

		pointer	base() const {return base_ptr;}	

		~vector_iterator() {}

/* 		Operator overloads____________________________________________________*/
		reference operator*() const 					{return *base_ptr;}
		pointer operator->() const 						{return base_ptr;}
		reference operator[] (difference_type n) const 	{return base_ptr[n];}

		vector_iterator operator+ (difference_type n) const {
			return vector_iterator(base_ptr + n);
		}
		vector_iterator operator- (difference_type n) const {
			return vector_iterator(base_ptr - n);
		}

		vector_iterator& operator++() {
			base_ptr++;
			return *this;
		}
		vector_iterator  operator++(int) {
			vector_iterator copy(*this);
			++(*this);
			return copy;
		}

		vector_iterator& operator--() {
			base_ptr--;
			return *this;
		}
		vector_iterator  operator--(int) {
			vector_iterator copy(*this);
			--(*this);
			return copy;
		}

		vector_iterator& operator+= (difference_type n) {
			base_ptr += n;
			return *this;
		}
		vector_iterator& operator-= (difference_type n) {
			base_ptr -= n;
			return *this;
		}
};

/*	Non-member operator overloads_____________________________________________*/
template< class T1, class T2 >
bool operator== (const VEC_ITER1 &lhs, const VEC_ITER2 &rhs) {
	return lhs.base() == rhs.base();
}

template< class T1, class T2 >
bool operator!= (const VEC_ITER1 &lhs, const VEC_ITER2 &rhs) {
	return lhs.base() != rhs.base();
}

template< class T1, class T2 >
bool operator< (const VEC_ITER1 &lhs, const VEC_ITER2 &rhs) {
	return lhs.base() < rhs.base();
}

template< class T1, class T2 >
bool operator<= (const VEC_ITER1 &lhs, const VEC_ITER2 &rhs) {
	return lhs.base() <= rhs.base();
}

template< class T1, class T2 >
bool operator> (const VEC_ITER1 &lhs, const VEC_ITER2 &rhs) {
	return lhs.base() > rhs.base();
}

template< class T1, class T2 >
bool operator>= (const VEC_ITER1 &lhs, const VEC_ITER2 &rhs) {
	return lhs.base() >= rhs.base();
}

template< class T1 >
VEC_ITER1 operator+ (typename VEC_ITER1::difference_type n,
	const VEC_ITER1 &it) {return it + n;}

template < class T1, class T2 >
typename VEC_ITER1::difference_type operator- (const VEC_ITER1 &lhs,
	const VEC_ITER2 &rhs) {return lhs.base() - rhs.base();}

};

#endif