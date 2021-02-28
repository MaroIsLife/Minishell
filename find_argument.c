#include "minishell.h"

char	*find_argument(char *s, int offset, t_source *src)
{
	int i;
	int b;
	char *re;


	i = offset;
	while (s[i] == ' ')
		i++;
	re = malloc((1024) * sizeof(char));
	b = 0;
	while (s[i] != '\n' && s[i] != '\0')
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