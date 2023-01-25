/* ************************************************************************** */
/*																			  */
/*   Project:	ft_containers                             :::      ::::::::   */
/*   File:		equal.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 by athekkep 		           #+#    #+#             */
/*   Updated: 2022/12/24 by athekkep                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	EQUAL_HPP
#define EQUAL_HPP

namespace ft {

template<class InputIt1, class InputIt2>
bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
	while (first1 != last1)
		if (*first1++ != *first2++)
			return false;
	return true;
}

template<class InputIt1, class InputIt2, class BinaryPredicate>
bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2,
		BinaryPredicate p) {
	while (first1 != last1)
		if (!p(*first1++, *first2++))
			return false;
	return true;
}

};

#endif