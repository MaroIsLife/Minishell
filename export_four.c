#include "minishell.h"

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
