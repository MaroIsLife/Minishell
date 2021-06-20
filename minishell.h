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
# include <termcap.h>
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
	char			*data;
	struct s_stack	*prev;
	struct s_stack	*next;
}	t_stack;

typedef struct s_pipe {
	char			*cmd;
	char			**arg;
	int				find_red;
	t_filename		*pipef;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_source
{
	int			cmdlen;
	int			offset;
	int			dquotes;
	int			squotes;
	int			aslash;
	int			lastenv;
	int			dollarused;
	char		**redsplit;
	int			foundpipe;
	int			founderror;
	int			foundred;
	int			c;
	int			nred;
	int			npipe;
	int			forkid;
	char		**export;
	char		**our_envp;
	char		*re;
	int			re_b;
	char		*ra;
	int			tmp;
	char		*ctmp;
	char		*ctmp2;
	int			tmp2;
	int			stop;
	int			ra_b;
	int			lastexp;
	int			count;
	int			allocate;
	int			ispipered;
	char		**filenames;
	int			fd_r_c;
	t_filename	*p;
	t_pipe		*ptemp;
	int			p_temp_i;
	int			fd[2];
}				t_source;

typedef struct s_node {
	char			*cmd;
	char			**arg;
	int				number;
	char			*filename;
	t_pipe			*pipe;
	t_filename		*first_filename;
	struct s_node	*next;
}	t_node;

typedef struct s_var {
	t_node		*head;
	t_node		*first;
	t_stack		*head1;
	t_stack		*tmp;
	char		*cmd;
	char		*ret;
	char		**pipes;
	int			count;
	int			edit;
	int			help;
	int			i;
	int			c;
	int			d;
	t_filename	*here;
	t_filename	*next;
}	t_var;

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
	char	*ret;
	int		fd1;
	int		fd2;

}		t_global;

t_global	g_global;

//Parsing

void		ms_free(t_var *var);
void		ms_free_inside(t_var *var);
char		*ms_get_cmd(t_source *src, t_var *var);
void		ms_init(t_source *src, t_var *var, char **envp);
void		ms_nodes(t_var *var, t_source *src, char **pipes, int c);
void		init_env(t_source *src, char **envp);
void		ms_pipe_one(t_source *src, t_var *var);
void		init_arg_pipe(char **arg, t_pipe *p, int tmp2);
char		*get_x_env(char **envp, char *envv_name);
void		freeList_pipe(t_pipe *head);
void		freeList(t_node *head);
int			num_of_node(t_pipe *tmp);
void		init(t_source *src);
void		sigs(void);
t_filename	*get_last_node(t_filename *tmp);
t_pipe		*get_last_node_p(t_pipe *tmp);
void		init_arg(t_node *head, char **arg, int tmp2);
int			init_parse(t_source *src, t_node *head, char **pipe);
char		*find_command(char *s, t_source *src);
int			find_file_name(int **i, char *s, t_source *src);
int			arg_if_space(char *s, int ***i, t_source *src);
char		*find_argument(char *s, t_source *src);
int			count_argument(char *s, t_source *src);
void		find_for_split(char *cmd, t_source *src);
int			finding_quotes(char *s, int i, t_source *src);
int			finding_quotes2(char *s, int i, t_source *src);
int			finding_aslash(char *s, int i, t_source *src);
int			finding_aslash2(char *s, int i, t_source *src);
int			finding_quotes_cmd(char *s, int i, t_source *src);
int			get_env_value_cmd(char *s, t_source *src, int i);
int			get_env_value_arg(char *s, t_source *src, int i);
int			find_equal_length(char **envp, int c, int b);
char		*get_env_value_cmd_two(char *s, t_source *src, int i);
int			finding_aslash_split(char *s, int i, t_source *src);
int			finding_quotes_split(char *s, int i, t_source *src);
char		**ft_split_normal(char *s, char c);
char		**my_ft_split(char *s, char c, t_source *src);
void		print_prompt1(void);
void		print_prompt2(void);
void		ms_loop(t_source *src, char **envp, t_var *var);
int			ft_exit(char **args);
void		command_list(char *cmd, char **args, t_source *src);
void		ft_echo(char **args);
int			ft_strlen_eq(char *src);
void		print_env(t_source *src);
void		ft_export(char **args, t_source *src);
char		*search_env(t_node *head, t_source *src, char **envp, int offset);
void		ft_sort(t_source *src);
char		**our_realloc(char **s, int count);
int			check_exsyn(char *src);
int			ft_alloc_count(char **envp, char **args);
void		ft_expn_add_else(char *add, t_source *src, char **args);
int			arg_counter(char **src);
void		replace_env(t_source *src, char *value);
void		ft_set_enxp(char **args, t_source *src);
void		ft_expn_chng(char *add, t_source *src);
int			found_eq(char *src);
void		em_export(t_source *src);
void		ft_expn_add(char *add, t_source *src, char **args);
void		ft_expn_add_two(char **tmp1, char **tmp2, int option, int i);
int			ft_unset(char **args, t_source *src);
void		ft_cd(char **args, t_source *src, char *home);
void		change_pwd_env(t_source *src);
void		change_pwd_export(t_source *src);
void		ft_pwd (void);
int			ft_isdollar(int c);
char		*where_home(t_source *src);
void		red_open(t_node *head, t_source *src);
void		red_open_pipe(t_filename *tmp);
void		fork_pips(int npipe, t_node *head, t_source *src);
int			ft_execute(char *cmd, char **args, t_source *src);
char		*get_correct_path(char **s, char **varg);
char		**get_env_path(char **envp);
char		**ft_valide_args(char *cmd, char **args, int count);
int			calc_args(char **args);
int			print_cmd_error(char *cmd, int option, int message, char **varg);
void		ft_signal(void);
void		handler(int c);
void		handler2(int c);
char		*get_x_env(char **envp, char *envv_name);
void		set_x_env(char **envp, t_source *src, char *envv_name, char *value);
int			init_question_arg(t_source *src, int ret);
int			init_question_cmd(t_source *src, int ret);
void		lstadd_dlist(t_stack **alst, t_stack *new);
void		next_node(t_stack **list);
void		prev_node(t_stack **list);
t_stack		*lstnewc(void *data);
int			is_equal(char *s1, char *s2);
char		*term_loop(t_stack **head, t_stack **tmp, t_var *var);
char		*ft_strjoinchar(char *s, char c);
int			get_char(void);
int			ft_search(char **src, char *value);
int			ft_putc(int s);
void		ft_key_remove(t_var *var);
t_filename	*new_file(char *s, t_source *src);
void		ft_key_down(t_stack **tmp, t_var *var);
void		init_filee(t_source *src);
int			count_start(char *s, t_source *src, int start, int *i);
int			count_start_two(char *s, t_source *src, int *start, int **i);
void		freeList(t_node *head);
int			parse_check(t_node *head, t_source *src);
void		ft_free_filenames(t_filename *head);
int			ms_free_two(char *cmd);
#endif