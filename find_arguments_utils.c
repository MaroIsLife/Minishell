#	include "minishell.h"

int	arg_if_space(char *s, int ***i, t_source *src)
{
	if (s[***i] == ' ' && (src->dquotes == 1 || src->squotes == 1))
		src->re[src->re_b++] = s[***i];
	while (s[***i + 1] == ' ' && !(src->dquotes == 0 || src->squotes == 0))
		(***i)++;
	return (***i);
}

int	check_offset(int offset, char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '>' || s[i] == '<')
		return (0);
	return (offset);
}
