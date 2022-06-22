CC		= c++

FLAGS	= -Wall -Wextra -Werror  -std=c++98

NAME 	= convert

SRCS	= main.cpp	TypeCast.cpp

all:	${NAME}

${NAME}: $(SRCS)
	${CC} ${FLAGS} -o ${NAME} ${SRCS}

clean:
	rm -f ${NAME}

fclean: clean

re: fclean all