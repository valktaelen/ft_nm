SRCS =	lib/lib64.c \
		lib/lib32.c \
		lib/print.c \
		lib/print32.c \
		lib/print64.c \
		lib/debug32.c \
		lib/debug64.c \
		error/error.c \
		error/utils.c \
		memory/file.c \
		memory/swap_bits.c \
		main.c

OBJS = ${SRCS:.c=.o}

HEADERS =	lib/lib.h \
			error/error.h \
			memory/memory.h \
			header.h

NAME = a.out
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3# -fsanitize=address
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
