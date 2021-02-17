#include "minishell.h"

int finding_quotes(char *s,int i)
{
	if (s[i] == '\"')
		{
			if (g_dQuotes == 0)
			{
				g_dQuotes = 1;
			}
			else
				g_dQuotes = 0;
		}
		else if (s[i] == '\'' && g_dQuotes == 0)
		{
			if (g_sQuotes == 0)
				g_sQuotes = 1;
			else
				g_sQuotes = 0;
		}
	return 0;
}

void	find_for_split(char *cmd)
{
	int i;
	char **token;

	i = 0;
	g_find.foundDQuotes = 0;
	g_find.foundPipe = 0;
	g_find.foundSemiColons = 0;
	g_find.foundSQuotes = 0;
	g_dQuotes = 0;
	g_sQuotes = 0;
	while (cmd[i] != '\0')
	{
		finding_quotes(cmd,i);
		if (cmd[i] == ';' && g_dQuotes == 0)
		{
			g_find.foundSemiColons = 1;
			g_find.nSemiColons++;
		}
		else if (cmd[i] == '|' && g_dQuotes == 0)
		{
			g_find.foundPipe = 1;
			g_find.nPipe++;
		}
		 else if (cmd[i] == '\'' && g_dQuotes == 0)
		 {
			// g_find.foundSQuotes = 1;
			g_find.nSQuotes++;
		 }
		 else if (cmd[i] == '\"')
		 {
			// g_find.foundDQuotes = 1;
			g_find.nDQuotes++;
		 }
		i++;
	}

	// printf("%d\n",g_find.nDQuotes); //Bugged to fix later
}

char	*find_command(char *s)
{
	int i;
	int start;
	int length;
	char *s1;

	i = 0;
	if (s[0] == ' ')
	{
		while(s[i] == ' ')
		{
			i++;
		}
	}
	while (s[i] == '\"' || s[i] == '\'')
	{
		i++;
	}
	start = i;
	length = 0;
	while ((s[i] != '\"' && s[i] != ' ' && s[i] != '\'') && i <= g_source.cmdlen)
	{
		if (s[i] == '\n')
			break;
		
		if (s[i] != '\"' || s[i] != '\'')
			length++;
		i++;
	}
	s1 = ft_substr(s,start,length);
	s1 = ft_strtrim(s1," ");
	g_source.offset = i;
		return (s1);
}

char	*find_argument(char *s)
{
	int i;
	int b;
	char *re;
	int dQuotes;
	int sQuotes;

	b = 0;
	dQuotes = 0;
	if (s[i] == '\"')
	{
		;
	}
	i = g_source.offset + 1;
	while (s[i] == ' ')
		i++;
	g_source.offset = i;
	while (s[i] != '\0' && i <= g_source.cmdlen)
	{
		i++;

		if (s[i - 1] != '\\' && s[i] == '\"')
			b--;
		b++; //b = size of Argument
	}
	i = g_source.offset;
	re = malloc((b + 1) * sizeof(char));
	b = 0;
	while (s[i] != '\0' && s[i] != '|' && i <= g_source.cmdlen)
	{
		if (s[i] == ' ')
		{
			re[b] = s[i];
			b++;
			while (s[i + 1] == ' ' && dQuotes == 0)
				i++;
		}
		else if (s[i] == '\"')
		{
			if (dQuotes == 0)
				dQuotes = 1;
			else
				dQuotes = 0;
		}
		else if (s[i] == '\'' && dQuotes == 0)
		{
			if (sQuotes == 0)
				sQuotes = 1;
			else
				sQuotes = 0;
		}
		else
		{
			re[b] = s[i];
			b++;
		}
		i++;
	}
	re[b] = '\0';

	// re = ft_substr(s,(g_source.offset),i - (g_source.offset));
	
	// printf("%s\n",re);
	return (re);
}