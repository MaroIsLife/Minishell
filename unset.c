#include "minishell.h"

void 	unset_export(t_source *src, char *arg)
{
	int	i;

	i = 0;
	while (src->export[i] != NULL)
	{
		if (is_equal(src->export[i], arg))
		{
			free(src->export[i]);
			src->export[i] = NULL;
			while ((src->export[i] != NULL))
			{
				src->export[i] = src->export[i + 1];
				i++;
			}
			src->lastexp--;
			src->export[i] = NULL;
			break ;
		}
		i++;
	}			
}

void	unset_env(t_source *src, char *arg)
{
	int	i;

	i = 0;
	while (src->our_envp[i] != NULL)
	{
		if (is_equal(src->our_envp[i], arg))
		{
			free(src->our_envp[i]);
			src->our_envp[i] = NULL;
			while ((src->our_envp[i] != NULL))
			{
				src->our_envp[i] = src->our_envp[i + 1];
				i++;
			}
			src->lastenv--;
			src->our_envp[i] = NULL;
			break ;
		}
		i++;
	}			
}

int	ft_unset(char **args, t_source *src)
{
	int	env;
	int	exp;
	int	j;
	int n;

	j = 0;
	while (args[j])
	{
		n = check_exsyn(args[j]);
		if (n)
		{
			write (2, "Minishell : not a valid identifier\n", 35);
			g_global.return_value = 1;
			j++;
			continue ;
		}
		env = ft_search(src->our_envp, args[j]);
		exp = ft_search(src->export, args[j]);
		if (exp)
			unset_export(src, args[j]);
		if (env)
			unset_env(src, args[j]);
		j++;
	}
	return (0);
}
