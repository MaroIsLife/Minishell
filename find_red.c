#	include "minishell.h"

void	find_red_two(t_source *src, int option)
{
	if (option == 1)
	{
		if (src->fd_r_c == 2)
		{
			puts("Here 4");
			src->fd_r_c = 50;
		}
		else if (src->fd_r_c == 3)
			src->fd_r_c = 51;
		else if (src->fd_r_c != 50)
		{
			src->fd_r_c = 1;
			puts("Here 5");
		}
	}
	else if (option == 2)
	{
		if (src->fd_r_c == 1)
		{
			puts("here 1");
			src->fd_r_c = 50;
		}
		else if (src->fd_r_c == 0)
		{
			puts("Here 2");
			src->fd_r_c = 2;
		}
	}
	else if (option == 3)
	{
		if (src->fd_r_c == 1)
			src->fd_r_c = 51;
		else if (src->fd_r_c == 0)
			src->fd_r_c = 3;
	}
}

void	find_red(int ***i, char *s, t_source *src)
{
	if (s[***i] == '<' && s[***i + 1] == '<')
	{
		find_red_two(src, 3);
		(***i) = (***i) + 2;
		src->p->c = 127;
	}
	else if (s[***i] == '>' && s[***i + 1] == '>')
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

void	find_file_name_six(t_source *src, int i, t_ft *ft, char *s)
{
	if ((s[(i)] == '\"') && src->squotes == 0 && src->aslash == 0)
		;
	else if ((s[(i)] == '\'') && src->dquotes == 0 && src->aslash == 0)
		;
	else if ((s[(i)] == '\\' || s[(i)] == '\"'
			|| s[(i)] == '\'') && src->aslash == 1)
	{
		src->p->filename[ft->b++] = s[(i)];
		src->aslash = 0;
	}
	else if (s[(i)] == '\\' && src->aslash == 0)
	{
		src->tmp = finding_aslash(s, i, src);
		if (src->aslash == 0 && src->tmp != 1)
		{
			src->p->filename[ft->b++] = s[(i)];
			src->tmp = 0;
		}
	}
	else
		src->p->filename[ft->b++] = s[(i)];
}

void	find_file_name_three(int ***i, char *s, t_source *src, t_ft *ft)
{
	if (s[***i] == '$' && src->squotes == 0)
	{
		ft->tmp = ft_strdup("");
		(***i)++;
		while (s[***i] != '\0' && s[***i] != '$')
		{	
			ft->tmp = ft_strdup(ft_strjoinchar(ft->tmp, s[***i]));
			if (ft_search(src->our_envp, ft->tmp)
				&& !ft_isalpha(s[(***i) + 1]))
			{
				ft->rev = get_x_env(src->our_envp, ft->tmp);
				ft->j = 0;
				while (ft->rev[ft->j] != '\0')
					src->p->filename[ft->b++] = ft->rev[ft->j++];
			}
			(***i)++;
		}
	}
	else
	{
		find_file_name_six(src, ***i, ft, s);
		(***i)++;
	}
}

int	find_file_name(int **i, char *s, t_source *src )
{
	t_ft	ft;

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
	ft.b = 0;
	while (s[**i] != '\0' && s[**i] != '\n' && s[**i] != '>' && s[**i] != '<')
	{
		finding_quotes(s, **i, src);
		if (s[**i] == ' ' && src->dquotes == 0 && src->squotes == 0)
			break ;
		find_file_name_three(&i, s, src, &ft);
	}
	src->p->filename[ft.b] = '\0';
	init_filee(src);
	src->allocate = 1;
	return (1);
}
