#include "minishell.h"

void	red_spawn(t_pipe *tmp, int write_fd, int read_fd, t_source *src)
{
	t_filename	*lastnamef;

	lastnamef = tmp->pipef;
	if (src->fd_r_c == 50)
		both_red(lastnamef);
	else if (lastnamef->c == '<')
		red_open_normal(write_fd, lastnamef);
	else if (lastnamef->c == '>')
		red_read(read_fd, lastnamef);
	else if (lastnamef->c == 94)
		red_open_append(read_fd, lastnamef);
}

void	child_exec(t_pipe *tmp, t_node *head, t_source *src)
{
	if (tmp != NULL && tmp->pipef == NULL)
	{
		dup2(src->read_fd, 0);
		dup2(src->write_fd, 1);
		close(src->read_fd);
		close(src->write_fd);
	}
	else if (tmp->pipef != NULL)
	{
		red_spawn(tmp, src->write_fd, src->read_fd, src);
	}
	if (src->i == 0)
		command_list(head->cmd, head->arg, src);
	else
		command_list(tmp->cmd, tmp->arg, src);
	exit(g_global.return_value);
}

void	return_fun(int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		wait(&g_global.id);
		i++;
		if (WIFSIGNALED(g_global.id))
			g_global.return_value = WTERMSIG(g_global.id) + 128;
		if (WIFEXITED(g_global.id))
			g_global.return_value = WEXITSTATUS(g_global.id);
	}
}

void	pipe_close_nrm(int i, t_source *src)
{
	if (i == 0)
	{
		pipe(src->fd);
		src->write_fd = dup(src->fd[1]);
		close(src->fd[1]);
	}
	else if (i == 1)
	{
		src->read_fd = dup(src->fd[0]);
		close(src->fd[0]);
	}
	else
	{
		close(src->read_fd);
		close(src->write_fd);
	}
}

void	fork_pips (int n, t_node *head, t_source *src)
{
	t_pipe	*tmp;

	src->i = 0;
	src->read_fd = dup(0);
	tmp = head->pipe;
	while (tmp)
	{
		if (src->i == 0 || tmp->next)
			pipe_close_nrm(0, src);
		else
			src->write_fd = dup(1);
		if (fork() == 0)
			child_exec(tmp, head, src);
		else
		{
			pipe_close_nrm(69, src);
			if (src->i == 0 || tmp->next)
				pipe_close_nrm(1, src);
		}
		if (src->i > 0)
			tmp = tmp->next;
		src->i++;
	}
	return_fun(n);
}
