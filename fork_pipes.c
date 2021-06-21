
#	include "minishell.h"
// void	return_fun(void)
// {
// 	if (WIFSIGNALED(g_global.id))
// 		g_global.return_value = WTERMSIG(g_global.id) + 128;
// 	if (WIFEXITED(g_global.id))
// 		g_global.return_value = WEXITSTATUS(g_global.id);
// }

// int	first_child (int in, int *out, t_node *tmp, t_source *src)
// {
// 	int	pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (tmp->first_filename != NULL)
// 			red_open_pipe(tmp->first_filename);
// 		else
// 		{
// 			if (in != 0)
// 			{
// 				dup2 (in, 0);
// 				close (in);
// 			}
// 			if (out[1] != 1)
// 			{
// 				dup2 (out[1], 1);
// 				close (out[1]);
// 				close (out[0]);
// 			}
// 			close(out[0]);
// 		}
// 		command_list(tmp->cmd, tmp->arg, src);
// 		exit(g_global.return_value);
// 	}
// 	return (pid);
// }

// int	inner_childs(int in, int *out, t_pipe *tmp, t_source *src)
// {
// 	int	pid;

// 	pid = fork ();
// 	if (pid == 0)
// 	{
// 		if (tmp->pipef != NULL)
// 			red_open_pipe(tmp->pipef);
// 		else
// 		{
// 			if (in != 0)
// 			{
// 				dup2 (in, 0);
// 				close (in);
// 			}
// 			if (out[1] != 1)
// 			{
// 				dup2 (out[1], 1);
// 				close (out[1]);
// 				close (out[0]);
// 			}
// 			close(out[0]);
// 		}
// 		command_list(tmp->cmd, tmp->arg, src);
// 		exit(g_global.return_value);
// 	}
// 	return (pid);
// }

// void	last_child(int in, int *fd, t_pipe *tmp, t_source *src)
// {
// 	int	x;
// 	int	i;

// 	x = fork();
// 	if (x == 0)
// 	{
// 		if (tmp->pipef != NULL)
// 			red_open_pipe(tmp->pipef);
// 		else
// 		{
// 			dup2 (in, 0);
// 			close(in);
// 			close (fd[0]);
// 		}
// 		command_list(tmp->cmd, tmp->arg, src);
// 		exit(g_global.return_value);
// 	}
// 	close (fd[0]);
// 	i = 0;
// 	while (i < src->npipe + 1)
// 	{
// 		wait(&g_global.id);
// 		i++;
// 		return_fun();
// 	}
// }

// void	fork_pips (int n, t_node *head, t_source *src)
// {
// 	int		i;
// 	int		in;
// 	t_pipe	*tmp;

// 	tmp = head->pipe;
// 	in = 0;
// 	i = 0;
// 	while (i < n - 1)
// 	{
// 		pipe (src->fd);
// 		if (i == 0)
// 			first_child (in, src->fd, head, src);
// 		else
// 		{
// 			if (tmp->next == NULL)
// 				break ;
// 			inner_childs (in, src->fd, tmp, src);
// 			tmp = tmp->next;
// 		}
// 		close (src->fd [1]);
// 		if (i++ != 0)
// 			close(in);
// 		in = src->fd [0];
// 	}
// 	last_child(in, src->fd, tmp, src);
// }

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
		// close(fd);
	}
	return (fd);
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
	int h = -50;
    t_pipe *tmp = head->pipe;
	while (tmp)
	{
		// fprintf(stderr, "current cmd: %s\n", cmd_list->argv[0]);
		fd[0] = -1;
		fd[1] = -1;
		if (tmp->next)
		{
			pipe(fd);
			write_fd = dup(fd[1]);
			close(fd[1]);
		}
		else
		{
			write_fd = dup(1);
		}
		// g_all->ctrl_quit = 1;
		if (fork() == 0)
		{
			if(tmp != NULL && tmp->pipef == NULL)
			{
				dup2(read_fd, 0);
				dup2(write_fd, 1);
		   		close(read_fd);
				close(write_fd);
				if (fd[0] + 1)
					close(fd[0]);
				if (fd[1] + 1)
					close(fd[1]);
			}
			else if(tmp->pipef != NULL)
			{
				// if(check_two_red(tmp) == 0)
				// {
					t_filename *lastnamef = tmp->pipef;
					// t_filename *lastnamef = last_name_func(tmp);
					// if(!lastnamef)
					// 	exit(1);
					// if(check_if_command_is_exist(tmp->filerdr->name, 0) == 3)
					// 	exit(1);
					// fprintf (stderr, "c==%d\n", lastnamef->c);
					// fprintf (stderr, "src==%d\n", src->fd_r_c);
					if (src->fd_r_c == 50)
					{
						// puts ("There 2");
							int fd_input = open(lastnamef->filename, O_RDONLY);
							lastnamef = lastnamef->next;
							int fd_out = open(lastnamef->filename, O_CREAT|O_WRONLY|O_APPEND, 0644);
							if(fd_out == -100)
								exit(1);
							if(fd_input == -100)
								exit(1);
							dup2(fd_input, 0);
							close(fd_input);
							dup2(fd_out, 1);
							close(fd_out);
							// fprintf (stderr, "%s\n", lastnamef->filename);
					}
					else if(lastnamef->c == '<')
					{
						puts ("Hi");
						h = get_last_filename(lastnamef, 1);//open(lastnamef->filename, O_RDONLY);
						dup2(h, 0);
						dup2(write_fd, 1);
						close(h);
					}
					else if(lastnamef->c == '>')
					{
						puts ("There");
						h = get_last_filename(lastnamef, 0);//open(lastnamef->filename,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
						dup2(h, 1);
						dup2(read_fd, 0);
						close(h);
					}
					else if(lastnamef->c == 94)
					{
						puts ("Not");
						h = open(lastnamef->filename, O_CREAT|O_WRONLY|O_APPEND, 0644);
						dup2(h, 1);
						dup2(read_fd, 0);
						close(h);
					}
					fprintf (stderr, "lf==%d\n", lastnamef->fd_r_c);
					fprintf (stderr, "src==%d\n", src->fd_r_c);
				// }
				// else if(check_two_red(tmp) == 1)
				// {
				// 	fd_out = output_ret(tmp);
				// 	if(fd_out == -100)
				// 		exit(1);
				// 	fd_input = input_ret(tmp);
				// 	if(fd_input == -100)
				// 		exit(1);
				// 	dup2(fd_input, 0);
				// 	close(fd_input);
				// 	dup2(fd_out, 1);
				// 	close(fd_out);
				// }
			}
		    command_list(tmp->cmd, tmp->arg, src);
			exit(1);
		}
		else
		{
			//parent
			close(read_fd);
			close(write_fd);
			if (tmp->next)
			{
				read_fd = dup(fd[0]);
				close(fd[0]);
			}
		}
		tmp = tmp->next;
	}
	while (wait(NULL) > 0);

}
