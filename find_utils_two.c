#include "minishell.h"

int	finding_quotes_cmd(char *s, int i, t_source *src)
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
	finding_aslash(s, i, src);
	return (0);
}

int	finding_quotes(char *s, int i, t_source *src)
{
	if (s[i] == '\"' && src->squotes == 0 && src->aslash == 0)
	{
		if (src->dquotes == 0)
		{
			src->dquotes = 1;
		}
		else
			src->dquotes = 0;
	}
	else if (s[i] == '\'' && src->dquotes == 0 && src->aslash == 0)
	{
		if (src->squotes == 0)
		{
			src->squotes = 1;
		}
		else
			src->squotes = 0;
	}
	finding_aslash_split(s, i, src);
	return (0);
}

int	finding_aslash(char *s, int i, t_source *src)
{
	if (s[i] == '\\' && s[i + 1] == '\'' && src->dquotes == 1)
		src->aslash = 0;
	else if (s[i] == '\\' && (s[i + 1] == '\"' || s[i + 1] == '\\'
			|| s[i + 1] == '\'' || s[i + 1] == '$')
		&& src->aslash == 0 && src->squotes == 0)
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

int	finding_aslash2(char *s, int i, t_source *src)
{
	if (s[i] == '\\' && s[i + 1] == '\'' && src->dquotes == 1)
		src->aslash = 0;
	else if (s[i] == '\\' && (s[i + 1] == '\"' || s[i + 1] == '\\'
			|| s[i + 1] == '\'' || s[i + 1] == '$')
		&& src->aslash == 0 && src->squotes == 0)
	{
		src->aslash = 1;
	}
	else
		src->aslash = 0;
	return (0);
}

int	finding_quotes2(char *s, int i, t_source *src)
{
	if (s[i] == '\"' && src->squotes == 0 && src->aslash == 0)
	{
		if (src->dquotes == 0)
		{
			src->dquotes = 1;
		}
		else
			src->dquotes = 0;
	}
	else if (s[i] == '\'' && src->dquotes == 0 && src->aslash == 0)
	{
		if (src->squotes == 0)
		{
			src->squotes = 1;
		}
		else
			src->squotes = 0;
	}
	finding_aslash2(s, i, src);
	return (0);
}
