/* ************************************************************************** */
/*																			  */
/*   Project:	ft_containers                             :::      ::::::::   */
/*   File:		reverse_iterator.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 by athekkep 		           #+#    #+#             */
/*   Updated: 2022/12/27 by athekkep                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

#define ITER_TRAITS	iterator_traits<Iterator>
#define REV_ITER1	reverse_iterator<Iterator1>
#define REV_ITER2	reverse_iterator<Iterator2>

namespace ft {
template<class Iterator> class reverse_iterator {
	public:
/* 		Types_________________________________________________________________*/
		typedef Iterator								iterator_type;
		typedef typename ITER_TRAITS::iterator_category	iterator_category;
		typedef	typename ITER_TRAITS::value_type		value_type;
		typedef	typename ITER_TRAITS::difference_type	difference_type;
		typedef	typename ITER_TRAITS::pointer			pointer;
		typedef	typename ITER_TRAITS::reference			reference;

	protected:
		iterator_type	current;

	public:
/* 		Constructors & base___________________________________________________*/
		reverse_iterator() : current() {}

		explicit reverse_iterator(iterator_type it) : current(it) {}

		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &rev_it)
			: current(rev_it.base()) {};

		iterator_type base() const {return current;}

/* 		Operator overloads____________________________________________________*/
		reference operator*() const {
			iterator_type copy(current);
			return *(--copy);
		}

		pointer operator->() const {return &(**this);}

		reference operator[] (difference_type n) const {
			iterator_type copy(current);
			for (difference_type i = 0; i < n; i++)
				copy--;
			return *(--copy);
		}

		reverse_iterator operator+ (difference_type n) const {
			return reverse_iterator(current - n);
		}
		reverse_iterator operator- (difference_type n) const {
			return reverse_iterator(current + n);
		}

		reverse_iterator& operator++() {
			current--;
			return *this;
		}
		reverse_iterator  operator++(int) {
			reverse_iterator copy(*this);
			++(*this);
			return copy;
		}

		reverse_iterator& operator--() {
			current++;
			return *this;
		}
		reverse_iterator  operator--(int) {
			reverse_iterator copy(*this);
			--(*this);
			return copy;
		}

		reverse_iterator& operator+= (difference_type n) {
			current -= n;
			return *this;
		}
		reverse_iterator& operator-= (difference_type n) {
			current += n;
			return *this;
		}
};

/*	Non-member operator overloads_____________________________________________*/
template< class Iterator1, class Iterator2 >
bool operator== (const REV_ITER1 &lhs, const REV_ITER2 &rhs) {
	return lhs.base() == rhs.base();
}

template< class Iterator1, class Iterator2 >
bool operator!= (const REV_ITER1 &lhs, const REV_ITER2 &rhs) {
	return lhs.base() != rhs.base();
}

template< class Iterator1, class Iterator2 >
bool operator< (const REV_ITER1 &lhs, const REV_ITER2 &rhs) {
	return lhs.base() > rhs.base();
}

template< class Iterator1, class Iterator2 >
bool operator<= (const REV_ITER1 &lhs, const REV_ITER2 &rhs) {
	return lhs.base() >= rhs.base();
}

template< class Iterator1, class Iterator2 >
bool operator> (const REV_ITER1 &lhs, const REV_ITER2 &rhs) {
	return lhs.base() < rhs.base();
}

template< class Iterator1, class Iterator2 >
bool operator>= (const REV_ITER1 &lhs, const REV_ITER2 &rhs) {
	return lhs.base() <= rhs.base();
}

template< class Iterator1 >
REV_ITER1 operator+ (typename REV_ITER1::difference_type n,
	const REV_ITER1& it) {return it + n;}

template < class Iterator1, class Iterator2 >
typename REV_ITER1::difference_type operator- (const REV_ITER1 &lhs,
	const REV_ITER2 &rhs) {return rhs.base() - lhs.base();}

};

#endif