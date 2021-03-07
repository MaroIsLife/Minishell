#include "minishell.h"

char	*find_command(char *s, int offset, t_source *src, char **envp)
{
	int i;
	int start;
	int length;
	char *s1;

	i = offset;
	while(s[i] == ' ')
		i++;
	start = i;
	while (s[start] != '\0' && s[i] != '\n')
	{
		finding_quotes(s, start, src);
		if (s[start] == ' ' && src->dquotes == 0 && src->squotes == 0)
			break ;
		start++;
	}
	length = 0;
	s1 = malloc((start + 1) * sizeof(char));
	while (i < start)
	{
		finding_quotes(s, i, src);
		if (s[i] == '\'')
		{
			if (src->dquotes == 1)
				s1[length++] = s[i];
		}
		else if (s[i] == '\"')
		{
			if (src->squotes == 1)
				s1[length++] = s[i];
		}
		else if (s[i] == '\\' && ft_isascii(s[i + 1]) == 1 && src->dquotes == 0 && src->squotes == 0)
			s1[length++] = s[++i];
		else if (s[i] == '\\' && src->aslash == 1)
		{
			if (s[i + 1] != '\\')
			{
				s1[length++] = s[i++];
				s1[length++] = s[i];
			}				
		}
		else 
			s1[length++] = s[i];
		i++;
	}
	s1[length] = '\0';
	src->offset = i + 1;
	return (s1);
}