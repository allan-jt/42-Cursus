CC		= cc

FLAGS	= -Wall -Werror -Wextra -I ./includes/ -I ./source/libft/

O		= -o

NAME	= minishell

SOURCE 	= $(addprefix	./source/,	minishell.c)	\

PSOURCE = $(addprefix	./source/parser/,	parser.c	sub_parse.c	parse_cmd.c)		\
			$(addprefix	./source/parser/,	lst_functions.c	parse_util.c	quotes.c)	\
			$(addprefix	./source/parser/,	dollar.c	parser_split.c	signal.c	parser_util2.c)		\

ESOURCE = $(addprefix	./source/execution/,	execution.c		exec_cd.c		exec_echo.c)	\
			$(addprefix	./source/execution/,	exec_env.c		exec_exit.c		exec_export.c)	\
			$(addprefix	./source/execution/,	exec_pwd.c		exec_unset.c	exec_utils_1.c)	\
			$(addprefix	./source/execution/,	redirections.c	exec_utils_2.c	wildcards.c)	\

LSOURCE	= libft.a

OBJ		= ${SOURCE:%.c=%.o}

POBJ	= ${PSOURCE:%.c=%.o}

EOBJ	= ${ESOURCE:%.c=%.o}

%.o: %.c
	${CC} $(FLAGS) -I${shell brew --prefix readline}/include -c $< -o $@

$(NAME): $(OBJ) $(POBJ) $(EOBJ)
	cd ./source/libft && make
	cd ../../
	$(CC) $(FLAGS) $(OBJ) $(POBJ) $(EOBJ) -L ./source/libft -lft -lreadline -L $(shell brew --prefix readline)/lib -o $(NAME)
	clear

all: $(NAME)

bonus: all

clean:
	rm -f *.o ./source/*.o ./source/execution/*.o ./source/parser/*.o
	cd ./source/libft && make clean
	cd ../../

fclean: clean
	rm -f $(NAME)
	cd ./source/libft && make fclean
	cd ../../

re: fclean all
