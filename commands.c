#include "minishell.h"

int	check_bs(char *n)
{
	int	i;

	i = 1;
	while (n[i] != 0)
	{
		if (n[0] != '-')
			return (2);
		if (n[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_print_args(char **args, int i)
{
	ft_putstr_fd(args[i], 1);
	if (args[i + 1])
		ft_putchar_fd(' ', 1);
}

void	ft_echo(char **args)
{
	int	i;
	int	nl;
	int	val_arg;

	i = 0;
	val_arg = 0;
	nl = 0;
	while (args && args[i] != NULL)
	{
		if (args[i][0] == '-')
		{
			if (!check_bs(args[i]) && !val_arg)
			{
				nl = 1;
				i++;
				if (args[i] && check_bs(args[i]))
					val_arg = 1;
				continue ;
			}
			val_arg = 2;
		}
		ft_print_args(args, i++);
	}
	if (nl == 0)
		ft_putchar_fd('\n', 1);
}
