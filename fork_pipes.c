#	include "minishell.h"

int 	get_last_filename(t_filename *tmp, int i)
{
	int	fd;

	fd = -99;
	while (tmp)
	{
		if (i == 0)
			fd = open(tmp->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(tmp->filename, O_RDONLY);
		if (tmp->next == NULL)
			return (fd);
		tmp = tmp->next;
	}
	return (fd);
}

void	both_red(t_filename *tmp)
{
	int	fd_input;
	int	fd_out;

	fd_input = open(tmp->filename, O_RDONLY);
	tmp = tmp->next;
	fd_out = open(tmp->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
		exit(1);
	if (fd_input == -1)
		exit(1);
	dup2(fd_input, 0);
	close(fd_input);
	dup2(fd_out, 1);
	close(fd_out);
}

void	red_open_normal(int write_fd, t_filename *tmp)
{
	int	file;

	file = get_last_filename(tmp, 1);
	dup2(file, 0);
	dup2(write_fd, 1);
	close(file);
}

void	red_read (int read_fd, t_filename *tmp)
{
	int	file;

	file = get_last_filename(tmp, 0);
	if (file == -1)
		exit(1);
	dup2(file, 1);
	dup2(read_fd, 0);
	close(file);
}

void	red_open_append(int read_fd, t_filename *tmp)
{
	int	file;

	file = open(tmp->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (file == -1)
		exit(1);
	dup2(file, 1);
	dup2(read_fd, 0);
	close(file);
}
