CFLAGS = -Wall -Wextra -Werror -I./include
CC = cc

CLIENT = client
CLIENT_SOURCES = mandatory/client.c \
		mandatory/convertStringToPID.c \
		mandatory/ft_putchar_fd.c \
		mandatory/ft_putstr_fd.c \
		mandatory/ft_strlen.c \
		mandatory/write_character_to_fd.c \
		mandatory/ft_upload.c
CLIENT_OBJECTS = ${CLIENT_SOURCES:.c=.o}

SERVER = server
SERVER_SOURCES = mandatory/server.c \
		mandatory/ft_putpid_fd.c \
		mandatory/ft_putchar_fd.c \
		mandatory/ft_putstr_fd.c \
		mandatory/ft_reset_client.c \
		mandatory/ft_put_client_message.c
SERVER_OBJECTS = ${SERVER_SOURCES:.c=.o}

REMOVE = rm -f

%.o: %.c include/minitalk.h
	${CC} ${CFLAGS} -c $< -o $@

all: ${CLIENT} ${SERVER}

${CLIENT}: ${CLIENT_OBJECTS}
	${CC} -o ${CLIENT} ${CLIENT_OBJECTS}

${SERVER}: ${SERVER_OBJECTS}
	${CC} -o ${SERVER} ${SERVER_OBJECTS}

clean:
	${REMOVE} ${CLIENT_OBJECTS} ${SERVER_OBJECTS}

fclean: clean
	${REMOVE} ${CLIENT} ${SERVER}

norm:
	norminette

re: fclean all

.PHONY: all clean fclean norm re
