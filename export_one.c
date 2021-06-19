#include "minishell.h"

void 	ft_expn_add(char *add, t_source *src, char **args)
{
	int		id;
	char	**tmp1;
	char	**tmp2;

	id = found_eq(add);
	if (id)
	{
		tmp1 = src->our_envp;
		tmp2 = src->export;
		src->our_envp = our_realloc(src->our_envp,
				sizeof(char *) * (ft_alloc_count(src->our_envp, args) + 2));
		src->export = our_realloc(src->export,
				sizeof(char *) * (ft_alloc_count(src->export, args) + 2));
		src->our_envp[src->lastenv++] = ft_strdup(add);
		src->export[src->lastexp++] = ft_strdup(add);
		src->export[src->lastexp] = NULL;
		src->our_envp[src->lastenv] = NULL;
		ft_expn_add_two(tmp1, tmp2, 1, 0);
	}
	else
	{
		tmp1 = src->export;
		ft_expn_add_else(add, src, args);
		ft_expn_add_two(tmp1, NULL, 2, 0);
	}
}

void	ft_expn_chng_two(char *add, t_source *src)
{
	int		i;
	char	**tmp;

	if (ft_search(src->our_envp, add))
		replace_env(src, add);
	else
	{
		tmp = src->our_envp;
		src->our_envp = our_realloc(src->our_envp,
				sizeof(char *) * (arg_counter(src->our_envp) + 2));
		src->our_envp[src->lastenv++] = ft_strdup(add);
		src->our_envp[src->lastenv] = NULL;
		i = 0;
		while (tmp[i] != NULL && tmp[i][0] != 0)
		{
			free(tmp[i]);
			tmp[i] = NULL;
			i++;
		}
		free(tmp);
	}
}

void	ft_expn_chng(char *add, t_source *src)
{
	int		i;
	char	*s_tmp;
	char	*see;

	i = 0;
	while (src->export[i] != NULL)
	{
		see = src->export[i];
		if (is_equal(add, src->export[i]))
		{
			if (found_eq(add))
			{
				s_tmp = src->export[i];
				src->export[i] = ft_strdup(add);
				free (s_tmp);
			}
			if (i == src->lastexp)
				src->export[++i] = NULL;
		}
		i++;
	}
	if (found_eq(add))
		ft_expn_chng_two(add, src);
}

void	ft_set_enxp(char **args, t_source *src)
{
	int	argn;
	int	i;
	int	n;

	i = 0;
	argn = arg_counter(args);
	while (i < argn)
	{
		n = check_exsyn(args[i]);
		if (n)
		{
			write (2, "Minishell : not a valid identifier\n", 35);
			g_global.return_value = 1;
			i++;
			continue ;
		}
		if (ft_search(src->export, args[i]))
			ft_expn_chng(args[i], src);
		else
			ft_expn_add(args[i], src, args);
		i++;
	}
}

void	ft_export(char **args, t_source *src)
{
	if (args[0] == NULL)
		em_export(src);
	else
		ft_set_enxp(args, src);
}
