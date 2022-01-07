CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

O		= -o

NAME	= so_long

BNAME	= so_long_bonus

SOURCE	= so_long.c	sl_utils1.c sl_utils2.c	sl_init.c	sl_map.c	sl_utils3.c\

BSOURCE	= so_long_bonus.c	sl_utils3.c sl_utils1.c	sl_utils2.c		sl_init.c	sl_map.c	sl_utils_bonus.c	\

OBJ		= ${SOURCE:%.c=%.o}

BOBJ	= ${BSOURCE:%.c=%.o}

%.o: %.c
	${CC} -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME): $(OBJ)
	cd ./libft && make
	cd ..
	cd ./mlx && make
	cd ..
	$(CC) $(CFLAGS) $(OBJ) -Lmlx -lmlx -Llibft -lft -framework OpenGL -framework AppKit -o $(NAME)	

$(BNAME): $(BOBJ) $(NAME)
	$(CC) $(CFLAGS) $(BOBJ) -Lmlx -lmlx -Llibft -lft -framework OpenGL -framework AppKit -o $(BNAME)	

all: $(NAME)

bonus: $(BNAME)

clean:
	rm -f *.o
	cd ./libft && make fclean
	cd ..
	cd ./mlx && make clean
	cd ..

fclean: clean
	rm -f $(NAME)
	rm -f $(BNAME)

re: fclean all
