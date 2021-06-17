#include "minishell.h"
int 	check_exsyn(char *src)
{
	int	i;

	if (src[0] == '_' || ft_isalpha(src[0]))
	{
		i = 1;
		while (src[i] != '=' && src[i])
		{	
			if (!ft_isalnum(src[i]) && src[i] != '_')
				return (1);
			i++;
		}
	}
	else
		return (1);
	return (0);
}

int	ft_alloc_count(char **envp, char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	while (args[j] != NULL)
	{
		if (ft_search(envp, args[j]))
			i++;
		j++;
	}
	return (i);
}

void	free2DArray(char	**array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_expn_add_two(char **tmp1, char **tmp2, int option, int i)
{
	if (option == 1)
	{
		while (tmp1[i] != NULL && tmp1[i][0] != 0)
		{
			free(tmp1[i]);
			i++;
		}
		free(tmp1);
		i = 0;
		while (tmp2[i] != NULL && tmp2[i][0] != 0)
		{
			free(tmp2[i]);
			i++;
		}
		free(tmp2);
	}
	else if (option == 2)
	{
		while (tmp1[i] != NULL)
		{
			free(tmp1[i]);
			i++;
		}
		free(tmp1);
	}
}

void	ft_expn_add_else(char *add, t_source *src, char **args)
{
	src->export = our_realloc(src->export,
			sizeof(char *) * (ft_alloc_count(src->export, args) + 2));
	src->export[src->lastexp++] = ft_strdup(add);
	src->export[src->lastexp] = NULL;
}
