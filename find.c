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
		else if (s[i] == '\\' && (s[i + 1] == '\"' || s[i + 1] == '\\' || s[i + 1] == '\'' || s[i + 1] == ';' || s[i + 1] == '|') && src->aslash == 0)
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

char	*find_command(char *s, int offset, t_source *src)
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
	while (s[i] == '\"' || s[i] == '\'' || s[i] == ';' || s[i] == ' ')
	{
		i++;
	}
	start = i;
	length = 0;
	s1 = malloc(1024 * sizeof(char));
	while (s[i] != ' ' && s[i] != '\0')
	{
		if (s[i] == '\n')
			break;
		
		if (s[i] != '\"' && s[i] != '\'' && s[i] != '\\')
		{
			s1[length] = s[i];
			length++;
		}
		i++;
	}
	s1[length] = '\0';
	// s1 = ft_strtrim(s1," ");
	src->offset = i + 1;
		return (s1);
}

char	*find_argument(char *s, int offset, t_source *src)
{
	int i;
	int b;
	char *re;


	b = 0;
	i = offset;
	while (s[i] == ' ')
		i++;
	src->offset = i;
	re = malloc((1024) * sizeof(char));
	b = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ')
		{
			if (s[i] == ' ' && (src->dquotes == 1 || src->squotes == 1))
				re[b++] = s[i];
			else if (s[i] == ' ' && (src->dquotes == 0 || src->squotes == 0))
			{
				src->offset = i;
				re[b] = '\0';
				return (re);
			}
			while (s[i + 1] == ' ' && src->dquotes == 0)
				i++;
		}
		else if ((s[i] == '|' || s[i] == ';') && (src->dquotes == 0 && src->aslash == 0 ))
		{
			if (src->squotes == 1)
				re[b++] = s[i];
			else {	
				src->offset = i;
				re[b] = '\0';
				return (re);
			}
		}
		else if (s[i] == '\"' && src->squotes == 0 && src->aslash == 0)
		{
			if (src->dquotes == 0)
				src->dquotes = 1;
			else
				src->dquotes = 0;
		}
		else if (s[i] == '\'' && src->dquotes == 0 && src->aslash == 0)
		{
			if (src->squotes == 0)
				src->squotes = 1;
			else
				src->squotes = 0;
		}
		else if (s[i] == '\\' && src->aslash == 0)
		{
			offset = finding_aslash(s,i, src);
			if (src->aslash == 0 && offset != 1)
			{
				re[b++] = s[i];
				offset = 0;
			}
		}
		else if ((s[i] == '\"' || s[i] == '\'' || s[i] == '\\' || s[i] == ';' || s[i] == '|') && src->aslash == 1)
		{
			re[b++] = s[i];
			src->aslash = 0;
		}
		else
			re[b++] = s[i];
		i++;
	}
	if (src->dquotes == 1 || src->squotes == 1)
		printf("Error\n");
	src->offset = i;
	re[b] = '\0';
	return (re);
}