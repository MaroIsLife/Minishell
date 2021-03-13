#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
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
	int		dquotes;
	int		squotes;
	int		aslash;
	int		lastenv;
	int		foundpipe;
	int		founderror;
	char	*user;
	int		c;
	int		npipe;
	int		dollar;
	char 	*export[1024];
	char 	*re;
	int		re_b;
	char	*ra;
	int		ra_b;
	int		lastexp;
	int 	count;
}				t_source;

typedef struct s_pipe {
	char			*cmd;
	char			**arg;
    struct s_pipe	*next;
}	t_pipe;

typedef struct s_node {
    char			*cmd;
	char			**arg;
	int				number;
	t_pipe			*pipe;
    struct s_node	*next;
}   t_node;


int g_return;


//Parsing
void	init_parse(t_source *src, t_node *head, char **envp, char **pipe);
char	*find_command(char *s, int offset, t_source *src, char **envp);
char	*find_argument(char *s, int offset, t_source *src, char **envp);
int		count_argument(char *s, int offset, t_source *src);
void	find_for_split(char *cmd, t_source *src);
int 	finding_quotes(char *s, int i, t_source *src);
int 	finding_quotes_cmd(char *s, int i, t_source *src);
int		finding_aslash(char *s, int i, t_source *src);
int		get_env_value_cmd(char *s, char **envp, t_source *src, int i);
int		get_env_value_arg(char *s, char **envp, t_source *src, int i);
int		find_equal_length(char **envp,int c, int b);

// char		**ft_split_normal(char const *s, char c);
char	**ft_split(char *s, char c, t_source *src);
void	clear();
void	print_prompt1();
void	print_prompt2();
char	*read_line();
void	ms_loop(t_source *src, char **envp);


// Built in functions
void	command_list(t_node *head, t_source *src, char **envp);
void	ft_echo(t_node *head, t_source *src);
void	print_env(t_node *head, t_source *src, char **envp);
void	ft_export(t_node *head, t_source *src, char **envp);
char	*search_env(t_node *head, t_source *src, char **envp, int offset);
int		ft_unset(t_node *head, t_source *src, char **envp);
void	ft_cd(t_node *head, char *home, char **envp);
void	change_pwd_env(char **envp);
void	ft_pwd (void);
int		ft_isdollar(int c);
char	*where_home(char **envp);


//Signals
void	ft_signal();
void	handler(int c);
void	handler2(int c);

#endif