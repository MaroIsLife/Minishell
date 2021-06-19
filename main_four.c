#include "minishell.h"

void	ms_free(t_var *var)
{
	int	n;

	n = 0;
	while (var->pipes[n] != NULL)
	{
		free(var->pipes[n]);
		n++;
	}
	free(var->pipes);
}

int	ms_free_two(char *cmd)
{
	if (ft_strncmp(cmd, "continue", 8) == 0)
	{
		return (1);
	}
	if (cmd[0] == ';' || cmd[0] == '\0')
	{
		write (2, "minishell : syntax error near unexpected token `;'\n", 51);
		free(cmd);
		free(g_global.ret);
		return (1);
	}
	return (0);
}
