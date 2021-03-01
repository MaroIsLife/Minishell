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
			if (head->arg[1] == NULL)
				break ;
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

char	*get_env_name(t_node *head, t_source *src, char **envp, int offset)
{
	int i;
	int c;
	char *s;

	c = 0;
	i = 0;

	s = malloc(1024 * sizeof(char));
	while (envp[i] != NULL)
	{
		if (envp[i][0] == head->arg[offset][0])
		{
			while (envp[i][c] == head->arg[offset][c])
			{
				if (head->arg[offset][c] == '=')
				{	
					s[c] = '\0';
					return (s);
				}
				s[c] = head->arg[offset][c];
				c++;
			}
		}
		i++;
	}
	return (NULL);
}

char	*get_env_value(t_node *head, t_source *src, char **envp, int offset)
{
	int		i;
	int		c;
	char	*s;
	int		b;

	c = 0;
	i = 0;
	b = 0;

	s = malloc(1024 * sizeof(char));
	while (envp[i] != NULL)
	{
		if (envp[i][0] == head->arg[offset][0])
		{
			while (envp[i][c] == head->arg[offset][c])
			{
				if (head->arg[offset][c++] == '=')
				{	
					while (head->arg[offset][c] != '\0')
						s[b++] = head->arg[offset][c++];

					s[b] = '\0';
					return (s);
				}
			}
		}
		i++;
	}
	return (NULL);
}

void	ft_export(t_node *head, t_source *src, char **envp)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	if (head->arg[i] == NULL)
		ft_putstr_fd("Printing export",1);
	else 
	{
		while (head->arg[i] != NULL)
		{	
			value = get_env_value(head, src, envp, i);
			name = get_env_name(head, src, envp, i);
			printf("%s %s\n",value,name);
			envp[src->lastenv] = head->arg[i];
			src->lastenv++;
			envp[src->lastenv] = NULL;
			i++;
		}
			// free(value);
			// free(name);
	}
}