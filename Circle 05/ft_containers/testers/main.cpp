/* ************************************************************************** */
/*																			  */
/*   Project:	ft_containers                             :::      ::::::::   */
/*   File:		main.cpp	                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 by athekkep 		           #+#    #+#             */
/*   Updated: 2023/01/23 by athekkep                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

int main() {
	struct timeval	currentTime;
	double			start, end;
	
	std::cout << TYPE << " vector test" << std::endl;
	gettimeofday(&currentTime, NULL);
	start = (currentTime.tv_usec / 1000.0) + (currentTime.tv_sec * 1000);
	run_vec_test();
	gettimeofday(&currentTime, NULL);
	end = (currentTime.tv_usec / 1000.0) + (currentTime.tv_sec * 1000);
	std::cout << "Total time: " << (end - start) << "ms\n";

	std::cout << std::endl << TYPE << " stack test" << std::endl;
	gettimeofday(&currentTime, NULL);
	start = (currentTime.tv_usec / 1000.0) + (currentTime.tv_sec * 1000);
	run_stack_test();
	gettimeofday(&currentTime, NULL);
	end = (currentTime.tv_usec / 1000.0) + (currentTime.tv_sec * 1000);
	std::cout << "Total time: " << (end - start) << "ms\n";

	std::cout << std::endl << TYPE << " map test" << std::endl;
	gettimeofday(&currentTime, NULL);
	start = (currentTime.tv_usec / 1000.0) + (currentTime.tv_sec * 1000);
	run_map_test();
	gettimeofday(&currentTime, NULL);
	end = (currentTime.tv_usec / 1000.0) + (currentTime.tv_sec * 1000);
	std::cout << "Total time: " << (end - start) << "ms\n";

	std::cout << std::endl << TYPE << " set test" << std::endl;
	gettimeofday(&currentTime, NULL);
	start = (currentTime.tv_usec / 1000.0) + (currentTime.tv_sec * 1000);
	run_set_test();
	gettimeofday(&currentTime, NULL);
	end = (currentTime.tv_usec / 1000.0) + (currentTime.tv_sec * 1000);
	std::cout << "Total time: " << (end - start) << "ms\n";

	return 0;
}