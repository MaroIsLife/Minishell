#include "minishell.h"

int	num_of_node(t_pipe *tmp)
{
	int	i;

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

void	freeList_pipe(t_pipe *head)
{
	t_pipe	*tmp;
	int		i;
	int		n;

	n = num_of_node(head);
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
				free(tmp->arg[i++]);
		}
		free(tmp->arg);
	}
	free(tmp);
}

char	*get_x_env(char **envp, char *envv_name)
{
	int		i;
	int		b;
	int		c;

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
