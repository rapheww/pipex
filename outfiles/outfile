NAME = pipex

SRC = pipex_bonus.c \
	libft/ft_putstr_fd.c \
	libft/ft_split.c \
	libft/ft_substr.c \

GNL = gnl/get_next_line.c \

LIBFT_DIR = libft
LIBFT_LIB = ${LIBFT_DIR}/libft.a

OBJ = $(SRC:.c=.o)

CC = cc -Wall -Werror -Wextra

all: ${LIBFT_LIB} ${NAME}

${LIBFT_LIB}:
	make -C ${LIBFT_DIR}

${NAME}: ${OBJ}
	${CC} ${OBJ} ${GNL} ${LIBFT_LIB} -o ${NAME}

clean:
	rm -rf ${OBJ}
	make clean -C ${LIBFT_DIR}

fclean: clean
	rm -rf ${NAME}
	make fclean -C ${LIBFT_DIR}

re: fclean all

.PHONY: all clean fclean re