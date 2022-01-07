# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 13:45:50 by athekkep          #+#    #+#              #
#    Updated: 2021/11/01 16:23:51 by athekkep         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

C		= -c

NAME	= libftprintf.a

LFLAGS	= ar rcs

SOURCE	= ft_print_nums.c			ft_print_str.c			ft_printf_utils.c	  \
		  ft_printf.c				libft/ft_isalpha.c		libft/ft_isdigit.c	  \
		  libft/ft_isascii.c		libft/ft_isprint.c		libft/ft_strlen.c     \
		  libft/ft_memset.c			libft/ft_bzero.c		libft/ft_memcpy.c     \
		  libft/ft_memmove.c		libft/ft_strlcpy.c		libft/ft_strlcat.c    \
		  libft/ft_toupper.c		libft/ft_tolower.c		libft/ft_strchr.c     \
		  libft/ft_strrchr.c		libft/ft_strncmp.c		libft/ft_memchr.c     \
		  libft/ft_memcmp.c			libft/ft_strnstr.c		libft/ft_atoi.c       \
		  libft/ft_calloc.c			libft/ft_strdup.c		libft/ft_substr.c     \
		  libft/ft_strjoin.c		libft/ft_strtrim.c		libft/ft_split.c      \
		  libft/ft_itoa.c			libft/ft_strmapi.c		libft/ft_striteri.c   \
		  libft/ft_putchar_fd.c		libft/ft_putstr_fd.c	libft/ft_putendl_fd.c \
		  libft/ft_putnbr_fd.c  	libft/ft_isalnum.c		libft/ft_strjoin_num.c\

OBJS	= ${SOURCE:%.c=%.o}

all:	${NAME}

${NAME}: ${SOURCE} ${OBJS}
	${CC} ${CFLAGS} ${C} ${SOURCE}
	${LFLAGS} ${NAME} ${OBJS}

bonus: all

clean:
	rm -f *.o ./libft/*.o

fclean: clean
	rm -f ${NAME}

re: fclean all
