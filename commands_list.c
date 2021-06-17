#include "minishell.h"

int	print_cmd_error(char *cmd, int option, int message)
{
	if (message == 1)
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
	}
	if (message == 2)
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	if (option == 1)
		g_global.return_value = 127;
	return (0);
}

void	command_list(char *cmd, char **args, t_source *src)
{
	char	*home;

	home = where_home(src);
	if (ft_strncmp(cmd, "cd", 2) == 0 && cmd[2] == '\0')
		ft_cd(args, src, home);
	else if (ft_strncmp(cmd, "echo", 4) == 0 && cmd[4] == '\0')
		ft_echo(args);
	else if (ft_strncmp(cmd, "env", 3) == 0 && cmd[3] == '\0')
		print_env(src);
	else if (ft_strncmp(cmd, "pwd", 3) == 0 && cmd[3] == '\0')
		ft_pwd();
	else if (ft_strncmp(cmd, "export", 6) == 0 && cmd[6] == '\0')
		ft_export(args, src);
	else if (ft_strncmp(cmd, "unset", 5) == 0 && cmd[5] == '\0')
		ft_unset(args, src);
	else if (ft_strncmp(cmd, "exit", 4) == 0 && cmd[4] == '\0')
		ft_exit(args, src);
	else if ((src->dollarused == 1 && cmd[0] == '\0'))
		;
	else
		ft_execute(cmd, args, src, src->our_envp);
	free(home);
}
