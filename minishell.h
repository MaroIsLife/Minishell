#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <errno.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"

typedef struct	s_source
{
	int		cmdlen;
	int		isPipe;
	int		offset;


}				t_source;

typedef struct s_pipe {
	char *cmd;
	
}	t_pipe;


typedef struct s_arg {
	char			*arg;
	t_pipe			pipe;
    struct s_node	*next;
}   t_arg;

typedef struct s_node {
    char			*cmd;
	int				foundPipe;
	int				number;
	t_arg			arg;
    struct s_node	*next;
}   t_node;

typedef struct	s_find
{
	int	foundPipe;
	int	nPipe;
	int	foundSemiColons;
	int	nSemiColons;
	int	foundDQuotes;
	int	nDQuotes;
	int	foundSQuotes;
	int	nSQuotes;
}				t_find;

t_source	g_source;
t_find		g_find;
t_node		*g_head;
t_node		*g_first;
int			g_dQuotes;
int			g_sQuotes;


char	*find_command(char *s);
char	*find_argument(char *s);
void	find_for_split(char *cmd);
int 	finding_quotes(char *s, int i);
void	clear();
void	print_prompt1();
void	print_prompt2();
char	*read_line();
void	ms_loop();

#endif