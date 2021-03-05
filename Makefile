NAME = minishell

LIB = libft/* gnl/*.c
SRC = *.c 
CC = gcc *.c libft/* gnl/*.c

all : $(NAME)

$(NAME):
	$(CC)  -g -fsanitize=address
	
clean :
	rm -fr a.out a.out.dSYM
fclean : clean

re : fclean all

.PHONY : all clean fclean re $(NAME)9  