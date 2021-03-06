NAME = minishell

LIB = libft/{ft_atoi,ft_bzero,ft_calloc,ft_isalnum,ft_isalpha,ft_isascii,ft_isdigit,ft_isprint,ft_itoa,ft_memccpy,ft_memchr,ft_memcmp,ft_memcpy,ft_memmove,ft_memset,ft_putchar_fd,ft_putendl_fd,ft_putnbr_fd,ft_putstr_fd,ft_split,ft_strchr,ft_strlcat,ft_strlcpy,ft_strlen,ft_strmapi,ft_strncmp,ft_strnstr,ft_strrchr,ft_strtrim,ft_tolower,ft_toupper}.c


GN = gnl/{get_next_line,get_next_line_utils}.c
SRC = commands.c find_argument.c find_command.c find_utils.c main.c misc.c parse.c read.c test.c
CC = gcc

all : $(NAME)

$(NAME):
	@$(CC) $(SRC) $(GN) $(LIB) -g -fsanitize=address && ./a.out   
	
clean :
	rm -fr a.out a.out.dSYM
fclean : clean

re : fclean all

.PHONY : all clean fclean re $(NAME)9  