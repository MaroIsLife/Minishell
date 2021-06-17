#include "minishell.h"

int     check_bs(char *n)
{
    int i;

    i = 1;
    while (n[i] != 0)
    {
        if (n[0] != '-')
            return (2);
        if (n[i] != 'n')
            return (1);
        i++;
    }
    return (0);
}
void    ft_print_args(char **args, int i)
{
    ft_putstr_fd(args[i], 1);
    if (args[i + 1])
        ft_putchar_fd(' ', 1);
}

void    ft_echo (char **args)
{
    int i;
    int nl;
    int val_arg;

    i = 0;
    val_arg = 0;
    nl = 0;
    while (args && args[i] != NULL)
    {
        if (args[i][0] == '-')
        {
            if (!check_bs(args[i]) && !val_arg)
                {
                    nl = 1;
                    i++;
                    if (check_bs(args[i]))
                        val_arg = 1;
                    continue;
                }
                val_arg = 2;
        }
        ft_print_args(args ,i++);
    }
    if (nl == 0)
        ft_putchar_fd('\n', 1);
}

int	ft_strlen_eq(char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		if (src[i] == '=')
			break ;
	return (i);
}

void	replace_env(char **envp, t_source *src, char *value)
{
	int		i;
	char	*tmp;

	i = 0;
	while (src->our_envp[i] != NULL)
	{
		if (ft_strncmp(value, src->our_envp[i], ft_strlen_eq(value)) == 0)
		{
			tmp = src->our_envp[i];
			src->our_envp[i] = ft_strdup(value);
			free (tmp);
			if (i == src->lastenv)
				src->our_envp[i] = NULL;
		}
		i++;
	}
}

int	arg_counter(char **src)
{
	int	i;

	i = 0;
	while (src[i] != NULL)
		i++;
	return (i);
}

char	**our_realloc(char **s, int count)
{
	char	**ret;
	int		i;

	ret = malloc(count);
	i = -1;
	while (s[++i])
		ret[i] = ft_strdup(s[i]);
	return (ret);
}

void	print_env(t_source *src)
{
	int	i;

	i = 0;
	while (src->our_envp[i] != NULL)
	{
		ft_putstr_fd(src->our_envp[i], 1);
		if (src->our_envp[i][0] != '\0')
			ft_putstr_fd("\n", 1);
		i++;
	}
}

char	*where_home(t_source *src)
{
	int		i;
	char	*home;

	i = 0;
	while (src->our_envp[i])
	{
		if (ft_strncmp(src->our_envp[i], "HOME=", 5) == 0)
		{
			home = malloc (ft_strlen(src->our_envp[i] + 5) + 1);
			ft_strlcpy(home, src->our_envp[i] + 5,
				ft_strlen(src->our_envp[i] + 5) + 1);
			return (home);
		}
		i++;
	}
	return (0);
}

void	ft_pwd (void)
{
	char	*s;

	s = malloc(100 * sizeof(char));
	printf("%s\n", getcwd(s, 100));
	free (s);
}

void	ft_cd(char **args, t_source *src, char *home)
{
	int	sign;

	sign = 0;
	if (!args[0])
	{
		if (!home)
			write(1, "minishell: cd: HOME not set\n", 23);
		else
			chdir(home);
	}
	else
		sign = chdir(args[0]);
	if (sign != 0)
		printf ("Error: %s\n", strerror(errno));
	change_pwd_env(src);
	change_pwd_export(src);
}

void	ft_sort_two(t_source *src, int *i, int *j, int *n)
{
	if (src->export[(*i)][0] > src->export[(*j)][0])
	{
		src->ctmp2 = src->export[(*i)];
		src->export[(*i)] = src->export[(*j)];
		src->export[(*j)] = src->ctmp2;
	}
	if (src->export[(*i)][0] == src->export[(*j)][0])
	{
		(*n) = 1;
		while (src->export[(*j)][(*n)] != '\0' && src->export[(*i)][(*n)] != '\0')
		{
			if (src->export[(*i)][(*n)] > src->export[(*j)][(*n)])
			{
				src->ctmp2 = src->export[(*i)];
				src->export[(*i)] = src->export[(*j)];
				src->export[(*j)] = src->ctmp2;
			}
			(*n)++;
		}
	}
	(*j)++;
}

void 	ft_sort(t_source *src)
{
	int		i;
	int		j;
	int		n;

	i = 0;
	while (i < src->lastexp && src->export[i] != NULL)
	{
		j = i + 1;
		while ((j) < src->lastexp && src->export[(j)] != NULL)
			ft_sort_two(src, &i, &j, &n);
		i++;
	}
}

void ft_wr_eq(char *s)
{
	int	i;
	int	sign;

	if (s != NULL)
	{
		i = 0;
		sign = 0;
		while (s[i] != 0)
		{
			if (s[i] == '=' && s[i + 1])
			{
				sign = 1;
				write(1, &s[i++], 1);
				write(1, "\"", 1);
			}
			write(1, &s[i], 1);
			if (s[i] == '=' && !s[i + 1])
			{
				write(1, "\"\"", 2);
				break ;
			}
			if (!s[++i] && sign == 1)
				write(1, "\"", 1);
		}
	}
}

void	em_export(t_source *src)
{
	int	i;

	i = 0;
	ft_sort(src);
	while (src->export[i] != NULL)
	{
		write (1, "declare -x ", 11);
		ft_wr_eq(src->export[i]);
		if (src->export[i][0] != '\0')
			write(1, "\n", 1);
		i++;
	}
}

int	found_eq(char *src)
{
	int	i;

	if (src)
	{
		i = -1;
		while (src[++i])
			if (src[i] == '=')
				return (1);
	}
	return (0);
}

int		is_equal(char *s1, char *s2)
{
	int	l1;
	int	l2;
	int	i;

	l1 = ft_strlen_eq(s1);
	l2 = ft_strlen_eq(s2);
	if (l1 != l2)
		return (0);
	i = 0;
	while (i < l1)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int ft_search(char **src, char *value)
{
	int i;

	i = 0;
	while (src[i] != NULL)
	{
		if (is_equal(src[i], value))
			return (1);
		i++;
	}
	return (0);
}

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

int ft_alloc_count(char **envp, char **args)
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

void free2DArray(char	**array)
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

void 	ft_expn_add(char *add, t_source *src, char **our_envp, char **args)
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
		ft_expn_add_two(tmp1, tmp2, 2, 0);
	}
}

void	ft_expn_chng_two(char *add, t_source *src, char **args, char **envp)
{
	int		i;
	char	**tmp;

	if (ft_search(src->our_envp, add))
		replace_env(envp, src, add);
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

void	ft_expn_chng(char *add, t_source *src ,char **envp, char **args)
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
		ft_expn_chng_two(add, src, args, envp);
}

void	ft_set_enxp(char **args, t_source *src, char **envp)
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
			write (2, "not a valid identifier\n", 23);
			i++;
			continue ;
		}
		if (ft_search(src->export, args[i]))
			ft_expn_chng(args[i], src, src->our_envp, args);
		else
			ft_expn_add(args[i], src, src->our_envp, args);
		i++;
	}
}

void	ft_export(char **args, t_source *src)
{
	if (args[0] == NULL)
		em_export(src);
	else
		ft_set_enxp(args, src, src->our_envp);
}
