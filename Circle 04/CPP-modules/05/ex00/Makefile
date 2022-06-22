CC		= c++

FLAGS	= -Wall -Wextra -Werror  -std=c++98

NAME 	= Bureaucrat

SRCS	= main.cpp Bureaucrat.cpp

all:	${NAME}

${NAME}: $(SRCS)
	${CC} ${FLAGS} -o ${NAME} ${SRCS}

clean:
	rm -f ${NAME}

fclean: clean

re: fclean all
