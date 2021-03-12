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
		ft_putstr_fd(envp[i], 1);
		if (envp[i][0] != '\0')
			ft_putstr_fd("\n", 1);
		i++;
	}

}

char	*where_home(char **envp)
{
	int i = 0;
	char *home;
	
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
		{
			home = malloc (ft_strlen(envp[i] + 5) + 1);
			ft_strlcpy(home, envp[i] + 5, ft_strlen(envp[i] + 5) + 1);
			return (home);
		}
	i++;
	}
	return (0);
}
void	ft_pwd (void)
{
	char* s = malloc (100);

	printf ("%s\n",getcwd(s, 100));
	free (s);
}
void	ft_cd(t_node *head, char *home)
{
	int sign;

	sign = 0;
	if (!head->arg[0])
		{
			chdir(home);
			free(home);
		}
	else
		sign = chdir(head->arg[0]);
	if (sign != 0)
		printf ("Error: %s\n", strerror(errno));
}

// char	*search_env(t_node *head, t_source *src, char **envp, int offset)
// {
// 	int i;
// 	int c;
// 	char *s;

// 	c = 0;
// 	i = 0;

// 	s = malloc(1024 * sizeof(char));
// 	while (envp[i] != NULL)
// 	{
// 		if (envp[i][0] == head->arg[offset][0])
// 		{
// 			while (envp[i][c] == head->arg[offset][c])
// 			{
// 				if (head->arg[offset][c] == '=')
// 				{	
// 					s[c] = '\0';
// 					return (s);
// 				}
// 				s[c] = head->arg[offset][c];
// 				c++;
// 			}
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }



void 	ft_sort(t_source *src)
{
	//sorting using strcmp with additiong to the counter i

	char *swap;
	int i = 0;
	int j;
	int n;
	while (i < src->lastexp && src->export[i] != NULL)
	{
		j = i + 1;
		while(j < src->lastexp &&  src->export[j] != NULL)
		{
			if (src->export[i][0] > src->export[j][0])
			{
				swap = src->export[i];
				src->export[i] = src->export[j];
				src->export[j] = swap;
			}
			if (src->export[i][0] == src->export[j][0])
			{
				n = 1;
				while (src->export[i][n] != '\0')
				{
					if (src->export[i][n] > src->export[j][n])
					{
						swap = src->export[i];
						src->export[i] = src->export[j];
						src->export[j] = swap;
					}
					n++;
				}
			}
			j++;
		}
		i++;
	}
}
void ft_wr_eq(char *s)
{
	if (s != NULL)
	{	int i = 0;
		int sign = 0;
		while (s[i] != 0)
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
}
void	em_export(t_source *src)
{

	int i = 0;
	ft_sort(src);
	while (src->export[i] != NULL)
		{
			write (1, "declare -x ", 11);
			ft_wr_eq(src->export[i]);
			if (src->export[i][0] != '\0')
				write(1,"\n",1);
			i++;
		}
}
int ft_strlen_eq(char *src)
{
	int i;

	i = -1;
	while (src[++i])
		if (src[i]== '=')
			break ;
	return (i);
}

int found_eq(char *src)
{
	int i;

	i = -1;
	while (src[++i])
		if (src[i]== '=')
			return(1);
	return (0);
}
int ft_search(t_source *src, char *value, int size)
{
	int i;

	i = 0;
	while (src->export[i] != NULL)
	{
		if (ft_strncmp(src->export[i], value, size) == 0)
			return(1);
		i++;
	}
	return (0);
}

void	replace_env(char **envp, t_source *src, char *value, int size)
{
	int i;
	int del;

	del = 0;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], value, size) == 0)
			{
				del = 1;
				envp[i] = value;
				break ;
			}
		i++;
	}
	if (!del)
	{
		envp[src->lastenv++] = value;
		envp[src->lastenv] = NULL;
	}
}
void	ft_export(t_node *head, t_source *src, char **envp)
{
	int		i;
	int		j;
	int		found;
	int		length;
	
	i = 0;
	if (head->arg[i] == NULL)
		em_export(src);
	else
	{
		while (head->arg[i] != NULL)
		{	
			length = ft_strlen_eq(head->arg[i]);
			found = ft_search(src,head->arg[i], length);
			if (found)
			 {
				 j = 0;
				while (src->export[j] != NULL)
				{
					if (ft_strncmp(src->export[j], head->arg[i], length) == 0)
					{
						src->export[j] = head->arg[i];
						replace_env(envp, src, head->arg[i], length);
						if (j == src->lastexp)
							src->export[++j] = NULL;
					}
					j++;
				}
			 
			 }
			else
			{

				if (found_eq(head->arg[i]))
				{
					envp[src->lastenv++] = head->arg[i];
					src->export[src->lastexp++] = head->arg[i];
					src->export[src->lastexp] = NULL;
					envp[src->lastenv] = NULL;
				}
				else
				{
					src->export[src->lastexp++] = head->arg[i];
					src->export[src->lastexp] = NULL;
				}
			}
				i++;
		}
	}
}


int		ft_unset(t_node *head, t_source *src, char **envp)
{
	int i;
	int c;
	int b;

	i = 0;
	c = 0;
	while (head->arg[i] != NULL)
	{
		c = 0;
		while (envp[c] != NULL)
		{
			b = 0;
			while (envp[c][b] != '=' && envp[c][b] != '\0')
				b++;
			if ((ft_strncmp(envp[c],head->arg[i], b)) == 0)
				envp[c][0] = '\0';
			c++;
		}
		c = 0;
		while (src->export[c] != '\0')
		{
			b = 0;
			while (src->export[c][b] != '=' && src->export[c][b] != '\0')
				b++;
			if ((ft_strncmp(src->export[c],head->arg[i], b)) == 0)
				src->export[c][0] = '\0';
			c++;
		}
		i++;
	}
	return (0);
}