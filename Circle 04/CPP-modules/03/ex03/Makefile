CC		= c++

FLAGS	= -Wall -Wextra -Werror -Wshadow -std=c++98

NAME 	= diamondTrap

SRCS	= main.cpp	ClapTrap.cpp	ScavTrap.cpp	FragTrap.cpp	DiamondTrap.cpp

all:	${NAME}

${NAME}: $(SRCS)
	${CC} ${FLAGS} -o ${NAME} ${SRCS}

clean:
	rm -f ${NAME}

fclean: clean

re: fclean all
