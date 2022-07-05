CC		= c++

FLAGS	= -Wall -Wextra -Werror  -std=c++98

NAME 	= containers

SRCS	= main.cpp

all:	${NAME}

${NAME}: $(SRCS)
	${CC} ${FLAGS} -o ${NAME} ${SRCS}

clean:
	rm -f ${NAME}

fclean: clean

re: fclean all