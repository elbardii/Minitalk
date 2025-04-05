CFLAGS = -Wall -Wextra -Werror -I./include
CC = cc

# Client
MANDATORY_EXEC_CLIENT = client
MANDATORY_CLIENT_SOURCES = mandatory/client.c \
                           mandatory/convertStringToPID.c \
                           mandatory/ft_putchar_fd.c \
                           mandatory/ft_putstr_fd.c \
                           mandatory/ft_strlen.c \
                           mandatory/write_pid_to_fd.c \
                           mandatory/ft_upload.c
MANDATORY_CLIENT_OBJECTS = ${MANDATORY_CLIENT_SOURCES:.c=.o}

# Server
MANDATORY_EXEC_SERVER = server
MANDATORY_SERVER_SOURCES = mandatory/server.c \
                           mandatory/write_pid_to_fd.c \
                           mandatory/ft_putchar_fd.c \
                           mandatory/ft_putstr_fd.c \
                           mandatory/ft_reset_client.c \
                           mandatory/show_client_message.c
MANDATORY_SERVER_OBJECTS = ${MANDATORY_SERVER_SOURCES:.c=.o}

REMOVE = rm -f

%.o: %.c include/minitalk.h
	${CC} ${CFLAGS} -c $< -o $@

all: ${MANDATORY_EXEC_CLIENT} ${MANDATORY_EXEC_SERVER}

${MANDATORY_EXEC_CLIENT}: ${MANDATORY_CLIENT_OBJECTS}
	${CC} -o ${MANDATORY_EXEC_CLIENT} ${MANDATORY_CLIENT_OBJECTS}

${MANDATORY_EXEC_SERVER}: ${MANDATORY_SERVER_OBJECTS}
	${CC} -o ${MANDATORY_EXEC_SERVER} ${MANDATORY_SERVER_OBJECTS}

clean:
	${REMOVE} ${MANDATORY_CLIENT_OBJECTS} ${MANDATORY_SERVER_OBJECTS}

fclean: clean
	${REMOVE} ${MANDATORY_EXEC_CLIENT} ${MANDATORY_EXEC_SERVER}

norm:
	norminette

re: fclean all

.PHONY: all clean fclean norm re
