#	include "minishell.h"

void	print_errno(char *filename)
{
	char	*err;

	err = strerror(errno);
	write(2, "minishell: ", 11);
	write(2, filename, ft_strlen(filename));
	write(2, " ", 1);
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	exit(0);
}

void	red_open_pipe_two(t_filename *p, int *fd, int *fd2)
{
	if (p->fd_r_c == 50)
	{
		dup2((*fd2), 0);
		dup2((*fd), 1);
	}
	else if (p->c == 94 || p->c == '>')
		dup2((*fd), 1);
	else if (p->c == '<')
		dup2((*fd2), 0);
	close((*fd));
	close((*fd2));
}

void	red_open_pipe(t_filename *tmp)
{
	int			fd;
	int			fd2;
	t_filename	*p;

	p = tmp;
	while (1)
	{
		if (p->c == 94)
			fd = open(p->filename, O_RDWR | O_APPEND | O_CREAT, 0777);
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
	red_open_pipe_two(p, &fd, &fd2);
}

void	red_open_two(t_filename *p, int *fd, int *fd2, t_source *src)
{
	if (src->fd_r_c == 50)
	{
		dup2((*fd2), 0);
		dup2((*fd), 1);
	}
	else if (p->c == 94 || p->c == '>')
		dup2((*fd), 1);
	else if (p->c == '<')
		dup2((*fd2), 0);
	close((*fd));
	close((*fd2));
}

void	red_open(t_node *head, t_source *src)
{
	int			fd;
	int			fd2;
	t_filename	*p;

	p = head->first_filename;
	while (1)
	{
		if (p->c == 94)
			fd = open(p->filename, O_RDWR | O_APPEND | O_CREAT, 0777);
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
	red_open_two(p, &fd, &fd2, src);
}
