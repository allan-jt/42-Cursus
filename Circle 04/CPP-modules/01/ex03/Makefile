CC		= c++

FLAGS	= -Wall -Wextra -Werror  -std=c++98

NAME 	= fight

SRCS	= main.cpp	Weapon.cpp	HumanA.cpp	HumanB.cpp

all:	${NAME}

${NAME}: $(SRCS)
	${CC} ${FLAGS} -o ${NAME} ${SRCS}

clean:
	rm -f ${NAME}

fclean: clean

re: fclean all
