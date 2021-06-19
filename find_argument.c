#include "minishell.h"

void	find_argument_five(char *s, t_source *src, int ***i, int option)
{
	int	o;

	o = (***i);
	if (option == 1)
	{
		src->tmp = finding_aslash(s, o, src);
		if (src->aslash == 0 && src->tmp != 1)
		{
			src->re[src->re_b++] = s[(***i)];
			src->tmp = 0;
		}
	}
	else if (option == 2)
	{
		src->re[src->re_b++] = s[(***i)];
		src->aslash = 0;
	}
}

int	find_argument_four(char *s, t_source *src, int **i, int option)
{
	if (option == 1)
		find_argument_five(s, src, &i, 1);
	else if (option == 2)
		find_argument_five(s, src, &i, 2);
	else if (option == 3)
	{
		if (s[(**i)] == ' ' && (src->dquotes == 1 || src->squotes == 1))
		{
			arg_if_space(s, &i, src);
			return (0);
		}
		else if (s[(**i)] == ' ' && (src->dquotes == 0 || src->squotes == 0)
			&& (s[(**i) + 1] != '>' && s[(**i) + 1] != '<'))
			return (2);
	}
	else if (option == 4)
	{
		if (src->squotes == 1)
		{
			src->re[src->re_b++] = s[(**i)];
			return (0);
		}
		return (2);
	}
	return (0);
}

int	find_argument_three(char *s, t_source *src, int *i, t_node *head)
{
	if ((s[(*i)] == '>' || s[(*i)] == '<')
		&& src->aslash == 0 && src->dquotes == 0 && src->squotes == 0)
		return (find_file_name(&i, s, src, head));
	else if (s[(*i)] == ' ')
		return (find_argument_four(s, src, &i, 3));
	else if ((s[(*i)] == '|' || s[(*i)] == ';')
		&& (src->dquotes == 0 && src->aslash == 0))
		return (find_argument_four(s, src, &i, 4));
	else if ((s[(*i)] == '\"') && src->squotes == 0 && src->aslash == 0)
		finding_quotes(s, (*i), src);
	else if ((s[(*i)] == '\'') && src->dquotes == 0 && src->aslash == 0)
		finding_quotes(s, (*i), src);
	else if (s[(*i)] == '$' && src->aslash == 0 && (ft_isalpha(s[(*i) + 1]) == 1
			|| s[(*i) + 1] == '?') && src->squotes == 0)
		(*i) = get_env_value_arg(s, src->our_envp, src, (*i)) - 1;
	else if (s[(*i)] == '\\' && src->aslash == 0)
		find_argument_four(s, src, &i, 1);
	else if ((s[(*i)] == '\"' || s[(*i)] == '\'' || s[(*i)] == '\\' || s[(*i)]
			 == ';' || s[(*i)] == '|' || s[(*i)] == '$' || s[(*i)] == '>'
			|| s[(*i)] == '<') && src->aslash == 1)
		find_argument_four(s, src, &i, 2);
	else
		src->re[src->re_b++] = s[(*i)];
	return (0);
}

int	find_argument_two(char *s, t_source *src, int i, t_node *head)
{
	int	a;

	while (s[i] != '\n' && s[i] != '\0')
	{
		a = find_argument_three(s, src, &i, head);
		if (a == 1)
			continue ;
		else if (a == 2)
			break ;
		i++;
	}
	return (i);
}

char	*find_argument(char *s, t_node *head, t_source *src, char **envp)
{
	int		i;
	char	*re;

	i = src->offset;
	while (s[i] == ' ')
		i++;
	src->re = malloc((4096) * sizeof(char));
	src->re_b = 0;
	i = find_argument_two(s, src, i, head);
	if (src->dquotes == 1 || src->squotes == 1 || src->aslash == 1)
		;
	src->offset = i;
	src->re[src->re_b] = '\0';
	return ((src->re));
}
