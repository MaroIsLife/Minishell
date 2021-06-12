
#include "minishell.h"
void    ft_echo(char **args)
{
	int i;
	int newline;
	
	newline = 0;
	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strncmp(args[0], "-n", 2) == 0 && args[0][2] == '\0')
		{
			i++;
			newline = 1;
			if (args[1] == NULL)
				break ;
		}
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] == NULL)
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

char **our_realloc(char **s, int count)
{
	char **ret = malloc (count);
	int i = -1;
	while (s[++i])
		ret[i] = ft_strdup(s[i]);

	return (ret);
}

void	print_env(t_source *src)
{


	int i;

	i = 0;
	while (src->our_envp[i] != NULL)
	{
		ft_putstr_fd(src->our_envp[i], 1);
		if (src->our_envp[i][0] != '\0')
			ft_putstr_fd("\n", 1);
		i++;
	}
}

char	*where_home(t_source *src)
{
	int i = 0;
	char *home;
	
	while (src->our_envp[i])
	{
		if (ft_strncmp(src->our_envp[i], "HOME=", 5) == 0)
		{
			home = malloc (ft_strlen(src->our_envp[i] + 5) + 1);
			ft_strlcpy(home, src->our_envp[i] + 5, ft_strlen(src->our_envp[i] + 5) + 1);
			return (home);
		}
	i++;
	}
	return (0);
}
void	ft_pwd (void)
{
	char *s;
	
	s = malloc(100 * sizeof(char));
	printf("%s\n", getcwd(s, 100));
	// printf ("%s\n", s1);
	free (s);
}
void ft_cd(char **args, t_source *src, char *home)
{
	int sign;

	sign = 0;

	//puts (args[0]);
	if (!args[0])
		{
			if (!home)
				write(1, "minishell: cd: HOME not set\n", 23);
			else
				chdir(home);
			free(home);
		}
	else
		sign = chdir(args[0]);
	if (sign != 0)
		printf ("Error: %s\n", strerror(errno));
	change_pwd_env(src);
	change_pwd_export(src);


}



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
			  if (s[i] == '=' && !s[i + 1])
				{
                    write(1,"\"\"",2);
                    break ;
                }
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
int is_equal(char *s1, char *s2)
{
	int l1 = ft_strlen_eq(s1); //if NULL=SEGFAULT
	int l2 = ft_strlen_eq(s2); //if NULL=SEGFAULT
	

	if (l1 != l2)
		return 0;

	for (int i = 0; i < l1; i++)
		if (s1[i] != s2[i])
			return 0;
	return 1;
}
int ft_search(char **src, char *value)
{
	int i;

	i = 0;
	// printf("%s\n",value);
	while (src[i] != NULL)
	{
		if (is_equal(src[i], value))
			return(1);
		i++;
	}
	return (0);
}


int 	check_exsyn(char *src)
{
	// if (src[0] >= '0' && src[0] <= '9')
	// 	return (1);
	if (src[0] == '_'  || ft_isalpha(src[0]) )
	{
		int i = 1;
		while (src[i] != '=' && src[i])
		{	if (!ft_isalnum(src[i]) && src[i] != '_') 
				return(1);
				i++;
			}
	}
	else
		return (1);
	return (0);
}

//envp just for testing
int ft_alloc_count(char **envp, char **args)
{
	int i = 0;
	while (envp[i])
		i++;
	int j = 0;
	while (args[j] != NULL)
		{
			if (ft_search(envp, args[j]))
				i++;
			j++;
		}
	return (i);
}


void 	ft_expn_add(char *add, t_source *src ,char **our_envp, char **args)
{
	int id;

	
	id = found_eq(add);
	if (id)
		{
			src->our_envp = our_realloc(src->our_envp, sizeof(char*) * (ft_alloc_count(src->our_envp,args) + 2) ); //here
			src->export = our_realloc(src->export, sizeof(char*) * (ft_alloc_count(src->export, args) + 2) ); //here
			src->our_envp[src->lastenv++] = ft_strdup(add);
			src->export[src->lastexp++] = ft_strdup(add);
			src->export[src->lastexp] = NULL;
			src->our_envp[src->lastenv] = NULL;
		}
	else 
		{
			src->export = our_realloc(src->export, sizeof(char*) * (ft_alloc_count(src->export, args) + 2) ); //here
			src->export[src->lastexp++] = ft_strdup(add);
			src->export[src->lastexp] = NULL;

		}
}

void	ft_expn_chng(char *add, t_source *src ,char **envp)
{
	int i;

	i = 0;
	while (src->export[i] != NULL)
	{
		char *see = src->export[i];
		// if (ft_strncmp(add, src->export[i], ft_strlen_eq(add)) == 0)
			if (is_equal(add, src->export[i]))
		{
			// src->export[i] = NULL;
			//change only if there is an equle
			if (found_eq(add))
				src->export[i] = ft_strdup(add);
			// src->our_envp[src->lastenv++] = ft_strdup(add);
			if (i == src->lastexp)
				src->export[++i] = NULL;
		}
		i++;
	}
	if (found_eq(add))
	{
		if (ft_search(src->our_envp, add))
			replace_env(envp, src, add);
		else
			{
				src->our_envp = our_realloc(src->our_envp, sizeof(char*) * (arg_counter(src->our_envp) + 2) );
				src->our_envp[src->lastenv++] = ft_strdup(add);
				src->our_envp[src->lastenv] = NULL;
			}

	}
}




void	ft_set_enxp(char **args, t_source *src, char **envp)
{
	int argn;
	int i;

	i = 0;
	argn = arg_counter(args);
	while (i < argn)
	{
		int n = check_exsyn(args[i]);
		if (n)
			{
				printf ("[%d]\n", n);
				write (2, "not a valid identifier\n", 23);
				i++;
				continue ;
			}
		if (ft_search(src->export, args[i]))
			ft_expn_chng(args[i], src, src->our_envp);
		else
			ft_expn_add(args[i], src, src->our_envp, args);
		i++;
	}
}

void	ft_export(char **args, t_source *src)
{
	if (args[0] == NULL)
		em_export(src);
	else
		ft_set_enxp(args, src, src->our_envp);
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




void 	unset_export(t_source *src, char *arg)
{
	int i = 0;
	while (src->export[i] != NULL)
	{
	if (is_equal(src->export[i], arg))
		{
			while ((src->export[i] != NULL))
				{
					src->export[i] = src->export[i + 1];
					i++;
				}
				src->lastexp--;
				src->export[i] = NULL;
				break ;
		}
	i++;
	}			
}

void 	unset_env(t_source *src, char *arg)
{
	int i = 0;
	while (src->our_envp[i] != NULL)
	{
	if (is_equal(src->our_envp[i], arg))
		{
			while ((src->our_envp[i] != NULL))
				{
					src->our_envp[i] = src->our_envp[i + 1];
					i++;
				}
				src->lastenv--;
				src->our_envp[i] = NULL;
				break ;
		}
	i++;
	}			
}

int		ft_unset(char **args,t_source *src)
{
	int env;
	int exp;
	int j = 0;

	while (args[j])
	{
		env = ft_search(src->our_envp, args[j]);
		exp = ft_search(src->export, args[j]);
		if (exp)	
			unset_export(src, args[j]);	
		/******************************************/
		if (env)
			unset_env(src, args[j]);	
		/******************************************/
		j++;
	}
	return (0);
}



int		ft_exit(char **args, t_source *src)
{
	int b;
	int ret;

	b = 0;
	if (args[0] == NULL)
		exit(0);
	while (args[0][b] != '\0')
	{
		if (ft_isdigit(args[0][b]) != 1)
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n",args[0]);
			//src->return_value = 2;
			exit(255);
		}
		b++;
	}
	if (args[1] != NULL) //CHECK IF IT DOESNT LEAVE CHILD PROCESS
	{
		printf("exit\nminishell: exit: too many arguments\n");
		return(0);
	}
	ret = ft_atoi(args[0]);
	// printf("%d\n",ret);
	if (ret > 255)
	{
		write(1,"exit\n",6);
		exit(ret % 256);
	}
	else if (ret < 0)
	{
		write(1,"exit\n",6);
		exit (ret + 256);
	}
	else
	{
		write(1,"exit\n",6);
		exit(ret);
	}
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