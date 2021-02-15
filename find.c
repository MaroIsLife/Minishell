#include "minishell.h"

void	find_for_split(char *cmd)
{
	int i;

	i = 0;
	g_find.foundDQuotes = 0;
	g_find.foundPipe = 0;
	g_find.foundSemiColons = 0;
	g_find.foundSQuotes = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == ';')
		{
			g_find.foundSemiColons = 1;
			g_find.nSemiColons++;
		}
		else if (cmd[i] == '|')
		{
			g_find.foundPipe = 1;
			g_find.nPipe++;
		}
		 else if (cmd[i] == '\'')
		 {
			g_find.foundSQuotes = 1;
			g_find.nSQuotes++;
		 }
		 else if (cmd[i] == '\"')
		 {
			g_find.foundDQuotes = 1; // \"
			g_find.nDQuotes++;
		 }
		i++;
	}
}

char	*find_command(char *s)
{
	int i;
	char *s1;

	i = 0;
	if (s[0] == ' ')
	{
		while(s[i] == ' ')
		{
			i++;
		}
	}
	while (s[i] != ' ' && i <= g_source.cmdlen)
	{
		if (s[i] == '\n')
			break;
		i++;
	}
	s1 = ft_substr(s,0,i);
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
	while (s[i] != '\n' && i <= g_source.cmdlen)
	{
		i++;

		if (s[i - 1] != '\\' && s[i] == '\"')
			b--;
		b++; //b = size of Argument
	}
	i = g_source.offset;
	re = malloc((b + 1) * sizeof(char));
	b = 0;
	while (s[i] != '\n' && s[i] != '|' && i <= g_source.cmdlen)
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
	
	printf("%s\n",re);
	return (re);
}