#include "minishell.h"
int		get_env_value_cmd(char *s, char **envp, t_source *src, int i)
{
	char	*temp;
	int		b;
	int		c;

	i = i + 1;
	b = 0;
	c = 0;

	if (s[i] == '?')
		return(init_question_cmd(src, i));
	src->dollarused = 1;
	temp = malloc(4096 * sizeof(char));
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
		if (ft_strncmp(envp[c], temp, find_equal_length(envp, c, b)) == 0)
		{
			while (envp[c][b] != '=' && envp[c][b] != '\0')
				b++;
				while (envp[c][++b] != '\0')
					src->ra[src->ra_b++] = envp[c][b];
				src->ra[src->ra_b] = '\0';
				break ;
		}
		c++;
	}
		// printf("MAde it here %s\n",src->ra);
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
	// printf("bug: %s\n i: %d \n", s, i);
	if (s[0] == '|' || s[i] == '\\')
		return 0;
	while(s[i] == ' ' || s[i] == '|')
		i++;
	start = i;
	start = count_start(s, src, start, &i);

	// printf("start: %d\n", start);
	// src->ra = malloc((start + 1) * sizeof(char));
	src->ra = malloc((4096) * sizeof(char));
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
		else if (s[i] == '$' && src->squotes == 0 && (ft_isalpha(s[i + 1]) == 1 || s[i + 1] == '?') && src->aslash == 0)
		{
			i = get_env_value_cmd(s, src->our_envp, src, i) - 1;
		}
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
	src->offset = i;
	// printf("Offset: %d\n",src->offset);
	return (src->ra);
}