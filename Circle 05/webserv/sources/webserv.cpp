/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:51:04                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../includes/server/ServerManager.hpp"


void	printStatusMessage(STRING message, STRING color) {
	int	msgLength = message.length();
	int	width = (MESSAGE_LENGTH - msgLength) / 2;

	std::cout << color << std::endl << std::string(width, '-') << message
		<< std::string(width + (msgLength % 2), '-') << RESET << std::endl;
}

int main(int argc, char **argv) {
	
	try {
		signal(SIGINT, handleSignals);
		signal(SIGPIPE, SIG_IGN);
		int	validNumOfArgs = 2;

		if (argc > validNumOfArgs)
			throw std::runtime_error("Error: invalid number of args");

		printStatusMessage(" Setting up servers ", YELLOW);
		Config file(argc < validNumOfArgs ? DEFAULT_CONFIG : argv[1]);
		ServerManager hostToast(file);
		hostToast.setUpAllServers();

		printStatusMessage(" Running servers ", GREEN);
		hostToast.runAllServers();
	} catch (std::exception &e){
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	printStatusMessage(" Closed Successfully ", YELLOW);
	return EXIT_SUCCESS;
}
