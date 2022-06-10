CC		= c++

FLAGS	= -Wall -Wextra -Werror  -std=c++98

NAME 	= animalMain

SRCS	= main.cpp	Animal.cpp	Dog.cpp	Cat.cpp	\
		  WrongAnimal.cpp	WrongCat.cpp		\

all:	${NAME}

${NAME}: $(SRCS)
	${CC} ${FLAGS} -o ${NAME} ${SRCS}

clean:
	rm -f ${NAME}

fclean: clean

re: fclean all
