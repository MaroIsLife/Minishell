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
			g_find.foundDQuotes = 1;
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