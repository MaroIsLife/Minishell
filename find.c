#include "minishell.h"

int finding_quotes_cmd(char *s,int i)
{
	if (s[i] == '\"' && i == 0)
		g_dquotes = 1;
	else if (s[i] == '\'' && i == 0 && g_dquotes == 0)
		g_squotes = 1;
	else if (s[i] == '\"' && s[i - 1] != '\\')
		{
			if (g_dquotes == 0)
			{
				g_dquotes = 1;
			}
			else
				g_dquotes = 0;
		}
		else if (s[i] == '\'' && g_dquotes == 0 && s[i - 1] != '\\')
		{
			if (g_squotes == 0)
				g_squotes = 1;
			else
				g_squotes = 0;
		}
	return 0;
}

int finding_quotes(char *s,int i)
{
	finding_aslash(s, i);
	if (s[i] == '\"' && g_squotes == 0 && g_aSlash == 0) //ADDED g_squotes??
	{
			if (g_dquotes == 0)
			{
				g_dquotes = 1;
			}
			else
				g_dquotes = 0;
	}
	else if (s[i] == '\'' && g_dquotes == 0 && g_aSlash == 0)
	{
			if (g_squotes == 0)
			{
				g_squotes = 1;
				printf("Here");
			}
			else
				g_squotes = 0;
	}
	return 0;
}

void	finding_aslash(char *s, int i)
{
		if (s[i] == '\\' && (s[i + 1] == '\"' || s[i + 1] == '\'' || s[i + 1] == '\\'))
				g_aSlash = 1;
		else
				g_aSlash = 0;

				//convert to return 0 or 1 for norminette?
}

void	find_for_split(char *cmd)
{
	int i;
	char **token;

	i = 0;
	g_find.founddquotes = 0;
	g_find.foundPipe = 0;
	g_find.foundSemiColons = 0;
	g_find.foundsquotes = 0;
	g_dquotes = 0;
	g_squotes = 0;
	while (cmd[i] != '\0')
	{
		finding_quotes_cmd(cmd,i);
		if (cmd[i] == ';' && g_dquotes == 0)
		{
			g_find.foundSemiColons = 1;
			g_find.nSemiColons++;
		}
		else if (cmd[i] == '|' && g_dquotes == 0)
		{
			g_find.foundPipe = 1;
			g_find.nPipe++;
		}
		 else if (cmd[i] == '\'' && g_dquotes == 0)
			g_find.nsquotes++;

		 else if (cmd[i] == '\"')
			g_find.ndquotes++;
		i++;
	}
	if (g_dquotes == 1 || g_squotes == 1)
		g_find.founderror = 1;
	// printf("%d\n",g_find.ndquotes); //Bugged to fix later
}

char	*find_command(char *s, int offset)
{
	int i;
	int start;
	int length;
	char *s1;

	i = offset;
	if (s[offset] == ' ')
	{
		while(s[i] == ' ')
			i++;
	}
	while (s[i] == '\"' || s[i] == '\'')
	{
		i++;
	}
	start = i;
	length = 0;
	while ((s[i] != '\"' && s[i] != ' ' && s[i] != '\''))
	{
		if (s[i] == '\n')
			break;
		
		if (s[i] != '\"' && s[i] != '\'')
			length++;
		i++;
	}
	s1 = ft_substr(s,start,length);
	s1 = ft_strtrim(s1," ");
	g_source.offset = i + 1;
		return (s1);
}

char	*find_argument(char *s, int offset)
{
	int i;
	int b;
	char *re;


	b = 0;
	i = offset;
	while (s[i] == ' ')
		i++;
	g_source.offset = i;
	i = g_source.offset;
	re = malloc((1024) * sizeof(char));
	b = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ')
		{
			if (s[i] == ' ' && (g_dquotes == 1 || g_squotes == 1))
				re[b++] = s[i];
			else if (s[i] == ' ' && (g_dquotes == 0 || g_squotes == 0))
			{
				g_source.offset = i;
				re[b] = '\0';
				return (re);
			}
			while (s[i + 1] == ' ' && g_dquotes == 0)
				i++;
		}
		else if ((s[i] == '|' || s[i] == ';') && (g_dquotes == 0))
		{
			if (g_squotes == 1)
				re[b++] = s[i];
			else {	
				g_source.offset = i;
				re[b] = '\0';
				return (re);
			}
		}
		else if (s[i] == '\"' && g_squotes == 0 && g_aSlash == 0)
		{
			if (g_dquotes == 0)
				g_dquotes = 1;
			else
				g_dquotes = 0;
		}
		else if (s[i] == '\'' && g_dquotes == 0 && s[i - 1] != '\\')
		{
			if (g_squotes == 0)
				g_squotes = 1;
			else
				g_squotes = 0;
		}
		else if (s[i] == '\\' && g_aSlash == 0)
		{
			finding_aslash(s,i);
			if (g_aSlash == 0)
				re[b++] = s[i];
		}
		else if ((s[i] == '\"' || s[i] == '\'' || s[i] == '\\') && g_aSlash == 1)
		{
			re[b++] = s[i];
			g_aSlash = 0;
		}
		else
			re[b++] = s[i];
		i++;
	}
	if (g_dquotes == 1 || g_squotes == 1)
		printf("Error\n");
	g_source.offset = i;
	re[b] = '\0';
	return (re);
}