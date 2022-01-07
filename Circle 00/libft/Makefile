# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 13:45:50 by athekkep          #+#    #+#              #
#    Updated: 2021/10/10 11:18:16 by athekkep         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

C		= -c

NAME	= libft.a

LFLAGS	= ar rcs

SOURCE	= ft_isalpha.c		ft_isdigit.c		ft_isalnum.c	\
		  ft_isascii.c		ft_isprint.c		ft_strlen.c     \
		  ft_memset.c		ft_bzero.c			ft_memcpy.c     \
		  ft_memmove.c		ft_strlcpy.c		ft_strlcat.c    \
		  ft_toupper.c		ft_tolower.c		ft_strchr.c     \
		  ft_strrchr.c		ft_strncmp.c		ft_memchr.c     \
		  ft_memcmp.c		ft_strnstr.c		ft_atoi.c       \
		  ft_calloc.c		ft_strdup.c			ft_substr.c     \
		  ft_strjoin.c		ft_strtrim.c		ft_split.c      \
		  ft_itoa.c			ft_strmapi.c		ft_striteri.c   \
		  ft_putchar_fd.c	ft_putstr_fd.c		ft_putendl_fd.c \
		  ft_putnbr_fd.c  \

BSOURCE	= ft_lstnew.c 		ft_lstadd_front.c	ft_lstsize.c	\
		  ft_lstlast.c		ft_lstadd_back.c	ft_lstdelone.c	\
		  ft_lstclear.c		ft_lstiter.c		ft_lstmap.c		\

OBJS	= ${SOURCE:%.c=%.o}

BOBJS	= ${BSOURCE:%.c=%.o}

all:	${NAME}

${NAME}: ${SOURCE} ${OBJS}
	${CC} ${CFLAGS} ${C} ${SOURCE}
	${LFLAGS} ${NAME} ${OBJS}

bonus: ${NAME} ${BOBJS} ${BSOURCE}
	${CC} ${CFLAGS} ${C} ${BSOURCE}
	${LFLAGS} ${NAME} ${BOBJS}

clean:
	rm -f *.o

fclean: clean
	rm -f ${NAME}

re: fclean all
