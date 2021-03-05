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
void ft_wr_eq(char *s)
{
	int i = 0;
	int sign = 0;
	while (s[i])
	{
		if (s[i] == '=')
			{
				sign = 1;
				write(1,&s[i++], 1);
				write(1,"\"",1);
			}
		write(1,&s[i], 1);
	i++;
		if (!s[i] && sign == 1)
				write(1,"\"",1);
	}

}
void em_export (t_source *src)
{

	int i = 0;
	while (src->export[i] != NULL)
		{
			write (1, "declare -x ", 11);
			ft_wr_eq(src->export[i++]);
			write(1,"\n",1);
		}
}
void	ft_export(t_node *head, t_source *src, char **envp)
{
	int		i;
	char	*name;
	int		length;
	int		c;

	i = 0;
	if (head->arg[i] == NULL)
		em_export( src);

		//write normal until you reach '=' then add ""
		//store garbage to print here
	else 
	{
		while (head->arg[i] != NULL)
		{	
			name = get_env_name(head, src, envp, i);
			length = 0;
			while (head->arg[i][length] != '=' && head->arg[i][length] != '\0')
				length++;
			if (name != 0)
			{
				c = 0;
				while (envp[c] != NULL)
				{
					if (ft_strncmp(envp[c],head->arg[i], length) == 0 && head->arg[i][length == '='])
					{
						envp[c] = head->arg[i];
						if (c == src->lastenv)
							envp[c] = NULL;
					}
					c++;
				}
			}
			else
			{
				if (head->arg[i][length] == '=')
				{
					envp[src->lastenv] = head->arg[i];
					src->export[src->lastexp] = head->arg[i];
					src->lastenv++;
					src->lastexp++;
					envp[src->lastenv] = NULL;
				}
				else 
				{
					src->export[src->lastexp] = head->arg[i];
					src->lastexp++;
					src->export[src->lastexp] = NULL;
				}
				// else head got to export
			}
				i++;
		}
			free(name);
	}
}