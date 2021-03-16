#include "minishell.h"

int		arg_if_space(char *s,int *i, t_source *src)
{
	if (s[*i] == ' ' && (src->dquotes == 1 || src->squotes == 1))
		src->re[src->re_b++] = s[*i];
	while (s[*i + 1] == ' ' && !(src->dquotes == 0 || src->squotes == 0))
		(*i)++;
	
	return (*i);
}

int count_argument(char *s, int offset, t_source *src) //CONVERT TO SPLIT?
{
	int i;
	int count;

	i = src->offset - 1;
	count = 0;
	if (s[0] == '\n')
		return 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' && i == 0)
		{
			src->dquotes = 1;
		}
		else if (s[i] == '\'' && i == 0)
			src->squotes = 1;
		else
			finding_quotes(s, i, src);
		if ((s[i] == ';' || s[i] == '|') && (src->dquotes == 0 && src->squotes == 0 && src->aslash == 0))
			return (count);
		if (s[i] == ' ' && src->dquotes == 0 && src->squotes == 0)
		{
			while (s[i] == ' ')
				i++;
			if ((s[i] == '|' || s[i] == ';') && src->dquotes == 0 && src->squotes == 0 && src->aslash == 0)
				return (count);
			if (s[i] == '\0' || s[i] == '\n')
				return (count);
			count++;
		}
		else
			i++;
	}
	return(count);
}


char	*find_argument(char *s, int offset, t_source *src, char **envp)
{
	int i;
	char *re;


	i = offset;
	while (s[i] == ' ')
		i++;
	src->re = malloc((1024) * sizeof(char));
	src->re_b = 0;
	while (s[i] != '\n' && s[i] != '\0')
	{
		if (s[i] == ' ')
		{
			if (s[i] == ' ' && (src->dquotes == 1 || src->squotes == 1))
				arg_if_space(s, &i, src);
			else if (s[i] == ' ' && (src->dquotes == 0 || src->squotes == 0))
				break ;
		}
		else if ((s[i] == '|' || s[i] == ';') && (src->dquotes == 0 && src->aslash == 0 ))
		{
			if (src->squotes == 1)
				src->re[src->re_b++] = s[i];
			else
				break ;
		}
		else if (s[i] == '\"' && src->squotes == 0 && src->aslash == 0)
			finding_quotes(s, i, src);
		else if (s[i] == '\'' && src->dquotes == 0 && src->aslash == 0)
			finding_quotes(s, i, src);
		else if (s[i] == '$' && src->aslash == 0 && ft_isalpha(s[i + 1]) == 1 && src->squotes == 0)
			i = get_env_value_arg(s, envp, src, i) - 1;
		else if (s[i] == '\\' && src->aslash == 0)
		{
			offset = finding_aslash(s,i, src);
			if (src->aslash == 0 && offset != 1)
			{
				src->re[src->re_b++] = s[i];
				offset = 0;
			}
		}
		else if ((s[i] == '\"' || s[i] == '\'' || s[i] == '\\' || s[i] == ';' || s[i] == '|' || s[i] == '$') && src->aslash == 1)
		{
			src->re[src->re_b++] = s[i];
			src->aslash = 0;
		}
		else
			src->re[src->re_b++] = s[i];
		i++;
	}
	if (src->dquotes == 1 || src->squotes == 1 || src->aslash == 1)
	{
		printf("Error\n");
		printf("Dquotes: %d, Squotes: %d, Aslash: %d\n",src->dquotes,src->squotes,src->aslash);
	}
	src->offset = i;
	src->re[src->re_b] = '\0';
	return (src->re);
}