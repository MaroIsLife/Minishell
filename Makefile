NAME = cub3D

LIB = Lib/{ft_atoi,ft_bzero,ft_calloc,ft_isalnum,ft_isalpha,ft_isdigit,ft_memcmp,ft_putstr,ft_split,ft_strdub_strjoin,ft_strlen,ft_strtrim}.c
SRC = srcs/{cub3d_raycasting,cub3d_tools,cub3d_tools_2,ft_draw,ft_file_handling,ft_file_handling_2,ft_filecheck,ft_filecheck_2,ft_game,ft_intersections,ft_mlx_loops,ft_screenshot,get_next_line}.c
CC = gcc  -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit  -Wall -Wextra -Werror  libmlx.dylib -fsanitize=address -g
REG = srcs/{cub3d_sprite,ft_3drendring}.c
BONUS = bonus/{cub3d_sprite_bonus,ft_3drendring_bonus}.c
MAP = maps/map3.cub
all : $(NAME)

$(NAME):
	
	
clean :
	

fclean : clean


re : fclean all

run :
	


	
bonus : 
	

.PHONY : all clean fclean re $(NAME)