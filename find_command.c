#include "minishell.h"
int		get_env_value_cmd(char *s, char **envp, t_source *src, int i)
{
	char	*temp;
	int		b;
	int		c;
	int length;

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
	length = ft_strlen(temp);
	while (envp[c] != NULL)
	{
		// if (ft_strncmp(envp[c], temp, find_equal_length(envp, c, b)) == 0)
		if (ft_strncmp(src->our_envp[c], temp, length) == 0 && src->our_envp[c][length] == '=')
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

int		find_command_three(char *s, t_source *src, t_node *head, int *i)
{

	if (s[(*i)] == '\'')
		{
			if (src->dquotes == 1)
				src->ra[src->ra_b++] = s[(*i)];
		}
		else if (s[(*i)] == '\"')
		{
			if (src->squotes == 1)
				src->ra[src->ra_b++] = s[(*i)];
		}
		else if (s[(*i)] == '\\' && ft_isascii(s[(*i) + 1]) == 1 && src->dquotes == 0 && src->squotes == 0)
			src->ra[src->ra_b++] = s[++(*i)];
		else if (s[(*i)] == '$' && src->squotes == 0 && (ft_isalpha(s[(*i) + 1]) == 1 || s[(*i) + 1] == '?') && src->aslash == 0)
		{
			(*i) = get_env_value_cmd(s, src->our_envp, src, (*i)) - 1;
		}
		else if ((s[(*i)] == '>' || s[(*i)] == '<') && src->aslash == 0 && src->dquotes == 0 && src->squotes == 0)
		{
			while (s[(*i)] == '>' || s[(*i)] == '<') //TEST THIS WITH ls>out1>out2 or >out1>out2 ls
				find_file_name(&i, s, src, head);
			(*i)++;
			return 1 ;
		}
		else if (s[(*i)] == '\\' && src->aslash == 1)
		{
			if (s[(*i) + 1] != '\\')
			{
				src->ra[src->ra_b++] = s[(*i)++];
				src->ra[src->ra_b++] = s[(*i)];
			}				
		}
		else 
			src->ra[src->ra_b++] = s[(*i)];
		return (0);
}

int find_command_two(char *s, t_source *src, int i, t_node *head)
{
	int start;

	start = i;
	start = count_start(s, src, start, &i);
	while (i < start)
	{
		finding_quotes(s, i, src);
		if (find_command_three(s, src, head, &i) == 1)
			continue ;
		i++;
	}
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
	i = find_command_two(s, src, i,head);
	src->ra[src->ra_b] = '\0';
	src->offset = i;
	return (ft_strdup(src->ra));
}