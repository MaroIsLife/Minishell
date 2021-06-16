#include "minishell.h"
int	arg_if_space(char *s, int ***i, t_source *src)
{
	if (s[***i] == ' ' && (src->dquotes == 1 || src->squotes == 1))
		src->re[src->re_b++] = s[***i];
	while (s[***i + 1] == ' ' && !(src->dquotes == 0 || src->squotes == 0))
		(***i)++;
	return (***i);
}

int	check_offset(int offset, char *s)
{
	int i = 0;
	
	while (s[i] == ' ')
		i++;
	if (s[i] == '>' || s[i] == '<')
		return (0);
	return (offset);
}

int	count_argument_three(char *s, int **i, t_source *src)
{
	if (s[(**i)] == '\"' && (**i) == 0)
		src->dquotes = 1;
	else if (s[(**i)] == '\'' && (**i) == 0)
		src->squotes = 1;
	else
		finding_quotes2(s, (**i), src);
	if ((s[(**i)] == ';' || s[(**i)] == '|') && (src->dquotes == 0
			&& src->squotes == 0 && src->aslash == 0) && s[(**i) - 1] != '\\')
		return (1);
	else
		return (0);
}

int	count_argument_two(char *s, int *i, int *count, t_source *src)
{
	if (count_argument_three(s, &i, src) == 1)
		return (1);
	if (s[(*i)] == ' ' && src->dquotes == 0 && src->squotes == 0)
	{
		while (s[(*i)] == ' ')
			(*i)++;
		if ((s[(*i)] == '|' || s[(*i)] == ';') && src->dquotes == 0
			&& src->squotes == 0 && src->aslash == 0 && s[(*i) - 1] != '\\')
			return (1);
		if (s[(*i)] == '\0' || s[(*i)] == '\n')
			return (1);
		if (s[(*i)] != '>' && s[(*i)] != '<' && src->tmp == 0)
			(*count)++;
		else
			src->tmp = 0;
	}
	else if (s[(*i)] == '>' || s[(*i)] == '<')
	{
		(*count)++;
		src->tmp = 1;
		(*i)++;
	}
	else
		(*i)++;
	return (0);
}

int		count_argument(char *s, int offset, t_source *src) //CONVERT TO SPLIT?
{
	int	i;
	int	jump;
	int	count;

	i = src->offset;
	count = 0;
	jump = 0;
	if (s[0] == '\n')
		return (0);
	if (i < 0)
		return (0);
	if (s[i] == '|')
		return (0);
	src->tmp = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		if (count_argument_two(s, &i, &count, src) == 1)
			return (count);
	}
	return(count);
}

void	find_red_two(t_source *src, int option)
{
	if (option == 1)
	{
		if (src->fd_r_c == 2)
			src->fd_r_c = 50;
		else if (src->fd_r_c != 50)
			src->fd_r_c = 1;
	}
	else if (option == 2)
	{
		if (src->fd_r_c == 1)
			src->fd_r_c = 50;
		else if (src->fd_r_c == 0)
			src->fd_r_c = 2;
	}
}

void	find_red(int ***i, char *s, t_source *src)
{
	if (s[***i] == '>' && s[***i + 1] == '>')
	{
		find_red_two(src, 1);
		src->p->c = 94;
		(***i) = (***i) + 2;
	}
	else if (s[***i] == '>')
	{
		find_red_two(src, 1);
		(***i)++;
		src->p->c = '>';
	}
	else if (s[***i] == '<')
	{
		find_red_two(src, 2);
		(***i)++;
		src->p->c = '<';
	}
}

void	find_file_name_three(int ***i, char *s, t_source *src, t_filetmp *filetmp)
{
	if (s[***i] == '$' && src->squotes == 0)
	{
		filetmp->tmp = ft_strdup("");
		(***i)++;
		while (s[***i] != '\0' && s[***i] != '$')
		{	
			filetmp->tmp = ft_strdup(ft_strjoinchar(filetmp->tmp, s[***i]));
			if (ft_search(src->our_envp, filetmp->tmp)
				&& !ft_isalpha(s[(***i) + 1]))
			{
				filetmp->rev = get_x_env(src->our_envp, src, filetmp->tmp);
				filetmp->j = 0;
				while (filetmp->rev[filetmp->j] != '\0')
				{	
					src->p->filename[filetmp->b] = filetmp->rev[filetmp->j];
					filetmp->j++;
					filetmp->b++;
				}
			}
			(***i)++;
		}
	}
	else
		src->p->filename[filetmp->b++] = s[(***i)++];
}

int		find_file_name(int **i, char *s, t_source *src, t_node *head)
{
	t_filetmp	filetmp;

	src->tmp2 = 1;
	if (src->allocate == 1)
	{
		src->p->next = (t_filename *) malloc(sizeof(t_filename));
		src->p->next->next = NULL;
		src->p = src->p->next;
	}
	find_red(&i, s, src);
	while (s[**i] == ' ')
		(**i)++;
	src->p->filename = malloc((4096 + 1) * sizeof(char));
	filetmp.b = 0;
	while (s[**i] != '\0' && s[**i] != '\n' && s[**i] != '>' && s[**i] != '<')
	{
		finding_quotes(s, **i, src);
		if (s[**i] == ' ' && src->dquotes == 0 && src->squotes == 0)
			break ;
		find_file_name_three(&i, s, src, &filetmp);
	}
	src->p->filename[filetmp.b] = '\0';
	init_filee(src);
	src->allocate = 1;
	return (1);
}

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

int		find_argument_four(char *s, t_source *src, int **i, int option)
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
		else
			return (2);
	}
		return (0);
}

int		find_argument_three(char *s, t_source *src, int *i, t_node *head)
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

int		find_argument_two(char *s, t_source *src, int i, t_node *head)
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
	{
		printf("Error\n");
		printf("Dquotes: %d, Squotes: %d, Aslash: %d\n", src->dquotes,
			src->squotes, src->aslash);
	}
	src->offset = i;
	src->re[src->re_b] = '\0';
	return ((src->re));
}
