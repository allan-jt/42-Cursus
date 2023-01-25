/* ************************************************************************** */
/*																			  */
/*   Project:	ft_containers                             :::      ::::::::   */
/*   File:		map_tester.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 by athekkep 		           #+#    #+#             */
/*   Updated: 2023/01/22 by athekkep                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

template<class T> void print_map_content(std::string name, T &c,
	std::ostream &results) {
	
	results << name << " Content: ";
	for (typename T::iterator it = c.begin(); it != c.end(); it++)
		results << it->first << "(" << it->second << ")" << " ";
	results << std::endl;
}

template<class T> void print_map_status(std::string name, T &c,
	std::ostream &results) {
	
	results << name << " Status:	" << std::endl;
	results << "Empty:	" << c.empty() << std::endl
			<< "Size:	" << c.size() << std::endl;
	if (c.begin() == c.end()) {
		results << "First element:	None" << std::endl
				<< "Last element:	None" << std::endl;
	} else {
		results << "First element:	" << c.begin()->first << "("
				<< c.begin()->second << ")" << std::endl
				<< "Last element:	" << (--c.end())->first << "("
				<< (--c.end())->second << ")" << std::endl;
	}
}

void run_map_test() {
	std::ofstream	results(MAP_FILE);
	NAMESPACE::vector<NAMESPACE::pair<int, int> > v1;
	for (int i = 0; i < 10; i++)
		v1.push_back(NAMESPACE::make_pair(i, i * 10));

	results << "1. Constructors_____________________________________________\n";
/*	1. Constructors, destructors, & assignment operator overload______________*/
	NAMESPACE::map<int, int>	m1;
	NAMESPACE::map<int, int>	m2(v1.begin(), v1.end());
	NAMESPACE::map<int, int>	m3(m2);
	NAMESPACE::map<int, int>	m4;
	m4 = m2;

	print_map_status("m1", m1, results);
	print_map_status("m2", m2, results);
	print_map_status("m3", m3, results);
	print_map_status("m4", m4, results);
	results << std::endl << std::endl;


	results << "2. Iterators________________________________________________\n";
/*	2. Iterators______________________________________________________________*/
	for (int i = 0; i < 10; i++)
		m1.insert(NAMESPACE::make_pair(i, i * 100));
	print_map_status("m1 insert()", m1, results);
	
	results << "Normal iterator: ";
	for(NAMESPACE::map<int, int>::iterator it = m1.begin();
		it != m1.end(); it++) {
		results << it->first << " ";
	}
	results << std::endl;

	results << "Reverse iterator: ";
	for(NAMESPACE::map<int, int>::reverse_iterator it = m1.rbegin();
		it != m1.rend(); it++) {
		results << it->first << " ";
	}
	results << std::endl << std::endl;


	results << "3. Capcity__________________________________________________\n";
/*	3. Capacity_______________________________________________________________*/
	results << "m1's status: " << std::endl
			<< "Emtpy: " << m1.empty()
			<< "Size: " << m1.size();
	results << std::endl << std::endl;


	results << "4. Modifiers________________________________________________\n";
/*	4. Modifiers______________________________________________________________*/
	m1.clear();
	print_map_status("m1 clear()", m1, results);

	m1.swap(m2);
	print_map_status("m1 swap()", m1, results);
	print_map_status("m2 swap()", m2, results);
	print_map_content("m1 content:", m1, results);

	m2.insert(m1.begin(), m1.end());
	print_map_status("m2 insert:", m2, results);
	print_map_content("m2 insert:", m2, results);

	m2.erase(3);
	print_map_content("m2 erase(3):", m2, results);

	m2.erase(m2.begin(), m2.end());
	print_map_status("m2 erase(range):", m2, results);
	print_map_content("m2 erase(range):", m2, results);

	NAMESPACE::pair<int, int> val(1, 1);
	results << "Failed insertion: " << m1.insert(val).second;
	results << std::endl << std::endl;


	results << "5. Access___________________________________________________\n";
/*	5. Access_________________________________________________________________*/
	results << "m1[1]: " << m1[1] << std::endl;
	m1[1] = 100;
	results << "m1[1] = 100 -> " << m1.at(1) << std::endl;

	m1[100] = 0;
	results << "m1[100] = 0 (key doesn't exists) -> " << m1.at(100);
	results << std::endl << std::endl;


	results << "6. Operations_______________________________________________\n";
/*	6. Operations_____________________________________________________________*/
	results << "m1.find(100)->second: " << m1.find(100)->second << std::endl;
	if (m1.find(1000) == m1.end())
		results << "m1.find(1000) == end()" << std::endl;
	
	results << "m1 lower bound at 2: " << m1.lower_bound(2)->first << std::endl
			<< "m1 upper bound at 2: " << m1.upper_bound(2)->first << std::endl; 

	results << "7. Non-member_______________________________________________\n";
/*	7. Non-member_____________________________________________________________*/
	m4 = m3;
	results << "m4 == m3:	" << (m4 == m3) << std::endl
			<< "m4 != m1:	" << (m4 != m1) << std::endl
			<< "m1 < m2:	" << (m1 < m2) << std::endl
			<< "m1 <= m2:	" << (m1 <= m2) << std::endl
			<< "m1 > m2:	" << (m1 > m2) << std::endl
			<< "m1 >= m2:	" << (m1 >= m2) << std::endl;
	results << std::endl;

	results.close();
}