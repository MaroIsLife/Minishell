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
	char			*cmd;
	char			**arg;
    struct s_node	*next;
	
}	t_pipe;

typedef struct s_node {
    char			*cmd;
	char			**arg;
	int				foundPipe;
	int				number;
	t_pipe			*pipe;
    struct s_node	*next;
}   t_node;

typedef struct	s_find
{
	int	foundPipe;
	int	nPipe;
	int	foundSemiColons;
	int	nSemiColons;
	int	founddquotes;
	int	ndquotes;
	int	foundsquotes;
	int	nsquotes;
	int	founderror;
}				t_find;

t_source	g_source;
t_find		g_find;
t_node		*g_head;
t_node		*g_first;
int			g_dquotes;
int			g_squotes;
int			g_aSlash;


char	*find_command(char *s, int offset);
char	*find_argument(char *s, int offset);
void	find_for_split(char *cmd);
int 	finding_quotes(char *s, int i);
int 	finding_quotes_cmd(char *s, int i);
void	finding_aslash(char *s, int i);
void	clear();
void	print_prompt1();
void	print_prompt2();
char	*read_line();
void	ms_loop();

#endif