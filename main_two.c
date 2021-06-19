#include "minishell.h"

void	init_env(t_source *src, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		src->lastenv++;
		src->lastexp++;
		i++;
	}
	src->our_envp = malloc(sizeof(char *) * (i + 2));
	src->export = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (envp[i] != NULL)
	{
		src->our_envp[i] = ft_strdup(envp[i]);
		src->export[i] = ft_strdup(envp[i]);
		i++;
	}
	src->our_envp[i] = NULL;
	src->export[i] = NULL;
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
	src->lastenv = 0;
	src->lastexp = 0;
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
	ft_free_filenames(var->head->pipe->pipef);
	var->head->pipe = NULL;
}
