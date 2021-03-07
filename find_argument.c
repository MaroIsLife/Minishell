#include "minishell.h"


int		get_env_value(char *s, char **envp, t_source *src, int i)
{
	char	*temp;
	int		b;
	int		c;

	i = i + 1;
	b = 0;
	c = 0;
	temp = malloc(1024 * sizeof(char));
	while (s[i] != '$' && s[i] != '\n' && s[i] != '\0' && s[i] != ' ')
	{
		temp[b++] = s[i++];
		if (ft_isalpha(s[i]) != 1)
			break ;
	}
	temp[b] = '\0';
	b = 0;
	while (envp[c] != NULL)
	{
		if (ft_strncmp(envp[c],temp,ft_strlen(temp)) == 0)
		{
			printf("Made it here\n");
			while (envp[c][b] != '=' && envp[c][b] != '\0')
				b++;
				while (envp[c][++b] != '\0')
					src->re[src->re_b++] = envp[c][b];
				break ;
		}
		c++;
	}
	free(temp);
	return (i);
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
				src->re[src->re_b++] = s[i];
			else if (s[i] == ' ' && (src->dquotes == 0 || src->squotes == 0))
			{
				src->offset = i;
				src->re[src->re_b] = '\0';
				return (src->re);
			}
			while (s[i + 1] == ' ' && src->dquotes == 0)
				i++;
		}
		else if ((s[i] == '|' || s[i] == ';') && (src->dquotes == 0 && src->aslash == 0 ))
		{
			if (src->squotes == 1)
				src->re[src->re_b++] = s[i];
			else {	
				src->offset = i;
				src->re[src->re_b] = '\0';
				return (src->re);
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
		else if (s[i] == '$' && src->aslash == 0 && ft_isalpha(s[i + 1]) == 1 && src->squotes == 0)
		{
			i = get_env_value(s, envp, src, i) - 1;
		}
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