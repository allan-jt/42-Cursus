# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 13:45:50 by athekkep          #+#    #+#              #
#    Updated: 2021/11/18 13:35:59 by athekkep         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

O		= -o

NAME	= push_swap

CNAME	= checker

SSOURCE = ft_pushswap.c		ft_solveralt.c	\

CSOURCE = ft_checker.c

SOURCE	= libft/ft_isascii.c		libft/ft_isprint.c		libft/ft_strlen.c     \
		  libft/ft_memset.c			libft/ft_bzero.c		libft/ft_memcpy.c     \
		  libft/ft_memmove.c		libft/ft_strlcpy.c		libft/ft_strlcat.c    \
		  libft/ft_toupper.c		libft/ft_tolower.c		libft/ft_strchr.c     \
		  libft/ft_strrchr.c		libft/ft_strncmp.c		libft/ft_memchr.c     \
		  libft/ft_memcmp.c			libft/ft_isdigit.c		libft/ft_atoi.c       \
		  libft/ft_calloc.c			libft/ft_strdup.c		libft/ft_substr.c     \
		  libft/ft_strjoin.c		libft/ft_strtrim.c		libft/ft_split.c      \
		  libft/ft_itoa.c			libft/ft_striteri.c   	libft/ft_isalnum.c	  \
		  libft/ft_putchar_fd.c		libft/ft_putstr_fd.c	libft/ft_putendl_fd.c \
		  libft/ft_putnbr_fd.c		libft/ft_isalpha.c	  	libft/ft_lstadd_back.c\
		  libft/ft_lstadd_front.c	libft/ft_lstiter.c		libft/ft_lstlast.c	  \
		  libft/ft_lstsize.c		ft_errorcheck.c 		ft_psutils.c 		  \
		  libft/ft_lstnew.c	  		ft_moves.c	\

all:	
	${CC} ${CFLAGS} ${O} ${NAME} ${SSOURCE} ${SOURCE}
	${CC} ${CFLAGS} ${O} ${CNAME} ${CSOURCE} ${SOURCE}

bonus: all

clean:
	rm ${NAME} ${CNAME}

fclean: clean

re: fclean all
