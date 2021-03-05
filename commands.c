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

char	*search_env(t_node *head, t_source *src, char **envp, int offset)
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

void 	ft_sort(t_source *src)
{
	//sorting using strcmp with additiong to the counter i

	char *swap;
	int i = 0;
	int j;
	while (i < src->lastexp)
	{
		j = i + 1;
		while(j < src->lastexp)
		{
			if (src->export[i][0] > src->export[j][0])
			{
				swap = src->export[i];
				src->export[i] = src->export[j];
				src->export[j] = swap;
			}
			j++;
		}
		i++;
	}
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
	ft_sort(src);
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
			name = search_env(head, src, envp, i);
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