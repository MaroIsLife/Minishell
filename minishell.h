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
# include <termios.h>
// # include <termcap.h>
# include <term.h>
# include <sys/types.h>
# include <sys/wait.h>

# define KEY_UP 183
# define KEY_DOWN 184
# define KEY_LEFT  186
# define KEY_RIGHT 185
# define ENTER 10
# define KEY_REMOVE 127
# define KEY_TAB 9
# define CTRL_D 4

typedef struct s_filename {
	char				*filename;
	char				c;
	char				r;
	int					fd_r_c;
    struct s_filename	*next;
}	t_filename;

typedef struct s_stack
{
	char            *data;
	struct s_stack	*prev;
	struct s_stack	*next;
}                t_stack;

typedef struct s_pipe {
	char			*cmd;
	char			**arg;
	int				find_red;
	t_filename		*pipef;
    struct s_pipe	*next;
}	t_pipe;

typedef struct	s_source
{
	int		cmdlen; // Contains input's length without counting \n
	int		offset;
	int		dquotes;
	int		squotes;
	int		aslash;
	int		lastenv;
	int 	dollarused;
	char 	**redsplit;
	int		foundpipe; // Found Pipe
	int		founderror; // Found Error
	int		foundred; // Found Redirection
	char	*user; // Contains User name
	int		c;
	int		nred; // N Redireciton
	int		npipe; // N pipe
	char	*pwd;
	int		forkid; // fork ID to know if we're in Parent or Child process
	char 	**export; // Should be Malloced !!!!!
	char	**our_envp;// Sould be malloced
	char 	*re;
	int		re_b;
	char	*ra;
	int		tmp; // Temp Variable to use on anything to avoid norminette
	char	*ctmp;
	char	*ctmp2;
	int		tmp2;
	int		stop;
	int		ra_b;
	int		lastexp;
	int 	count;
	int 	allocate;
	int		ispipered;
	char 	**filenames;
	// int		return_value;
	int		fd_r_c;
	t_filename	*p;
	t_pipe		*ptemp;
	int			p_temp_i;
}				t_source;


typedef struct s_termc {
	int				edit;
	int				help;
}	t_termc;


typedef struct s_node {
    char			*cmd;
	char			**arg;
	int				number;
	char			*filename;
	t_pipe			*pipe;
	t_filename		*first_filename;
    struct s_node	*next;
}   t_node;

typedef struct s_ft {
	int			b;
	char		*tmp;
	int			j;
	char		*rev;
}		t_ft;

typedef struct s_global {
	int		fsignal;
	int		ffork;
	int		id;
	int		return_value;
	char 	*ret;

}		t_global;

t_global g_global;

//Parsing
void	init_parse(t_source *src, t_node *head, char **envp, char **pipe);
char	*find_command(char *s, t_node *head, t_source *src, char **envp);
int		get_env_value_cmd(char *s, char **envp, t_source *src, int i);
int		find_file_name(int **i, char *s, t_source *src, t_node *head);
int		arg_if_space(char *s, int ***i, t_source *src);
char	*find_argument(char *s, t_node *head, t_source *src, char **envp);
int		count_argument(char *s, int offset, t_source *src);
void	find_for_split(char *cmd, t_source *src);
int 	finding_quotes(char *s, int i, t_source *src);
int 	finding_quotes2(char *s, int i, t_source *src);
int		finding_aslash(char *s, int i, t_source *src);
int		finding_aslash2(char *s, int i, t_source *src);
int 	finding_quotes_cmd(char *s, int i, t_source *src);
int		get_env_value_cmd(char *s, char **envp, t_source *src, int i);
int		get_env_value_arg(char *s, char **envp, t_source *src, int i);
int		find_equal_length(char **envp,int c, int b);

char	**ft_split_normal(char *s, char c);
char	**my_ft_split(char *s, char c, t_source *src);
void	print_prompt1();
void	print_prompt2();
char	*read_line();
void	ms_loop(t_source *src, char **envp);
// Built in functions
int		ft_exit(char **args, t_source *src);
void	command_list(char *cmd, char **args, t_source *src);
void	ft_echo(char **args);
//export
int		ft_strlen_eq(char *src);
void	print_env(t_source *src);
void	ft_export(char **args, t_source *src);
char	*search_env(t_node *head, t_source *src, char **envp, int offset);
void 	ft_sort(t_source *src);
char	**our_realloc(char **s, int count);
int 	check_exsyn(char *src);
int	ft_alloc_count(char **envp, char **args);
void	ft_expn_add_else(char *add, t_source *src, char **args);
int	arg_counter(char **src);
void	replace_env(char **envp, t_source *src, char *value);
void	ft_set_enxp(char **args, t_source *src, char **envp);
void	ft_expn_chng(char *add, t_source *src, char **envp, char **args);
int	found_eq(char *src);
void	em_export(t_source *src);
void 	ft_expn_add(char *add, t_source *src, char **our_envp, char **args);
void	ft_expn_add_two(char **tmp1, char **tmp2, int option, int i);
//end export
int		ft_unset(char **args,t_source *src);
void	ft_cd(char **args,t_source *src, char *home);
void	change_pwd_env(t_source *src);
void 	change_pwd_export(t_source *src);
void	ft_pwd (void);
int		ft_isdollar(int c);
char	*where_home(t_source *src);
void	red_open(t_node *head, t_source *src);
void	red_open_pipe(t_filename *tmp);
int 	fork_pips(int npipe, t_node *head, t_source *src);
//Execute
int	ft_execute(char *cmd, char **args, t_source *src, char **envp);
char	*get_correct_path(char **s, char **varg);
char	**get_env_path(char **envp, t_source *src);
char	**ft_valide_args(char *cmd, char **args, int count);
int		calc_args(char **args);
int		print_cmd_error(char *cmd, int option, int message);

//Signals
void	ft_signal();
void	handler(int c);
void	handler2(int c);


//Utils
char	*get_x_env(char **envp, t_source *src, char *envv_name);
void	set_x_env(char **envp, t_source *src, char *envv_name, char *value);
int 	init_question_arg(t_source *src, int ret);
int 	init_question_cmd(t_source *src, int ret);


void	lstadd_dlist(t_stack **alst, t_stack *new);
void	next_node(t_stack **list);
void	prev_node(t_stack **list);
t_stack	*lstnewc(void *data);

///
int is_equal(char *s1, char *s2);

char *term_loop(t_stack **head, t_stack **tmp, t_termc *termc);
char    *ft_strjoinchar(char *s, char c);
int 	ft_search(char **src, char *value);


t_filename		*new_file(char *s, t_source *src);
void init_filee(t_source *src);


int		count_start(char *s, t_source *src, int start, int *i);
int		count_start_two(char *s, t_source *src, int *start, int **i);
void freeList(t_node* head);


#endif