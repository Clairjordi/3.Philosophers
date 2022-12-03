# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clorcery <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/18 11:31:17 by clorcery          #+#    #+#              #
#    Updated: 2022/12/03 17:04:14 by clorcery         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = mandatory/main.c \
	   mandatory/verif_arg.c \
	   mandatory/init.c \
	   mandatory/philosophers.c \
	   mandatory/mutex.c \
	   mandatory/eat.c \
	   mandatory/die.c \
	   mandatory/die_util.c \
	   mandatory/time.c \
	   mandatory/display.c \
	   mandatory/utils.c \
	   mandatory/free.c 


OBJS = ${SRCS:.c=.o}

NAME = philo

FLAGS = -O3 -Werror -Wextra -Wall -g -pthread #-fsanitize=thread

all: ${NAME}

.c.o:
	clang ${FLAGS} -c $< -o $@

${NAME}: ${OBJS}
	clang ${FLAGS} ${OBJS} -o  ${NAME}

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
