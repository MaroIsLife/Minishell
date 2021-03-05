#include "minishell.h"

int finding_quotes_cmd(char *s,int i, t_source *src)
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
	return 0;
}

int finding_quotes(char *s,int i, t_source *src)
{
	if (s[i] == '\"' && src->squotes == 0 && src->aslash == 0)
	{
			if (src->dquotes == 0)
			src->dquotes = 1;
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
	finding_aslash(s, i, src);
	return 0;
}

int		finding_aslash(char *s, int i, t_source *src)
{
		if (s[i] == '\\' && s[i + 1] == '\'' && src->dquotes == 1)
			src->aslash = 0;
		else if (s[i] == '\\' && (s[i + 1] == '\"' || s[i + 1] == '\\' || s[i + 1] == '\'' || s[i + 1] == ';' || s[i + 1] == '|') && src->aslash == 0 && src->squotes == 0)
			src->aslash = 1;
		else if (s[i] == '\\' && (src->dquotes == 0 && src->squotes == 0))
		{
			if (ft_isascii(s[i + 1]) == 0)
				g_find.founderror = 1;
			else
				return (1);
		}
		else
			src->aslash = 0; //convert to return 0 or 1 for norminette?
	return 0;
}

void	find_for_split(char *cmd, t_source *src)
{
	int i;
	char **token;

	i = 0;
	g_find.founddquotes = 0;
	g_find.foundPipe = 0;
	g_find.foundSemiColons = 0;
	g_find.foundsquotes = 0;
	src->dquotes = 0;
	src->squotes = 0;
	while (cmd[i] != '\0')
	{
		finding_quotes_cmd(cmd,i, src);
		if (cmd[i] == ';' && src->dquotes == 0 && src->squotes == 0)
		{
			g_find.foundSemiColons = 1;
			g_find.nSemiColons++;
		}
		else if (cmd[i] == '|' && src->dquotes == 0 && src->squotes == 0)
		{
			g_find.foundPipe = 1;
			g_find.nPipe++;
		}
		 else if (cmd[i] == '\'' && src->dquotes == 0)
			g_find.nsquotes++;

		 else if (cmd[i] == '\"')
			g_find.ndquotes++;
		i++;
	}
	if (src->dquotes == 1 || src->squotes == 1)
		g_find.founderror = 1;
	// printf("%d\n",g_find.ndquotes); //Bugged to fix later
}