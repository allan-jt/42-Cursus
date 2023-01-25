/* ************************************************************************** */
/*																			  */
/*   Project:	ft_containers                             :::      ::::::::   */
/*   File:		vec_tester.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 by athekkep 		           #+#    #+#             */
/*   Updated: 2023/01/22 by athekkep                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

template<class T> void print_vec_content(std::string name, T &c,
	std::ostream &results) {
	
	results << name << " Content: ";
	for (typename T::iterator it = c.begin(); it != c.end(); it++)
		results << *it << " ";
	results << std::endl;
}

template<class T> void print_vec_status(std::string name, T &c,
	std::ostream &results) {
	
	results << name << " Status:	" << std::endl;
	results << "Empty:	" << c.empty() << std::endl
			<< "Size:	" << c.size() << std::endl;
	if (c.begin() == c.end()) {
		results << "First element:	None" << std::endl
				<< "Last element:	None" << std::endl;
	} else {
		results << "First element:	" << *(c.begin()) << std::endl
				<< "Last element:	" << *(c.end() - 1) << std::endl;
	}
}

void run_vec_test() {
	std::ofstream	results(VEC_FILE);

	results << "1. Constructors_____________________________________________\n";
/*	1. Constructors, destructors, & assignment operator overload______________*/
	NAMESPACE::vector<int>	v1;
	NAMESPACE::vector<int>	v2(SML_BUF, 1);
	NAMESPACE::vector<int>	v3(MID_BUF, 2);
	NAMESPACE::vector<int>	v4(BIG_BUF, 3);
	NAMESPACE::vector<int>	v5(v2);
	v3 = v2;

	print_vec_status("v1", v1, results);
	print_vec_status("v2", v2, results);
	print_vec_status("v3", v3, results);
	print_vec_status("v4", v4, results);
	print_vec_status("v5", v5, results);
	results << std::endl;


	results << "2. Iterators________________________________________________\n";
/*	2. Iterators______________________________________________________________*/
	NAMESPACE::vector<std::string>	v_it(10, "Hello");
	v_it.insert(v_it.end(), 10, "lol");
	
	results << "Normal iterator: ";
	for(NAMESPACE::vector<std::string>::iterator it = v_it.begin();
		it != v_it.end(); it++) {
		results << *it << " ";
	}
	results << std::endl;

	results << "Reverse iterator: ";
	for(NAMESPACE::vector<std::string>::reverse_iterator it = v_it.rbegin();
		it != v_it.rend(); it++) {
		results << *it << " ";
	}
	results << std::endl << std::endl;


	results << "3. Capcity__________________________________________________\n";
/*	3. Capacity_______________________________________________________________*/
	results	<< "v_it size:		" << v_it.size() << std::endl
			<< "v_it max size:	" << v_it.max_size() << std::endl
			<< "v_it empty:		" << v_it.empty() << std::endl;

	results	<< "v4 size:		" << v4.size() << std::endl
			<< "v4 max size:	" << v4.max_size() << std::endl
			<< "v4 empty:		" << v4.empty() << std::endl;
	results << std::endl;


	results << "4. Modifiers________________________________________________\n";
/*	4. Modifiers______________________________________________________________*/
	results << "Pop and push: \n";
	for (int i = 0; i < 10; i++)
		v1.push_back(i);
	print_vec_content("v1 push()", v1, results);
	print_vec_status("v1 push()", v1, results);
	
	for (int i = 0; i < 5; i++)
		v1.pop_back();
	print_vec_content("v1 pop()", v1, results);
	print_vec_status("v1 pop()", v1, results);
	results << std::endl;

	results << "Resize & clear: \n";
	v4.resize(200);
	v5.clear();
	print_vec_status("v4 resize(200)", v4, results);
	print_vec_status("v5 clear()", v5, results);
	results << std::endl;

	results << "Assign: \n";
	v_it.assign(3, "Hey!");
	v5.assign(v4.begin(), v4.end());
	print_vec_content("v_it assign(3, heya)", v_it, results);
	print_vec_status("v_it assign(3, heya)", v_it, results);
	print_vec_status("v5 assign(v4.b, v4.e)", v5, results);
	results << std::endl;

	results << "Insert: \n";
	v_it.insert(v_it.begin() + 1, 5, "yo");
	v1.insert(v1.begin(), v2.begin(), v2.begin() + 5);
	print_vec_content("v_it insert()", v_it, results);
	print_vec_status("v_it insert()", v_it, results);
	print_vec_content("v1 insert()", v1, results);
	print_vec_status("v1 insert()", v1, results);
	results << std::endl;

	results << "Erase: \n";
	v_it.erase(v_it.end() - 5, v_it.end());
	print_vec_content("v_it erase()", v_it, results);
	print_vec_status("v_it erase()", v_it, results);
	results << std::endl;

	results << "Swap: \n";
	print_vec_status("v3 before", v3, results);
	print_vec_status("v4 before", v4, results);
	v3.swap(v4);
	print_vec_status("v3 after", v3, results);
	print_vec_status("v4 after", v4, results);
	results << std::endl;

	results << std::endl;

	results << "5. Access___________________________________________________\n";
/*	5. Access_________________________________________________________________*/
	v5.clear();
	for (int i = 0; i < 10; i++)
		v5.push_back(i);
	print_vec_content("v5 after push", v5, results);
	results << "[5]:	" << v5[5] << std::endl
			<< "at(5):	" << v5.at(5) << std::endl
			<< "front():	" << v5.front() << std::endl
			<< "back():	" << v5.back() << std::endl
			<< "*data():	" << *(v5.data()) << std::endl;
	results << std::endl;

	results << "6. Non-member_______________________________________________\n";
/*	6. Non-member_____________________________________________________________*/
	v5 = v4;
	results << "v4 == v1:	" << (v4 == v1) << std::endl
			<< "v4 == v5:	" << (v4 == v5) << std::endl
			<< "v4 < v5:	" << (v4 < v5) << std::endl
			<< "v4 <= v5:	" << (v4 <= v5) << std::endl
			<< "v4 > v5:	" << (v4 > v5) << std::endl
			<< "v4 >= v5:	" << (v4 >= v5) << std::endl;
	results << std::endl;

	results.close();
}