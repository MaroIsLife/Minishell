
#	include "minishell.h"

int 	get_last_filename(t_filename *tmp, int i)
{
	int fd;

	fd = -99;
	while (tmp)
	{
		if (i == 0)
			fd = open(tmp->filename, O_CREAT|O_WRONLY|O_APPEND, 0644);
		else
			fd = open(tmp->filename, O_RDONLY);
		if (tmp->next == NULL)
			return (fd);
		tmp = tmp->next;
	}
	return (fd);
}
void both_red(t_filename *tmp)
{
	int fd_input = open(tmp->filename, O_RDONLY);
	tmp = tmp->next;
	int fd_out = open(tmp->filename, O_CREAT|O_WRONLY|O_APPEND, 0644);
	if(fd_out == -100)
		exit(1);
	if(fd_input == -100)
		exit(1);
	dup2(fd_input, 0);
	close(fd_input);
	dup2(fd_out, 1);
	close(fd_out);
}

void red_open_normal(int write_fd, t_filename *tmp)
{
	int h;

	h = get_last_filename(tmp, 1);//open(lastnamef->filename, O_RDONLY);
	dup2(h, 0);
	dup2(write_fd, 1);
	close(h);
}
void red_read (int read_fd, t_filename *tmp)
{
	int h;

	h = get_last_filename(tmp, 0);//open(lastnamef->filename,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(h, 1);
	dup2(read_fd, 0);
	close(h);
}
void red_open_append(int read_fd, t_filename *tmp)
{
	int h;

	h = open(tmp->filename, O_CREAT|O_WRONLY|O_APPEND, 0644);
	dup2(h, 1);
	dup2(read_fd, 0);
	close(h);
}
void red_spawn(t_pipe *tmp, int write_fd, int read_fd, t_source *src)
{
	t_filename *lastnamef = tmp->pipef;
	if (src->fd_r_c == 50)
			both_red(lastnamef);
	else if(lastnamef->c == '<')
		red_open_normal(write_fd, lastnamef);
	else if(lastnamef->c == '>')
		red_read(read_fd, lastnamef);
	else if(lastnamef->c == 94)
		red_open_append(read_fd, lastnamef);
}
void fork_pips (int n, t_node *head, t_source *src)
{
    int i;
	int fd[2];
	int read_fd;
	int write_fd;
	
	i = 0;
	read_fd = dup(0);
	n = 1;
    t_pipe *tmp = head->pipe;
	/**
	 *  make head-> cmd into pipe->cmd;
	 * **/
	while (tmp)
	{
		fd[0] = -1;
		fd[1] = -1;
		if (i == 0 || tmp->next)
		{
			pipe(fd);
			write_fd = dup(fd[1]);
			close(fd[1]);
		}
		else
			write_fd = dup(1);
		if (fork() == 0)
		{
			if(tmp != NULL && tmp->pipef == NULL)
			{
				dup2(read_fd, 0);
				dup2(write_fd, 1);
		   		close(read_fd);
				close(write_fd);
			}
			else if(tmp->pipef != NULL)
			{
				red_spawn(tmp, write_fd, read_fd, src);

			}
			if (i == 0)
				command_list(head->cmd, head->arg, src);
			else
				command_list(tmp->cmd, tmp->arg, src);
			exit(g_global.return_value);
		}
		else
		{
			close(read_fd);
			close(write_fd);
			if (i == 0 || tmp->next)
			{
				read_fd = dup(fd[0]);
				close(fd[0]);
			}
		}
		if (i > 0)
			tmp = tmp->next;
		i++;
	}
	while (wait(NULL) > 0);
}
