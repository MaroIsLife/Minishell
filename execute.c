#	include "minishell.h"

char	*get_path(t_source *src, char *cmd, char **args, char **varg)
{
	char	*path;
	char	**s;
	int		index;

	path = NULL;
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		path = ft_strdup(cmd);
	else
	{
		s = get_env_path(src->our_envp, src);
		path = get_correct_path(s, varg);
		index = 0;
		while (s[index])
			free(s[index++]);
		free(s);
	}
	return (path);
}

void	ft_execute_child(char **varg, char *path, t_source *src)
{
	src->tmp = 0;
	g_global.ffork = 1;
	g_global.id = fork();
	if (g_global.id == 0)
	{
		if (execve(path, &varg[0], src->our_envp) == -1)
		{
			print_cmd_error(varg[0], 0, 2);
			while (varg[src->tmp])
				free(varg[src->tmp++]);
			free(varg);
			free(path);
			exit(-1);
		}
	}
	else
	{
		wait(&g_global.id);
		g_global.ffork = 0;
		if (WIFSIGNALED(g_global.id))
			g_global.return_value = WTERMSIG(g_global.id) + 128;
		if (WIFEXITED(g_global.id))
			g_global.return_value = WEXITSTATUS(g_global.id);
	}
}

int	ft_execute(char *cmd, char **args, t_source *src, char **envp)
{
	char			**s;
	char			*path;
	static int		i;
	char			**varg;

	varg = ft_valide_args(cmd, args, calc_args(args));
	if (cmd[0] == '\0')
		return (print_cmd_error(cmd, 1, 1));
	if (get_x_env(src->our_envp, src, "PATH") == 0
		&& (cmd[0] != '/' && cmd[0] != '.'))
		return (print_cmd_error(cmd, 1, 1));
	path = get_path(src, cmd, args, varg);
	if (path != 0)
		ft_execute_child(varg, path, src);
	else
		print_cmd_error(varg[0], 1, 1);
	src->tmp = 0;
	while (varg[src->tmp])
		free(varg[src->tmp++]);
	free(varg);
	free(path);
	return (0);
}
