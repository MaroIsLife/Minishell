#include "minishell.h"

void	ft_exit_two(char **args, int ret)
{
	ret = ft_atoi(args[0]);
	if (ret > 255)
	{
		write(1, "exit\n", 6);
		exit(ret % 256);
	}
	else if (ret < 0)
	{
		write(1, "exit\n", 6);
		exit (ret + 256);
	}
	else
	{
		write(1, "exit\n", 6);
		exit(ret);
	}
}

int	ft_exit(char **args, t_source *src)
{
	int	b;
	int	ret;

	b = 0;
	if (args[0] == NULL)
		exit(g_global.return_value);
	while (args[0][b] != '\0')
	{
		if (ft_isdigit(args[0][b]) != 1)
		{
			printf("exit\nminishell: exit: ");
			printf("%s: numeric argument required\n", args[0]);
			exit(255);
		}
		b++;
	}
	if (args[1] != NULL)
	{
		printf("exit\nminishell: exit: too many arguments\n");
		g_global.return_value = 1;
		return (0);
	}
	ft_exit_two(args, ret);
	return (0);
}
