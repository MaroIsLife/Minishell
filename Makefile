LIB = libft/{ft_atoi,ft_bzero,ft_calloc,ft_isalnum,ft_isalpha,ft_isascii,ft_isdigit,ft_isprint,ft_itoa,ft_memccpy,ft_memchr,ft_memcmp,ft_memcpy,ft_memmove,ft_memset,ft_putchar_fd,ft_putendl_fd,ft_putnbr_fd,ft_putstr_fd,ft_split_normal,ft_strchr,ft_strlcat,ft_strlcpy,ft_strlen,ft_strmapi,ft_strncmp,ft_strnstr,ft_strrchr,ft_strtrim,ft_tolower,ft_toupper}.c
GN = gnl/{get_next_line,get_next_line_utils}.c
SRC = commands.c free_filename.c find_argument.c find_command.c find_utils.c find_utils_two.c find_utils_three.c main.c main_two.c main_three.c main_four.c misc.c parse.c parse_two.c parse_three.c sigs.c commands_list.c commands_utils.c environement.c ft_split.c helpers.c test2.c test3.c fork_pipes.c fork_pipes_two.c count_starts.c find_red.c count_argument.c find_arguments_utils.c red_open.c red_open_two.c execute.c execute_utils.c exit.c unset.c export_one.c export_two.c export_three.c sort.c cdpwd.c export_four.c find_command_two.c
CC = gcc

all: minishell

minishell:
	@$(CC) $(SRC) $(GN) $(LIB) -o minishell -lncurses -lreadline -Wall -Wextra -Werror -Werror 
clean :
	rm -rf minishell.o
fclean : clean
		rm -rf ./minishell minishell.dSYM
re : fclean all

.PHONY : all clean fclean re $(NAME)
