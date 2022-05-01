
SRC	=	ft_memset.c\
				ft_bzero.c\
				ft_isalpha.c\
				ft_isdigit.c\
				ft_isalnum.c\
				ft_isascii.c\
				ft_isprint.c\
				ft_memcpy.c\
				ft_memmove.c\
				ft_strlen.c\
				ft_strlcat.c\
				ft_tolower.c\
				ft_toupper.c\
				ft_strchr.c\
				ft_strrchr.c\
				ft_strncmp.c\
				ft_memchr.c\
				ft_memcmp.c\
				ft_strnstr.c\
				ft_atoi.c\
				ft_strlcpy.c\
				ft_strdup.c\
				ft_calloc.c\
				ft_substr.c\
				ft_putchar_fd.c\
				ft_putstr_fd.c\
				ft_putendl_fd.c\
				ft_putnbr_fd.c\
				ft_strjoin.c\
				ft_strtrim.c\
				ft_itoa.c\
				ft_split.c\
				ft_strmapi.c\
				ft_striteri.c	
SRC_BONUS   =	ft_lstnew.c ft_lstadd_front.c \
			ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c\
			ft_lstclear.c ft_lstiter.c ft_lstmap.c
CFLAGS		=	-Wall -Wextra -Werror
NAME = libft.a
OBJ	=	$(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)


all:$(NAME)
	@echo libft created!
$(NAME): $(OBJ)
	@ar -rsc $@ $^

$(OBJ): $(SRC)
	@gcc -c $(CFLAGS) $^ -I.

bonus: $(OBJ_BONUS)
	@ar -rsc $(NAME) $^
	echo Bonus Added to library!
$(OBJ_BONUS): $(SRC_BONUS)
	@gcc -c $(CFLAGS) $(SRC_BONUS) $(SRC) -I.

clean:
	rm -rf $(OBJ) $(OBJ_BONUS)
	
fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY:	bonus all clean fclean re
