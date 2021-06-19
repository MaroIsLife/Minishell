#include "minishell.h"

void	find_command_four(char *s, t_source *src, int **i, int option)
{
	if (option == 1)
	{
		if (src->dquotes == 1)
			src->ra[src->ra_b++] = s[(**i)];
	}
	else if (option == 2)
	{
		if (src->squotes == 1)
			src->ra[src->ra_b++] = s[(**i)];
	}
	else if (option == 3)
	{
		if (s[(**i) + 1] != '\\')
		{
			src->ra[src->ra_b++] = s[(**i)++];
			src->ra[src->ra_b++] = s[(**i)];
		}
	}
}

int	find_command_three(char *s, t_source *src, t_node *head, int *i)
{
	if (s[(*i)] == '\'')
		find_command_four(s, src, &i, 1);
	else if (s[(*i)] == '\"')
		find_command_four(s, src, &i, 2);
	else if (s[(*i)] == '\\' && ft_isascii(s[(*i) + 1]) == 1
		&& src->dquotes == 0 && src->squotes == 0)
		src->ra[src->ra_b++] = s[++(*i)];
	else if (s[(*i)] == '$' && src->squotes == 0 && (ft_isalpha(s[(*i) + 1])
			== 1 || s[(*i) + 1] == '?') && src->aslash == 0)
		(*i) = get_env_value_cmd(s, src->our_envp, src, (*i)) - 1;
	else if ((s[(*i)] == '>' || s[(*i)] == '<') && src->aslash == 0
		&& src->dquotes == 0 && src->squotes == 0)
	{
		while (s[(*i)] == '>' || s[(*i)] == '<')
			find_file_name(&i, s, src, head);
		(*i)++;
		return (1);
	}
	else if (s[(*i)] == '\\' && src->aslash == 1)
		find_command_four(s, src, &i, 3);
	else
		src->ra[src->ra_b++] = s[(*i)];
	return (0);
}

int	find_command_two(char *s, t_source *src, int i, t_node *head)
{
	int	start;

	start = i;
	src->ctmp = ft_strdup("");
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
	int	i;
	int	start;
	int	file_found;

	file_found = 0;
	i = src->offset;
	while (s[i] == ' ' || s[i] == '|')
		i++;
	start = i;
	src->ctmp = ft_strdup("");
	start = count_start(s, src, start, &i);
	src->ra = malloc((4096) * sizeof(char));
	i = find_command_two(s, src, i, head);
	src->ra[src->ra_b] = '\0';
	src->offset = i;
	return (ft_strdup(src->ra));
}
