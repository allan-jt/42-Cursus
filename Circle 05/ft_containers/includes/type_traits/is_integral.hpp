/* ************************************************************************** */
/*																			  */
/*   Project:	ft_containers                             :::      ::::::::   */
/*   File:		is_integral.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 by athekkep 		           #+#    #+#             */
/*   Updated: 2022/12/26 by athekkep                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	IS_INTEGRAL_HPP
#define	IS_INTEGRAL_HPP

namespace ft {

/* 		Non-integral types____________________________________________________*/
template<class T> struct is_integral {
	static const bool value = false;
	operator bool() {return value;}
};

/* 		Integral types________________________________________________________*/
template<> struct is_integral<bool> {
	static const bool value = true;
	operator bool() {return value;}
};

template<> struct is_integral<char> {
	static const bool value = true;
	operator bool() {return value;}
};

template<> struct is_integral<wchar_t> {
	static const bool value = true;
	operator bool() {return value;}
};

template<> struct is_integral<signed char> {
	static const bool value = true;
	operator bool() {return value;}
};

template<> struct is_integral<short int> {
	static const bool value = true;
	operator bool() {return value;}
};

template<> struct is_integral<int> {
	static const bool value = true;
	operator bool() {return value;}
};

template<> struct is_integral<long int> {
	static const bool value = true;
	operator bool() {return value;}
};

template<> struct is_integral<long long int> {
	static const bool value = true;
	operator bool() {return value;}
};

template<> struct is_integral<unsigned char> {
	static const bool value = true;
	operator bool() {return value;}
};

template<> struct is_integral<unsigned short int> {
	static const bool value = true;
	operator bool() {return value;}
};

template<> struct is_integral<unsigned int> {
	static const bool value = true;
	operator bool() {return value;}
};

template<> struct is_integral<unsigned long int> {
	static const bool value = true;
	operator bool() {return value;}
};

template<> struct is_integral<unsigned long long int> {
	static const bool value = true;
	operator bool() {return value;}
};

};

#endif