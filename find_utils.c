#include "minishell.h"

int	init_question_arg(t_source *src, int ret)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_itoa(g_global.return_value);
	while (s[i] != '\0')
		src->re[src->re_b++] = s[i++];
	free(s);
	return (ret + 1);
}

int	init_question_cmd(t_source *src, int ret)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_itoa(g_global.return_value);
	while (s[i] != '\0')
		src->ra[src->ra_b++] = s[i++];
	free(s);
	return (ret + 1);
}

int	init_question_red(t_source *src, int ret)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_itoa(g_global.return_value);
	while (s[i] != '\0')
		src->ra[src->ra_b++] = s[i++];
	free(s);
	return (ret + 1);
}

int	get_env_value_arg_three(t_source *src, int *b, int c, char *temp)
{
	if (ft_strncmp(src->our_envp[c], temp, ft_strlen(temp)) == 0
		&& src->our_envp[c][ft_strlen(temp)] == '=')
	{
		while (src->our_envp[c][(*b)] != '=' && src->our_envp[c][(*b)] != '\0')
			(*b)++;
		while (src->our_envp[c][++(*b)] != '\0')
			src->re[src->re_b++] = src->our_envp[c][(*b)];
		return (1);
	}
	return (0);
}

int	get_env_value_arg(char *s, t_source *src, int i)
{
	char	*temp;
	int		b;
	int		length;
	int		c;

	i = i + 1;
	b = 0;
	c = 0;
	if (s[i] == '?')
		return (init_question_arg(src, i));
	temp = get_env_value_cmd_two(s, src, i);
	i = src->tmp;
	b = 0;
	length = ft_strlen(temp);
	while (src->our_envp[c] != NULL)
	{
		if (get_env_value_arg_three(src, &b, c, temp) == 1)
			break ;
		c++;
	}
	free(temp);
	return (i);
}
