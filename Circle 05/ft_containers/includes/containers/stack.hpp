/* ************************************************************************** */
/*																			  */
/*   Project:	ft_containers                             :::      ::::::::   */
/*   File:		stack.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 by athekkep 		           #+#    #+#             */
/*   Updated: 2023/01/19 by athekkep                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {

template < class T, class Container = ft::vector<T> > class stack {
	public:
/* 		Types_________________________________________________________________*/
		typedef	Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;
	
	protected:
		container_type	c;
	
	public:
/* 		Constructors, destructors, & assignment operator overload_____________*/
		explicit stack (const container_type& ctnr = container_type())
			: c(ctnr) {}

		stack(const stack &other) : c(other.c) {}

		stack &operator=(const stack &other) {
			if (this != &other)
				c = other.c;
			return *this;
		}

		~stack() {}

/* 		Functions_____________________________________________________________*/
		bool 		empty() const	{return c.empty();}
		size_type 	size() const	{return c.size();}
		
		value_type& 		top() 		{return c.back();}
		const value_type& 	top() const	{return c.back();}
		
		void pop() {c.pop_back();}
		void push (const value_type& val) {
			return c.push_back(val);
		}

/* 		Operator overloads____________________________________________________*/
		friend bool operator== (const stack &lhs, const stack &rhs) {
			return lhs.c == rhs.c;
		}

		friend bool operator!= (const stack &lhs, const stack &rhs) {
			return lhs.c != rhs.c;
		}

		friend bool operator< (const stack &lhs, const stack &rhs) {
			return lhs.c < rhs.c;
		}

		friend bool operator<= (const stack &lhs, const stack &rhs) {
			return lhs.c <= rhs.c;
		}

		friend bool operator> (const stack &lhs, const stack &rhs) {
			return lhs.c > rhs.c;
		}

		friend bool operator>= (const stack &lhs, const stack &rhs) {
			return lhs.c >= rhs.c;
		}
};

};

#endif