#include "minishell.h"

void	init_find_for_split(t_source *src)
{
	src->foundpipe = 0;
	src->npipe = 0;
	src->nred = 0;
	src->dquotes = 0;
	src->foundred = 0;
	src->squotes = 0;
}

void	find_for_split(char *cmd, t_source *src)
{
	int		i;

	i = 0;
	init_find_for_split(src);
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '|' && src->dquotes == 0
			&& src->squotes == 0 && src->aslash == 0)
		{
			src->foundpipe = 1;
			src->npipe++;
		}
		else if ((cmd[i] == '>' || cmd[i] == '<') && src->dquotes == 0
			&& src->squotes == 0 && src->aslash == 0)
		{
			src->foundred = 1;
			src->nred++;
		}
		finding_quotes_split(cmd, i, src);
		i++;
	}
}

int	find_equal_length(char **envp, int c, int b)
{
	int	length;

	length = 0;
	while (envp[c][b] != '=' && envp[c][b] != '\0')
	{
		b++;
		length++;
	}
	return (length);
}

int	finding_quotes_split(char *s, int i, t_source *src)
{
	if (s[i] == '\"' && i == 0)
		src->dquotes = 1;
	else if (s[i] == '\'' && i == 0 && src->dquotes == 0)
		src->squotes = 1;
	else if (s[i] == '\"' && src->squotes == 0 && src->aslash == 0)
	{
		if (src->dquotes == 0)
		{
			src->dquotes = 1;
		}
		else
			src->dquotes = 0;
	}
	else if (s[i] == '\'' && src->dquotes == 0)
	{
		if (src->squotes == 0)
			src->squotes = 1;
		else
			src->squotes = 0;
	}
	finding_aslash_split(s, i, src);
	return (0);
}

int	finding_aslash_split(char *s, int i, t_source *src)
{
	if (s[i] == '\\' && s[i + 1] == '\'' && src->dquotes == 1)
		src->aslash = 0;
	else if (s[i] == '\\' && (s[i + 1] == '\"' || s[i + 1] == '\\'
			|| s[i + 1] == '\'' || s[i + 1] == '$' || s[i + 1] == '|')
		&& src->aslash == 0 && src->squotes == 0 && src->dquotes == 0)
		src->aslash = 1;
	else if (s[i] == '\\' && (src->dquotes == 0 && src->squotes == 0))
	{
		if (ft_isascii(s[i + 1]) == 0)
			src->founderror = 1;
		else
			return (1);
	}
	else
		src->aslash = 0;
	return (0);
}
