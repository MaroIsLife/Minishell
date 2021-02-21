#include "minishell.h"


int finding_quotes(char *s,int i)
{
	if (s[0] == '\"')
	{
		g_dQuotes = 1;
		return 0;
	}
	else if (s[0] == '\'')
	{
		g_sQuotes = 1;
		return 0;
	}
	if (s[i] == '\"' && s[i - 1] != '\\')
		{
			if (g_dQuotes == 0)
			{
				g_dQuotes = 1;
			}
			else
				g_dQuotes = 0;
		}
		else if (s[i] == '\'' && g_dQuotes == 0 && s[i - 1] != '\\')
		{
			if (g_sQuotes == 0)
				g_sQuotes = 1;
			else
				g_sQuotes = 0;
		}
	return 0;
}

void	finding_aslash(char *s, int i)
{
		if (s[i] == '\\' && (s[i + 1] != '\"' || s[i + 1] != '\'') && s[i + 1] != '\\')
		{
			if (g_aSlash == 0)
			{
				g_aSlash = 1;
			}
			else
				g_aSlash = 0;
		}
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
	g_source.offset = i + 1;
		return (s1);
}

char	*find_argument(char *s)
{
	int i;
	int b;
	char *re;


	b = 0;
	i = g_source.offset;
	while (s[i] == ' ')
		i++;
	g_source.offset = i;
	while (s[i] != '\0' && i <= g_source.cmdlen)
	{
		i++;

		// if (s[i - 1] != '\\' && s[i] == '\"')
		// 	b--;
		b++; //b = size of Argument
	}
	i = g_source.offset;
	re = malloc((1024) * sizeof(char));
	b = 0;
	while (s[i] != '\0' && s[i] != '|' && i <= g_source.cmdlen)
	{
		finding_aslash(s, i);
		if (s[i] == ' ')
		{
			if (s[i] == ' ' && (g_dQuotes == 1 || g_sQuotes == 1))
			{
				re[b] = s[i];
				b++;
			}
			else if (s[i] == ' ' && (g_dQuotes == 0 || g_sQuotes == 0))
			{
				g_source.offset = i;
				re[b] = '\0';
				return (re);
			}
			while (s[i + 1] == ' ' && g_dQuotes == 0)
				i++;
		}
		else if (s[i] == '\"' && s[i - 1] != '\\')
		{
			if (g_dQuotes == 0)
				g_dQuotes = 1;
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
		else if (s[i] == '\\' && (s[i + 1] == '\"' || s[i + 1] == '\'' || s[i + 1] == '\\'))
		{
			;
		}
		else
		{
			re[b] = s[i];
			b++;
		}
		i++;
	}
	if (g_dQuotes == 1)
		printf("Error\n");
	printf("Slash: %d\n",g_aSlash);
	g_source.offset = i;
	re[b] = '\0';
	return (re);
}