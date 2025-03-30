CFLAGS = -Wall -Wextra -Werror -I./include
CC = cc

NAME = client
SOURCES = mandatory/client.c \
		  mandatory/convertStringToPID.c \
		  mandatory/ft_putchar_fd.c \
		  mandatory/ft_putstr_fd.c \
		  mandatory/ft_strlen.c \
		  mandatory/write_character_to_fd.c \
		  mandatory/ft_upload.c
OBJECTS = ${SOURCES:.c=.o}

REMOVE = rm -f

%.o: %.c include/minitalk.h
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJECTS}
	${CC} -o ${NAME} ${OBJECTS}

clean:
	${REMOVE} ${OBJECTS}

fclean: clean
	${REMOVE} ${NAME}

norm:
	norminette

re: fclean all

.PHONY: all clean fclean norm re
