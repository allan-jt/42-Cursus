/* ************************************************************************** */
/*																			  */
/*   Project:	ft_containers                             :::      ::::::::   */
/*   File:		set_tester.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 by athekkep 		           #+#    #+#             */
/*   Updated: 2023/01/23 by athekkep                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

template<class T> void print_set_content(std::string name, T &c,
	std::ostream &results) {
	
	results << name << " Content: ";
	for (typename T::iterator it = c.begin(); it != c.end(); it++)
		results << *it << " ";
	results << std::endl;
}

template<class T> void print_set_status(std::string name, T &c,
	std::ostream &results) {
	
	results << name << " Status:	" << std::endl;
	results << "Empty:	" << c.empty() << std::endl
			<< "Size:	" << c.size() << std::endl;
	if (c.begin() == c.end()) {
		results << "First element:	None" << std::endl
				<< "Last element:	None" << std::endl;
	} else {
		results << "First element:	" << *(c.begin()) << std::endl
				<< "Last element:	" << *(--c.end()) << std::endl;
	}
}

void run_set_test() {
	std::ofstream	results(SET_FILE);
	NAMESPACE::vector<int> v1;
	for (int i = 0; i < 10; i++)
		v1.push_back(i);

	results << "1. Constructors_____________________________________________\n";
/*	1. Constructors, destructors, & assignment operator overload______________*/
	NAMESPACE::set<int>	s1;
	NAMESPACE::set<int>	s2(v1.begin(), v1.end());
	NAMESPACE::set<int>	s3(s2);
	NAMESPACE::set<int>	s4;
	s4 = s2;

	print_set_status("s1", s1, results);
	print_set_status("s2", s2, results);
	print_set_status("s3", s3, results);
	print_set_status("s4", s4, results);
	results << std::endl << std::endl;


	results << "2. Iterators________________________________________________\n";
/*	2. Iterators______________________________________________________________*/
	for (int i = 0; i < 10; i++)
		s1.insert(i);
	print_set_status("s1 insert()", s1, results);
	
	results << "Normal iterator: ";
	for(NAMESPACE::set<int>::iterator it = s1.begin();
		it != s1.end(); it++) {
		results << *it << " ";
	}
	results << std::endl;

	results << "Reverse iterator: ";
	for(NAMESPACE::set<int>::reverse_iterator it = s1.rbegin();
		it != s1.rend(); it++) {
		results << *it << " ";
	}
	results << std::endl << std::endl;


	results << "3. Capcity__________________________________________________\n";
/*	3. Capacity_______________________________________________________________*/
	results << "s1's status: " << std::endl
			<< "Emtpy: " << s1.empty()
			<< "Size: " << s1.size();
	results << std::endl << std::endl;


	results << "4. Modifiers________________________________________________\n";
/*	4. Modifiers______________________________________________________________*/
	s1.clear();
	print_set_status("s1 clear()", s1, results);

	s1.swap(s2);
	print_set_status("s1 swap()", s1, results);
	print_set_status("s2 swap()", s2, results);
	print_set_content("s1 content:", s1, results);

	s2.insert(s1.begin(), s1.end());
	print_set_status("s2 insert:", s2, results);
	print_set_content("s2 insert:", s2, results);

	s2.erase(3);
	print_set_content("s2 erase(3):", s2, results);

	s2.erase(s2.begin(), s2.end());
	print_set_status("s2 erase(range):", s2, results);
	print_set_content("s2 erase(range):", s2, results);

	int val = 1;
	results << "Failed insertion: " << s1.insert(val).second;
	results << std::endl << std::endl;


	results << "5. Operations_______________________________________________\n";
/*	5. Operations_____________________________________________________________*/
	val = 100;

	s1.insert(val);
	results << "s1.find(100)->second: " << *s1.find(100) << std::endl;
	if (s1.find(1000) == s1.end())
		results << "s1.find(1000) == end()" << std::endl;
	
	results << "s1 lower bound at 2: " << *s1.lower_bound(2) << std::endl
			<< "s1 upper bound at 2: " << *s1.upper_bound(2) << std::endl; 

	results << "6. Non-member_______________________________________________\n";
/*	6. Non-member_____________________________________________________________*/
	s4 = s3;
	results << "s4 == s3:	" << (s4 == s3) << std::endl
			<< "s4 != s1:	" << (s4 != s1) << std::endl
			<< "s1 < s2:	" << (s1 < s2) << std::endl
			<< "s1 <= s2:	" << (s1 <= s2) << std::endl
			<< "s1 > s2:	" << (s1 > s2) << std::endl
			<< "s1 >= s2:	" << (s1 >= s2) << std::endl;
	results << std::endl;

	results.close();
}