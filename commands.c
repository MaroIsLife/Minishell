
#include "minishell.h"
void    ft_echo(t_node *head, t_source *src)
{
	int i;
	int newline;
	
	newline = 0;
	i = 0;
	while (head->arg[i] != NULL)
	{
		if (ft_strncmp(head->arg[0], "-n", 2) == 0 && head->arg[0][2] == '\0')
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
int ft_strlen_eq(char *src)
{
	int i;

	i = -1;
	while (src[++i])
		if (src[i]== '=')
			break ;
	return (i);
}

void	replace_env(char **envp, t_source *src, char *value)
{
	int i;

	i = 0;
	while (src->our_envp[i] != NULL)
	{
		if (ft_strncmp(value, src->our_envp[i], ft_strlen_eq(value)) == 0)
			{
				src->our_envp[i] = ft_strdup(value);
				if (i == src->lastenv)
					src->our_envp[i] = NULL;
			}
		i++;
	}
}

int arg_counter(char **src)
{
	int i;

	i = 0;
	while (src[i] != NULL)
		i++;
	return (i);
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
void	ft_cd(t_node *head, char *home, char **envp)
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
	change_pwd_env(envp);
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
				while (src->export[j][n] != '\0' && src->export[i][n] != '\0')
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
			if (s[i] == '=' && s[i + 1])
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


int found_eq(char *src)
{
	if (src)
	{
		int i;

		i = -1;
		while (src[++i])
			if (src[i]== '=')
				return(1);
	}
		return (0);
}
int ft_search(char **src, char *value)
{
	int i;

	i = 0;
	while (src[i] != NULL)
	{
		
		if (ft_strncmp(src[i], value,ft_strlen_eq(value)) == 0)
			return(1);
		i++;
	}
	return (0);
}


int 	check_exsyn(char *src)
{
	if (src[0] >= '0' && src[0] <= '9')
		return (1);
	return (0);
}

void 	ft_expn_add(char *add, t_source *src ,char **envp)
{
	int id;

	
	id = found_eq(add);
	if (id)
		{
			envp[src->lastenv++] = add;
			src->export[src->lastexp++] = add;
			src->export[src->lastexp] = NULL;
			envp[src->lastenv] = NULL;
		}
	else
		{
			src->export[src->lastexp++] = add;
			src->export[src->lastexp] = NULL;
		}
}

void	ft_expn_chng(char *add, t_source *src ,char **envp)
{
	int i;

	i = 0;
	while (src->export[i] != NULL)
	{
		if (ft_strncmp(add, src->export[i], ft_strlen_eq(add)) == 0)
		{
			src->export[i] = NULL;
			src->export[i] = ft_strdup(add);
			envp[src->lastenv++] = ft_strdup(add);
			if (i == src->lastexp)
				src->export[++i] = NULL;
		}
		i++;
	}
	if (found_eq(add) && ft_search(envp, add))
		replace_env(envp, src, add);

}
int ft_alloc_count(char **envp, t_node *head)
{
	int i = 0;
	while (envp[i])
		i++;
	int j = 0;
	while (head->arg[j])
		{
			if (ft_search(envp, head->arg[i]))
				i++;
			j++;
		}
	return (i);
}

void ft_realloc_enxp(t_source *src, t_node *head)
{
	int ex = ft_alloc_count(src->export, head);
	int en = ft_alloc_count(src->our_envp, head);
	
}
void	ft_set_enxp(t_node *head, t_source *src, char **envp)
{
	int argn;
	int i;

	i = 0;
	argn = arg_counter(head->arg);
	while (i < argn)
	{
		if (check_exsyn(head->arg[i]))
			{
				write (2, "not a valid identifier\n", 23);
				i++;
				continue ;
			}
		if (ft_search(src->export, head->arg[i]))
			ft_expn_chng(head->arg[i], src, envp);
		else
			{
				ft_realloc_enxp(src, head);
				ft_expn_add(head->arg[i], src, envp);}
		i++;
	}
}

void	ft_export(t_node *head, t_source *src, char **envp)
{
	if (head->arg[0] == NULL)
		em_export(src);
	else
		ft_set_enxp(head, src, envp);
}






// void	ft_export(t_node *head, t_source *src, char **envp)
// {
// 	int		i;
// 	int		j;
// 	int		found;
// 	int		length;
	
// 	i = 0;
// 	if (head->arg[i] == NULL)
// 		em_export(src);
// 	else
// 	{
// 		while (head->arg[i] != NULL)
// 		{	
// 			//  length = ft_strlen_eq(head->arg[i]);
// 			found = ft_search(src,head->arg[i]);
// 			if (found)
// 			 {
// 				 j = 0;
// 				while (src->export[j] != NULL)
// 				{
// 					length = ft_strlen_eq(src->export[j]);
// 					if (ft_strncmp(src->export[j], head->arg[i], length) == 0)
// 					{
// 						if (length < ft_strlen(head->arg[i]))
// 						{
// 							src->export[j] = head->arg[i];
// 							replace_env(envp, src, head->arg[i], length);
// 							if (j == src->lastexp)
// 								src->export[++j] = NULL;
// 						}
	
// 					}
// 					j++;
// 				}
// 			 }
// 			else
// 			{
// 				if (found_eq(head->arg[i]))
// 				{
// 					envp[src->lastenv++] = head->arg[i];
// 					src->export[src->lastexp++] = head->arg[i];
// 					src->export[src->lastexp] = NULL;
// 					envp[src->lastenv] = NULL;
// 				}
// 				else
// 				{
// 					// if ()
// 					src->export[src->lastexp++] = head->arg[i];
// 					src->export[src->lastexp] = NULL;
// 				}
// 			}
// 				i++;
// 		}
// 	}
// }

int		ft_unset(t_node *head, t_source *src, char **envp)
{
	int i;
	int c;
	int len;
	int arglen;

	i = 0;
	c = 0;
	while (head->arg[i] != NULL)
	{
		len = ft_strlen(head->arg[i]);
		arglen = arg_counter(envp);
		while(src->export[c]!= NULL)
		{
			if (ft_strncmp(head->arg[i], src->export[c], len) == 0)
				{
					int j = c;
					while (j < arglen - 1)
              	  	{
                    	src->export[j] = src->export[j + 1];
                    	j++;
              	 	 }
					src->lastexp--;
					src->export[j] = NULL;
					if (ft_search(envp, head->arg[i]))
					{
						int count = 0;
						arglen = arg_counter(envp);
						while (envp[count] != NULL)
						{
							if (ft_strncmp(head->arg[i], envp[c], ft_strlen(head->arg[i])) == 0)
							{
								int j = c;
								while (j < arglen - 1)
              	  				{
            						envp[j] =envp[j + 1];
                    				j++;
              	 				 }
									src->lastenv--;
									envp[j] = NULL;
								
							}
							count++;
						}

						
					}
				}
			c++;
		}
		i++;
	}
	return (0);
}
/*
void command_unset(t_commands *tmp ,char **envp)
{
    int lenp;
    int lenarg;
    int k = 0;
    lenp = len_of_args(envp);
    lenarg = nbr_argts(tmp) - 1;
    while(k < lenarg)
    {
        check_syntax(tmp, k ,lenarg);
        for (int i = 0; i < lenp; i++)
        {
            if (strncmp(envp[i], tmp->arguments[k], strlen(tmp->arguments[k])) == 0)
            {
                int j = i;
                while (j < lenp - 1)
                {
                    envp[j] = envp[j + 1];
                    j++;
                }
                envp[j] = NULL;
                lenp = len_of_args(envp);
            }
        }
        k++;
    }
}*/