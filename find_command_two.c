#include "minishell.h"

char	*get_env_value_cmd_two(char *s, t_source *src, int i)
{
	int		b;
	char	*temp;

	b = 0;
	temp = malloc(4096 * sizeof(char));
	while (s[i] != '$' && s[i] != '\n' && s[i] != '\0' && s[i] != ' ')
	{
		temp[b++] = s[i++];
		if (ft_isalpha(s[i]) != 1)
			break ;
	}
	temp[b] = '\0';
	src->tmp = i;
	return (temp);
}

int	get_env_value_cmd_three(t_source *src, int *b, int c, char *temp)
{
	if (ft_strncmp(src->our_envp[c], temp, ft_strlen(temp)) == 0
		&& src->our_envp[c][ft_strlen(temp)] == '=')
	{
		while (src->our_envp[c][(*b)] != '=' && src->our_envp[c][(*b)] != '\0')
			(*b)++;
		while (src->our_envp[c][++(*b)] != '\0')
			src->ra[src->ra_b++] = src->our_envp[c][(*b)];
		src->ra[src->ra_b] = '\0';
		return (1);
	}
	return (0);
}

int	get_env_value_cmd(char *s, t_source *src, int i)
{
	char	*temp;
	int		b;
	int		c;
	int		length;

	i = i + 1;
	c = 0;
	if (s[i] == '?')
		return (init_question_cmd(src, i));
	src->dollarused = 1;
	temp = get_env_value_cmd_two(s, src, i);
	i = src->tmp;
	b = 0;
	length = ft_strlen(temp);
	while (src->our_envp[c] != NULL)
	{
		if (get_env_value_cmd_three(src, &b, c, temp) == 1)
			break ;
		c++;
	}
	free(temp);
	temp = NULL;
	return (i);
}
