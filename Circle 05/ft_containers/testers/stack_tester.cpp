/* ************************************************************************** */
/*																			  */
/*   Project:	ft_containers                             :::      ::::::::   */
/*   File:		stack_tester.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 by athekkep 		           #+#    #+#             */
/*   Updated: 2023/01/22 by athekkep                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

template<class T> void print_stack_status(std::string name,
	T &c, std::ostream &results) {
	
	results << name << " Status:	" << std::endl;
	results << "Empty:	" << c.empty() << std::endl
			<< "Size:	" << c.size() << std::endl;
	if (c.size() == 0) {
		results << "Top element:	None" << std::endl;
	} else {
		results << "Top element:	" << c.top() << std::endl;
	}
}

void run_stack_test() {
	std::ofstream	results(STACK_FILE);
	NAMESPACE::stack<int, NAMESPACE::vector<int> >	s1;

	results << "1. Functions________________________________________________\n";
/* 	1. Functions______________________________________________________________*/
	print_stack_status("s1 before push()", s1, results);

	for (int i = 0; i < MID_BUF; i++)
		s1.push(i);
	print_stack_status("s1 after push()", s1, results);
	results << std::endl;

	results << "top() & pop()" << std::endl;
	for (int i = 0; i < 10; i++) {
		results << s1.top() << " ";
		s1.pop();
	}
	results << std::endl;
	print_stack_status("s1 after pop()", s1, results);
	results << std::endl;

	results << "2. Constructors_____________________________________________\n";
/*	2. Constructors, destructors, & assignment operator overload______________*/
	NAMESPACE::vector<int> v1(10, 10);
	NAMESPACE::stack<int, NAMESPACE::vector<int> > s2(s1);
	NAMESPACE::stack<int, NAMESPACE::vector<int> > s3(v1);
	
	print_stack_status("s2(s1)", s2, results);
	print_stack_status("s3(v1)", s3, results);
	s2 = s3;
	print_stack_status("s2 = s3", s2, results);
	results << std::endl;

	results << "3. Operators________________________________________________\n";
/* 	3. Operator overloads_____________________________________________________*/
		results << "s2 == s3:	" << (s2 == s3) << std::endl
			<< "s2 != s1:	" << (s2 != s1) << std::endl
			<< "s2 < s3:	" << (s2 < s3) << std::endl
			<< "s2 <= s3:	" << (s2 <= s3) << std::endl
			<< "s2 > s3:	" << (s2 > s3) << std::endl
			<< "s2 >= s3:	" << (s2 >= s3) << std::endl;
	results << std::endl;

	results.close();
}	