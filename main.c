#	include "minishell.h"

void	ms_pipe_two(t_source *src, t_var *var)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		red_open(var->head, src);
		command_list(var->head->cmd, var->head->arg, src);
		exit(0);
	}
	wait(&id);
}

void	ms_loop_semicolons(t_source *src, t_var *var)
{
	int	c;

	c = 0;
	while (var->pipes[c] != NULL)
	{
		ms_nodes(var, src, var->pipes, c);
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
	int	n;

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
	while (var->head->arg && var->head->arg[n])
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
	char	*ret;
	int		c;

	ms_init(src, var, envp);
	while (1)
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

int	main(int argc, char **argv, char **envp)
{
	t_source	src;
	t_var		var;

	ms_loop(&src, envp, &var);
	return (0);
}
