SRCS =	lib/lib64.c \
		lib/print.c \
		error/error.c \
		memory/get_binary.c \
		main.c

OBJS = ${SRCS:.c=.o}

HEADERS =	lib/lib.h \
			error/error.h \
			memory/memory.h \
			header.h

NAME = a.out
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
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
