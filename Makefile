NAME=	proc
SRC=	proc.c		\
	prompt.c	\
	cmd.c		\
	key_generator.c	\
	debug.c		\
	main.c
OBJ=	$(SRC:.c=.o)
CC=	gcc
CFLAGS=	-W -Wall
LIB=	-lcrypto
RM=	@rm -fv

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(NAME)

re: clean fclean $(NAME)

