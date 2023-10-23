# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/23 06:52:52 by aartiges          #+#    #+#              #
#    Updated: 2023/10/23 06:52:57 by aartiges         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c 				\
		lib/32/algo.c		\
		lib/32/header.c		\
		lib/32/list.c		\
		lib/32/print.c		\
		lib/32/section.c	\
		lib/32/symbol.c		\
		lib/64/algo.c		\
		lib/64/header.c		\
		lib/64/list.c		\
		lib/64/print.c		\
		lib/64/section.c	\
		lib/64/symbol.c		\
		lib/lib.c			\
		utils/file.c		\
		utils/memory.c		\
		utils/swap_bits.c	\
		utils/tools.c		\


OBJS = ${SRCS:.c=.o}

HEADERS =	header.h		\
			utils/struct.h	\
			utils/utils.h	\
			lib/lib.h	\


NAME = a.out
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
RM = rm -rf

%.o : %.c $(HEADERS)
	@${CC} ${CFLAGS} -c $< -o $@

all: 		${NAME}

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
			@${RM} ${OBJS}

fclean:
			@${RM} ${OBJS} ${NAME}

re: fclean all
