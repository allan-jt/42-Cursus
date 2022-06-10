CC		= c++

FLAGS	= -Wall -Wextra -Werror  -std=c++98

NAME 	= scavTrap

SRCS	= main.cpp	ClapTrap.cpp	ScavTrap.cpp

all:	${NAME}

${NAME}: $(SRCS)
	${CC} ${FLAGS} -o ${NAME} ${SRCS}

clean:
	rm -f ${NAME}

fclean: clean

re: fclean all
