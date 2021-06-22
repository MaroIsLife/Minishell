#include "minishell.h"

void	here_doc(int fd3, char *filename)
{
	char	*s;
	char	*tmp;

	while (1)
	{
		s = readline("> ");
		tmp = s;
		s = ft_strjoinchar(s, '\n');
		free(tmp);
		if (ft_strncmp(s, filename, ft_strlen(filename)) == 0)
		{
			free(s);
			break ;
		}
		write(fd3, s, ft_strlen(s));
		free(s);
	}
}

void	here_doc_two(int fd3, char *filename)
{
	fd3 = open("/tmp/tmp1", O_RDWR | O_TRUNC | O_CREAT, 0777);
	here_doc(fd3, filename);
	close(fd3);
}

void	red_open(t_node *head, t_source *src)
{
	int			fd;
	int			fd2;
	int			fd3;
	t_filename	*p;

	p = head->first_filename;
	fd3 = 0;
	while (1)
	{
		if (p->c == 94)
			fd = open(p->filename, O_RDWR | O_APPEND | O_CREAT, 0777);
		else if (p->c == 127)
			here_doc_two(fd3, p->filename);
		else if (p->c == '>')
			fd = open(p->filename, O_RDWR | O_TRUNC | O_CREAT, 0777);
		else if (p->c == '<')
			fd2 = open(p->filename, O_RDONLY);
		if (fd == -1 || fd2 == -1)
			print_errno(p->filename);
		if (p->next == NULL)
			break ;
		p = p->next;
	}
	src->tmp = open("/tmp/tmp1", O_RDONLY, 0644);
	red_open_two(p, &fd, &fd2, src);
}
