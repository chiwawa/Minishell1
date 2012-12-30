NAME	=       mysh	

SRC_DIR =	src/

SRC	=	main.c \
		$(SRC_DIR)getRawInput.c \
		$(SRC_DIR)formatInput.c \
		$(SRC_DIR)envHandler.c  \
		$(SRC_DIR)execution.c

CFLAGS +=	-I./internals -I./inc -ggdb

LDFLAGS +=	-ggdb

OBJ	=	$(SRC:.c=.o)


all: $(NAME)


$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
