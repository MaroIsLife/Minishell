#include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include "minishell.h"

	void freeList(t_node* head)
	{
	t_node* tmp;
		char *c_tmp;
		int i;

	while (head != NULL)
		{
		tmp = head;
		head = head->next;
		free(tmp->cmd);
			i = 0;
		if (tmp->arg)
		{
			while (tmp->arg[i])
				free(tmp->arg[i++]);}
			free(tmp->arg);
		}
		free(tmp);

	}
int num_of_node(t_pipe *tmp)
{
	int i;

	i = 0;
	while (tmp)
	{
		if (tmp->next == NULL)
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (i);
}
void freeList_pipe(t_pipe* head)
{
 	t_pipe* tmp;
	char *c_tmp;
	int i;
	int n = num_of_node(head);

	// printf ("===========%d=========\n", n);
	i = 0;
   while (head != NULL)
    {
		write (2, "how here\n", 9);
	   tmp = head;
       head = head->next;
       free(tmp->cmd);
	   if (tmp->pipef)
	   	free(tmp->pipef);
	
	if (tmp->arg)
	{
		while (tmp->arg[i])
			free(tmp->arg[i++]);}
		free(tmp->arg);
    }

	free(tmp);


}

char	*get_x_env(char **envp, t_source *src, char *envv_name)
{
	int		i;
	int		b;
	int		c;
	char	*s;

	b = 0;
	c = 0;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], envv_name, ft_strlen(envv_name)) == 0
			&& envp[i][ft_strlen(envv_name)] == '=')
			return (ft_strrchr(envp[i], '=') + 1);
		i++;
	}
	return (0);
}

void	init(t_source *src)
{
	src->founderror = 0;
	src->offset = 0;
	src->dquotes = 0;
	src->squotes = 0;
	src->aslash = 0;
	src->offset = 0;
}

void	init_env(t_source *src, char **envp)
{
	int	i;

	i = 0;
	src->lastenv = 0;
	src->lastexp = 0;
	while (envp[i] != NULL)
	{
		src->lastenv++;
		src->lastexp++;
		i++;
	}
	src->our_envp = malloc(sizeof(char *) * (i + 2));
	src->export = malloc(sizeof(char *) * (i + 2));
	src->our_envp[i] = "\0";
	i = 0;
	src->export[i] = ft_strdup("OLDPWD");
	while (envp[i] != NULL)
	{
		src->our_envp[i] = ft_strdup(envp[i]);
		src->export[i + 1] = ft_strdup(envp[i]);
		i++;
	}
	src->our_envp[i + 1] = NULL;
	src->export[i + 1] = NULL;
	src->lastenv++;
	src->lastexp++;
}

void	sigs()
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler2);
	if (g_global.fsignal == 0)
	{
		print_prompt1();
		g_global.fsignal = 1;
	}
	g_global.ret = NULL;
}

char	*ms_get_cmd(t_source *src, t_var *var)
{
	char	*cmd;
	int		b;

	b = 0;
	sigs();
	cmd = term_loop(&var->head1, &var->tmp, var);
	while (cmd[b] == ' ')
		b++;
	if (cmd[b] == '\0')
	{
		print_prompt1();
		free(cmd);
		free(g_global.ret);
		return ("continue");
	}
	g_global.fsignal = 0;
	init(src);
	return (cmd);
}
void	ms_init(t_source *src, t_var *var, char **envp)
{
	init_env(src, envp);
	g_global.return_value = 0;
	var->edit = 0;
	var->help = 0;
	g_global.ret = NULL;
  	tgetent(NULL, getenv("TERM"));
	var->tmp = NULL;
	var->head1 = NULL;
}

void	ms_nodes(t_var *var, t_source *src, char **pipes, int c)
{
	var->head = (t_node *) malloc(sizeof(t_node));
	var->head->next = NULL;
	var->head->pipe = NULL;
	var->head->first_filename = NULL;
	var->first = var->head;
	find_for_split(pipes[c], src);
	src->allocate = 0;
	if (src->foundred == 1)
	{
		var->head->first_filename = (t_filename *)malloc(sizeof(t_filename));
		var->head->first_filename->next = NULL;
		src->p = var->head->first_filename;
	}
	src->dquotes = 0;
	src->squotes = 0;
	src->fd_r_c = 0;
	src->c = c;
	init_parse(src, var->head, src->our_envp, pipes);
	src->offset = 0;
	g_global.return_value = 0;
	if (src->founderror == 1)
		write(1, "Found error\n", 12);
}

void	ms_pipe_one(t_source *src, t_var *var)
{
	t_pipe		*here;
	t_pipe		*next;
	int			cont;

	fork_pips(src->npipe + 1, var->head, src);
	here = var->head->pipe;
	while (here != NULL)
	{
		cont = 0;
		next = here->next;
		free(here->cmd);
		while (here->arg[cont])
			free(here->arg[cont++]);		
		free(here->arg);
		free(here);
		here = next;
	}
	var->head->pipe = NULL;
}

void	ms_pipe_two(t_source *src, t_var *var)
{
	int id;

	id = fork();
	if (id == 0)
	{
		red_open(var->head, src);
		command_list(var->head->cmd ,var->head->arg, src);
		exit(0);
	}
	wait(&id);
}


void	ms_loop_semicolons(t_source *src, t_var *var)
{
	int  c;

	c = 0;
	while (var->pipes[c] != NULL)
	{
			ms_nodes(var ,src, var->pipes, c);
			if (!var->head->cmd)
			{
				c++;
				continue ;
			}
			if (src->foundred == 0 && src->foundpipe == 0)
				command_list(var->head->cmd, var->head->arg, src);
			else
			{
				if (src->foundpipe == 1)
					ms_pipe_one(src, var);
				if (src->foundred && !src->foundpipe)
					ms_pipe_two(src, var);
			}
			c++;
	}
}

void	ms_free(t_source *src, t_var *var)
{
	int n;
	
	n = 0;
	var->here = var->head->first_filename;
	while (var->here != NULL)
	{
		var->next = var->here->next;
		free(var->here->filename);
		free(var->here);
		var->here = var->next;
	}
	free(var->head->cmd);
	while (var->head->arg[n])
		free(var->head->arg[n++]);
	free(var->head->arg);
	free(var->head);
	n = 0;
	while (var->pipes[n] != NULL)
	{
		free(var->pipes[n]);
		n++;
	}
	free(var->pipes);
}


void	ms_loop(t_source *src, char **envp, t_var *var)
{
	char	*cmd;
	int		count;
	int		i = 0;
	char	*ret;
	int		c;

	ms_init(src, var, envp);
	while(1)
	{
		cmd = ms_get_cmd(src, var);
		if (ft_strncmp(cmd, "continue", 8) == 0)
			continue ;
		var->pipes = my_ft_split(cmd, ';', src);
		free(cmd);
		free(g_global.ret);
		c = 0;
		src->fd_r_c = 0;
		ms_loop_semicolons(src, var);
		ms_free(src, var);
	}
}

int     main(int argc, char **argv, char **envp)
{
	t_source src;
	t_var	var;

	ms_loop(&src, envp, &var);
	
	return (0);
}