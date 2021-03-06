#include "minishell.h"

char	**parse_pipe_arg(int count, t_source *src, char **pipe)
{
	char	**arg;
	int		i;

	i = 0;
	arg = malloc((count + 1) * sizeof(char *));
	src->ispipered = 1;
	src->fd_r_c = 0;
	src->tmp2 = 0;
	while (i < count)
	{
		arg[i] = find_argument(pipe[src->c], src);
		i++;
	}
	arg[i] = NULL;
	return (arg);
}

t_pipe	*new_pipe(char **pipe, t_source *src)
{
	t_pipe	*tmp;
	char	**arg;
	int		count;
	int		i;

	tmp = (t_pipe *) malloc(sizeof(t_pipe));
	tmp->next = NULL;
	tmp->pipef = NULL;
	src->ptemp = tmp;
	src->tmp2 = 0;
	tmp->cmd = find_command(pipe[src->c], src);
	free(src->ra);
	count = count_argument(pipe[src->c], src);
	arg = parse_pipe_arg(count, src, pipe);
	if (src->fd_r_c == 50 && tmp->pipef != NULL)
		tmp->pipef->fd_r_c = 50;
	init_arg_pipe(arg, tmp, src->tmp2);
	i = 0;
	while (arg[i])
		free(arg[i++]);
	free(arg);
	return (tmp);
}

void	loop_pipe(t_source *src, t_node *head, char **pipe)
{
	int		c;
	t_pipe	*tmp;
	int		i;

	c = 0;
	i = 0;
	while (c < src->npipe)
	{
		tmp = get_last_node_p(head->pipe);
		if (tmp == NULL)
			head->pipe = new_pipe(pipe, src);
		else
			tmp->next = new_pipe(pipe, src);
		c++;
	}
}

void	init_parse_arg(int count, char **pipe, t_source *src, t_node *head)
{
	char	**arg;
	int		i;

	i = 0;
	arg = malloc((count + 1) * sizeof(char *));
	src->tmp2 = 0;
	while (i < count)
	{
		arg[i] = find_argument(pipe[src->c], src);
		i++;
	}
	arg[i] = NULL;
	init_arg(head, arg, src->tmp2);
	i = 0;
	while (arg[i] != NULL)
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

int	init_parse(t_source *src, t_node *head, char **pipe)
{
	int		i;
	int		c;
	int		count;

	i = 0;
	c = 0;
	src->dollarused = 0;
	src->ispipered = 0;
	src->tmp2 = 0;
	head->cmd = find_command(pipe[src->c], src);
	if (parse_check(head, src) == 1)
		return (0);
	count = count_argument(pipe[src->c], src);
	src->count = count;
	src->dquotes = 0;
	src->squotes = 0;
	init_parse_arg(count, pipe, src, head);
	if (src->foundpipe == 1)
	{
		head->pipe = NULL;
		loop_pipe(src, head, pipe);
	}
	return (0);
}
