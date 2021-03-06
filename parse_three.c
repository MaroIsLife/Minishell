#include "minishell.h"

int	find_space(t_source *src, int i)
{
	int	c;

	c = 0;
	while (src->redsplit[i][c] == ' ' && src->redsplit[i][c] != '\0')
		c++;
	while (src->redsplit[i][c] != ' ' && src->redsplit[i][c] != '\0')
		c++;
	return (c);
}

void	init_arg(t_node *head, char **arg, int tmp2)
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
	head->arg = malloc((b + 1) * sizeof(char *));
	i = 0;
	b = 0;
	while (arg[i] != NULL)
	{
		if (arg[i][0] != c)
			head->arg[b++] = ft_strdup(arg[i]);
		i++;
	}
	head->arg[b] = NULL;
}

int	parse_check(t_node *head, t_source *src)
{
	free(src->ra);
	if (head->cmd[0] == 0 && src->tmp2 == 1)
		src->dollarused = 1;
	if (src->aslash == 1 || src->dquotes == 1 || src->squotes == 1)
	{
		src->dollarused = 1;
		head->arg = NULL;
		return (1);
	}
	return (0);
}
