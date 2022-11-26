# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clorcery <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/18 11:31:17 by clorcery          #+#    #+#              #
#    Updated: 2022/11/26 16:05:28 by clorcery         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = mandatory/main.c \
	   mandatory/verif_arg.c \
	   mandatory/init.c \
	   mandatory/philosophers.c \
	   mandatory/free.c \
	   mandatory/utils.c 


OBJS = ${SRCS:.c=.o}

NAME = philo

FLAGS = -Werror -Wextra -Wall -g -pthread #-fsanitize=thread

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
