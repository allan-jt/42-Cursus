/* ************************************************************************** */
/*																			  */
/*   Project:	ft_containers                             :::      ::::::::   */
/*   File:		pair.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 by athekkep 		           #+#    #+#             */
/*   Updated: 2023/12/28 by athekkep                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

#include "../algorithm/lexicographical_compare.hpp"

namespace ft {

template <class T1, class T2> struct pair {
	public:
/* 		Types_________________________________________________________________*/	
		typedef T1	first_type;
		typedef T2	second_type;

/* 		Variables_____________________________________________________________*/
		first_type	first;
		second_type	second;

/* 		Constructors, destructors, & assignment operator overload_____________*/
		pair() : first(first_type()), second(second_type()) {}

		template<class U, class V> 
		pair(const pair<U,V> &pr) : first(pr.first), second(pr.second) {}

		pair(const first_type& a, const second_type& b) : first(a), second(b) {}

		pair& operator= (const pair& pr) {
			if (this != &pr) {
				first = pr.first;
				second = pr.second;
			}
			return *this;
		}

/* 		Non-member function___________________________________________________*/
		friend bool operator== (const pair &lhs, const pair &rhs) {
			return (lhs.first == rhs.first && lhs.second == rhs.second);
		}

		friend bool operator!= (const pair &lhs, const pair &rhs) {
			return !(lhs == rhs);
		}

		friend bool operator< (const pair &lhs, const pair &rhs) {
			return (lhs.first < rhs.first) ||
				(lhs.first == rhs.first && lhs.second < rhs.second);
		}
		
		friend bool operator<= (const pair &lhs, const pair &rhs) {
			return !(rhs < lhs);
		}
		
		friend bool operator> (const pair &lhs, const pair &rhs) {
			return (rhs < lhs);
		}
		
		friend bool operator>= (const pair &lhs, const pair &rhs) {
			return !(lhs < rhs);
		}
};

template< class T1, class T2 >
ft::pair<T1, T2> make_pair( T1 t, T2 u ) {return ft::pair<T1, T2>(t, u);}

};

#endif
