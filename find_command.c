#include "minishell.h"
int		get_env_value_cmd(char *s, char **envp, t_source *src, int i)
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
		if (ft_strncmp(envp[c], temp, find_equal_length(envp, c, b) - 1) == 0)
		{
			while (envp[c][b] != '=' && envp[c][b] != '\0')
				b++;
				while (envp[c][++b] != '\0')
					src->ra[src->ra_b++] = envp[c][b];
				break ;
		}
		c++;
	}
	free(temp);
	return (i);
}
char	*find_command(char *s, t_node *head, t_source *src, char **envp)
{
	int i;
	int start;
	int file_found;
	file_found = 0;
	i = src->offset;
	while(s[i] == ' ')
		i++;
	start = i;
	while (s[start] != '\0' && s[start] != '\n')
	{
		finding_quotes(s, start, src);
		if (s[start] == '>' || s[start] == '<') // to be changed later
		{
			if (s[start + 1] == '>')
				start = start + 2;
			else
				start++;
			while (s[start] == ' ')
				start++;
			while (s[start] != ' ' && s[start] != '\0')
				start++;
			file_found = 1;
		}
		if (s[start] == ' ' && src->dquotes == 0 && src->squotes == 0 && file_found == 0)
			break ;
		else
			file_found = 0;
		if (s[start] != '\0')
			start++;
	}
	src->ra_b = 0;
	// src->ra = malloc((start + 1) * sizeof(char));
	src->ra = malloc((1024) * sizeof(char));
	while (i < start)
	{
		finding_quotes(s, i, src);
		if (s[i] == '\'')
		{
			if (src->dquotes == 1)
				src->ra[src->ra_b++] = s[i];
		}
		else if (s[i] == '\"')
		{
			if (src->squotes == 1)
				src->ra[src->ra_b++] = s[i];
		}
		else if (s[i] == '\\' && ft_isascii(s[i + 1]) == 1 && src->dquotes == 0 && src->squotes == 0)
			src->ra[src->ra_b++] = s[++i];
		else if (s[i] == '$' && src->squotes == 0 && ft_isalpha(s[i + 1]) == 1 && src->aslash == 0)
			i = get_env_value_cmd(s, envp, src, i) - 1;
		else if ((s[i] == '>' || s[i] == '<') && src->aslash == 0 && src->dquotes == 0 && src->squotes == 0)
		{
			while (s[i] == '>' || s[i] == '<') //TEST THIS WITH ls>out1>out2 or >out1>out2 ls
				find_file_name(&i, s, src, head);
			i++;
			continue ;
		}
		else if (s[i] == '\\' && src->aslash == 1)
		{
			if (s[i + 1] != '\\')
			{
				src->ra[src->ra_b++] = s[i++];
				src->ra[src->ra_b++] = s[i];
			}				
		}
		else 
			src->ra[src->ra_b++] = s[i];
		i++;
	}
	src->ra[src->ra_b] = '\0';
	src->offset = i + 1;
	return (src->ra);
}