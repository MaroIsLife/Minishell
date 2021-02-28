#include "minishell.h"

void    ft_echo(t_node *head, t_source *src)
{
	int i;
	int newline;
	
	newline = 0;
	i = 0;
	while (head->arg[i] != NULL)
	{
		if (ft_strncmp(head->arg[0], "-n", 2) == 0)
		{
			i++;
			newline = 1;
		}
		ft_putstr_fd(head->arg[i], 1);
		if (head->arg[i + 1] == NULL)
			break ;
		ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline == 0)
		ft_putstr_fd("\n", 1);
}

void	print_env(t_node *head, t_source *src, char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		ft_putstr_fd(envp[i++], 1);
		ft_putstr_fd("\n", 1);
	}
}

void ft_export(t_node *head, t_source *src, char **envp)
{
	int i;
	int b;
	int c;
	char *s = "abc";

	i = 0;
	b = 0;
	c = 0;
	if (head->arg[i] == NULL)
		ft_putstr_fd("test",1);
	else 
	{	
		envp[src->lastenv] = head->arg[i];
		printf("%s\n",envp[src->lastenv]);
		src->lastenv++;
		envp[src->lastenv] = NULL;

	}

}