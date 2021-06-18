#include "minishell.h"

void	init_arg_pipe(char **arg, t_pipe *p, int tmp2)
{
	int		b;
	int		i;
	char	c;

	i = 0;
	b = 0;
	if (tmp2 == 1)
		c = 0;
	else
		c = 127;
	while (arg[i] != NULL)
	{
		if (arg[i++][0] != c)
			b++;
	}
	p->arg = malloc((b + 1) * sizeof(char *));
	i = 0;
	b = 0;
	while (arg[i] != NULL)
	{
		if (arg[i][0] != c)
			p->arg[b++] = ft_strdup(arg[i]);
		i++;
	}
	p->arg[b] = NULL;
}

t_filename	*new_file(char *s, t_source *src)
{
	t_filename	*tmp;

	tmp = (t_filename *) malloc(sizeof(t_filename));
	tmp->next = NULL;
	tmp->filename = ft_strdup(s);
	tmp->c = src->p->c;
	return (tmp);
}

t_filename	*get_last_node(t_filename *tmp)
{
	while (tmp)
	{
		if (tmp->next == NULL)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

t_pipe	*get_last_node_p(t_pipe *tmp)
{
	while (tmp)
	{
		if (tmp->next == NULL)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void	init_filee(t_source *src)
{
	t_filename	*tmp;

	if (src->npipe > 0 && src->foundred == 1 && src->ispipered == 1)
	{
		tmp = get_last_node(src->ptemp->pipef);
		if (tmp == NULL)
			src->ptemp->pipef = new_file(src->p->filename, src);
		else
			tmp->next = new_file(src->p->filename, src);
	}
}
