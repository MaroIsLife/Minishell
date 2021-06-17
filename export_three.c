#include "minishell.h"

void	ft_wr_eq(char *s)
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

int	is_equal(char *s1, char *s2)
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

int	ft_search(char **src, char *value)
{
	int	i;

	i = 0;
	while (src[i] != NULL)
	{
		if (is_equal(src[i], value))
			return (1);
		i++;
	}
	return (0);
}
