# $< "include one prerequisite"
# $@ "include target"
# $^ "include the full list of prerequisites)"

SRCS = get_next_line.c get_next_line_utils.c

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Werror -Wall -Wextra -g3

NAME = gnl.a

$(NAME): $(OBJS)
	@@ar -rsc $@ $^
	@ranlib $(NAME)
	@echo gnl.a created!

all : $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re