CC		= c++

FLAGS	= -Wall -Wextra -Werror -std=c++98

NAME 	= animalMain

SRCS	= main.cpp	AMateria.cpp	Character.cpp	\
			Cure.cpp	Ice.cpp	MateriaSource.cpp	\

all:	${NAME}

${NAME}: $(SRCS)
	${CC} ${FLAGS} -o ${NAME} ${SRCS}

clean:
	rm -f ${NAME}

fclean: clean

re: fclean all
