# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 13:45:50 by athekkep          #+#    #+#              #
#    Updated: 2021/11/18 14:25:04 by athekkep         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

O		= -o

NAME	= philo_bonus

SOURCE = main_bonus.c	action_bonus.c	utils_bonus.c	error_bonus.c\

all:	
	${CC} ${CFLAGS} -pthread ${O} ${NAME} ${SOURCE}

bonus: all

clean:
	rm -f ${NAME}

fclean: clean

re: fclean all