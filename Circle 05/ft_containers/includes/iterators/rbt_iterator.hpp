/* ************************************************************************** */
/*																			  */
/*   Project:	ft_containers                             :::      ::::::::   */
/*   File:		rbt_iterator.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 by athekkep 		           #+#    #+#             */
/*   Updated: 2022/01/15 by athekkep                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_ITERATOR_HPP
#define RBT_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "../utilities/rbt_node.hpp"

#define RBT_TRAITS	iterator_traits<Val*>
#define RBT_ITER1	rbt_iterator<N1, V1>
#define RBT_ITER2	rbt_iterator<N2, V2>
namespace ft {

template<class Val, class Node> class rbt_iterator {
	public:
/* 		Types_________________________________________________________________*/
		typedef typename RBT_TRAITS::difference_type	difference_type;
		typedef typename RBT_TRAITS::value_type			value_type;
		typedef typename RBT_TRAITS::pointer			pointer;
		typedef typename RBT_TRAITS::reference			reference;
		typedef std::bidirectional_iterator_tag			iterator_category;
		typedef Node*									node_ptr;
	
	private:
		node_ptr	_node;
	
	public:
/* 		Constructors, destructors, & assignment operator overload_____________*/
		rbt_iterator() : _node(NULL) {}
		
		rbt_iterator(const node_ptr &val_ptr) : _node(val_ptr) {}
		
		rbt_iterator(const rbt_iterator &it) : _node(it._node) {}

		node_ptr	base() const 	{return _node;}

		~rbt_iterator() {}

/* 		Operator overloads____________________________________________________*/
		reference	operator*() const	{return _node->get_value();}
		pointer 	operator->() const 	{return &(_node->get_value());}

		rbt_iterator& operator++() {
			_node = _node->get_next_by_val();
			return *this;
		}
		rbt_iterator  operator++(int) {
			rbt_iterator copy(*this);
			++(*this);
			return copy;
		}

		rbt_iterator& operator--() {
			_node = _node->get_prev_by_val();
			return *this;
		}
		rbt_iterator  operator--(int) {
			rbt_iterator copy(*this);
			--(*this);
			return copy;
		}

		operator rbt_iterator<const Val, Node>() const {
			return rbt_iterator<const Val, Node>(_node);
		}

};

/*	Non-member operator overloads_____________________________________________*/
template< class N1, class N2, class V1, class V2 >
bool operator== (const RBT_ITER1 &lhs, const RBT_ITER2 &rhs) {
	return lhs.base() == rhs.base();
}

template< class N1, class N2, class V1, class V2 >
bool operator!= (const RBT_ITER1 &lhs, const RBT_ITER2 &rhs) {
	return lhs.base() != rhs.base();
}

};

#endif