/* ************************************************************************** */
/*																			  */
/*   Project:	ft_containers                             :::      ::::::::   */
/*   File:		tester.hpp	                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 by athekkep 		           #+#    #+#             */
/*   Updated: 2023/01/23 by athekkep                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
#define TESTER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sys/time.h>

/* STL CONTAINERS */
#include <vector>
#include <stack>
#include <map>
#include <set>

/* FT CONTAINERS*/
#include "../includes/containers/vector.hpp"
#include "../includes/containers/stack.hpp"
#include "../includes/containers/map.hpp"
#include "../includes/containers/set.hpp"

/* TESTER VARIABLES */
#ifndef	FT
	#define VEC_FILE	"std_vec_test"
	#define MAP_FILE	"std_map_test"
	#define STACK_FILE	"std_stack_test"
	#define SET_FILE	"std_set_test"
	#define NAMESPACE	std
	#define	TYPE		"std"
#else
	#define VEC_FILE	"ft_vec_test"
	#define MAP_FILE	"ft_map_test"
	#define STACK_FILE	"ft_stack_test"
	#define SET_FILE	"ft_set_test"
	#define NAMESPACE	ft
	#define	TYPE		"ft"
#endif

/* BUFFER */
#define BIG_BUF	10000000	// 10,000,000
#define MID_BUF	100000		//    100,000
#define SML_BUF	1000		//		1,000

/* VECTOR TESTER */
template<class T> void 	print_vec_content(std::string, T &, std::ostream &);
template<class T> void 	print_vec_status(std::string, T &, std::ostream &);
void					run_vec_test();

/* STACK TESTER */
template<class T> void	print_stack_status(std::string, T &, std::ostream &);
void					run_stack_test();

/* MAP TESTER */
template<class T> void	print_map_content(std::string, T &, std::ostream &);
template<class T> void	print_map_status(std::string, T &, std::ostream &);
void 					run_map_test();

/* SET TESTER */
template<class T> void 	print_set_content(std::string, T &, std::ostream &);
template<class T> void 	print_set_status(std::string, T &, std::ostream &);
void 					run_set_test();

#endif