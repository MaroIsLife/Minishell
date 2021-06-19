#	include "minishell.h"

int	count_argument_three(char *s, int **i, t_source *src)
{
	if (s[(**i)] == '\"' && (**i) == 0)
		src->dquotes = 1;
	else if (s[(**i)] == '\'' && (**i) == 0)
		src->squotes = 1;
	else
		finding_quotes2(s, (**i), src);
	if ((s[(**i)] == ';' || s[(**i)] == '|') && (src->dquotes == 0
			&& src->squotes == 0 && src->aslash == 0) && s[(**i) - 1] != '\\')
		return (1);
	else
		return (0);
}

int	count_argument_two(char *s, int *i, int *count, t_source *src)
{
	if (count_argument_three(s, &i, src) == 1)
		return (1);
	if (s[(*i)] == ' ' && src->dquotes == 0 && src->squotes == 0)
	{
		while (s[(*i)] == ' ')
			(*i)++;
		if ((s[(*i)] == '|' || s[(*i)] == ';') && src->dquotes == 0
			&& src->squotes == 0 && src->aslash == 0 && s[(*i) - 1] != '\\')
			return (1);
		if (s[(*i)] == '\0' || s[(*i)] == '\n')
			return (1);
		if (s[(*i)] != '>' && s[(*i)] != '<' && src->tmp == 0)
			(*count)++;
		else
			src->tmp = 0;
	}
	else if (s[(*i)] == '>' || s[(*i)] == '<')
	{
		(*count)++;
		src->tmp = 1;
		(*i)++;
	}
	else
		(*i)++;
	return (0);
}

int	count_argument(char *s, t_source *src)
{
	int	i;
	int	jump;
	int	count;

	i = src->offset;
	count = 0;
	jump = 0;
	if (s[0] == '\n')
		return (0);
	if (i < 0)
		return (0);
	if (s[i] == '|')
		return (0);
	src->tmp = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		if (count_argument_two(s, &i, &count, src) == 1)
			return (count);
	}
	return (count);
}
