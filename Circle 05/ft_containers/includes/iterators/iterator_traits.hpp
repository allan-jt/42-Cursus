/* ************************************************************************** */
/*																			  */
/*   Project:	ft_containers                             :::      ::::::::   */
/*   File:		iterator_traits.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 by athekkep 		           #+#    #+#             */
/*   Updated: 2022/12/27 by athekkep                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <cstddef>
#include <iterator>	/* USED ONLY FOR ITERATOR TAGS */

namespace ft {
/* 		Tags__________________________________________________________________*/
/*struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag 		: public input_iterator_tag {};
struct bidirectional_iterator_tag 	: public forward_iterator_tag {};
struct random_access_iterator_tag 	: public bidirectional_iterator_tag {};
*/
/* 		Traits________________________________________________________________*/
template<class Iterator> struct iterator_traits {
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
};

template<class T> struct iterator_traits<T*> {
	typedef ptrdiff_t						difference_type;
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef std::random_access_iterator_tag	iterator_category;
};

template<class T> struct iterator_traits<const T*> {
	typedef ptrdiff_t						difference_type;
	typedef T								value_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	typedef std::random_access_iterator_tag	iterator_category;
};
};

/*
#include <typeinfo>     // typeid

int main() {
  typedef std::iterator_traits<int*> traits;
  if (typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag))
    std::cout << "int* is a random-access iterator";
  return 0;
}
*/

#endif