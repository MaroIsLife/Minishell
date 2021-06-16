#include "minishell.h"

int		count_start_two(char *s, t_source *src, int *start, int **i)
{
	char *tmp;

	finding_quotes(s, ++(*start), src);
	if (src->squotes == 1 || src->dquotes == 1)
	{
		(*start)++;
		(**i) = (*start);
		return (1);
	}
	while (s[*start] != '\0' && s[*start] != '$' && s[*start] != ' ')
	{
		tmp = src->ctmp;
		src->ctmp = ft_strjoinchar(src->ctmp, s[*start]);
		free(tmp);
		(*start)++;
	}
	if (get_x_env(src->our_envp, src, src->ctmp) == 0)
	{
		free(src->ctmp);
		src->ctmp = ft_strdup("");
		while (s[*start] == ' ')
			(*start)++;
		(**i) = (*start);
		src->dollarused = 1;
		return (1);
	}
	// free(src->ctmp);
	return (0);
}

void    count_start_three(char *s, t_source *src, int *start, int *file_found)
{
            if (s[(*start) + 1] == '>')
				(*start) = (*start) + 2;
			else
				(*start)++;
			while (s[(*start)] == ' ')
				(*start)++;
			while (s[(*start)] != ' ' && s[(*start)] != '\0')
				(*start)++;
			(*file_found) = 1;
}

int		count_start(char *s, t_source *src, int start, int *i)
{
	int		file_found;

	src->ctmp = ft_strdup("");
	while (s[start] != '\0' && s[start] != '\n')
	{
		finding_quotes(s, start, src);
		if (s[start] == '$' && src->squotes == 0 && src->dquotes == 0 && s[start + 1] != '?')
		{
			if(count_start_two(s, src, &start, &i) == 1)
				continue;
		}
		if (s[start] == '>' || s[start] == '<')
            count_start_three(s, src, &start, &file_found);
		if ((s[start] == ' ' || s[start] == '|') && src->dquotes == 0 && src->squotes == 0 && file_found == 0)
			break ;
		else
			file_found = 0;
		if (s[start] != '\0')
			start++;
	}
	src->ra_b = 0;
	free(src->ctmp);
	src->ctmp = NULL;
	return (start);
}