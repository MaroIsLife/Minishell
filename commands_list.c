#include "minishell.h"
char **ft_valide_args(t_node *head, int count)
{
	char **varg = malloc (sizeof(char*) * (count + 2));
	int i = 1;
   varg[0] = head->cmd;
	while (i < (count + 1))
	{
		varg[i] = ft_strdup(head->arg[i - 1]);
		i++;
	}
	varg[i] = NULL;
	return (varg);
}

char	**get_env_path(char **envp, t_source *src)
{
	int		i;
	char	*s;
	char 	**paths;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0 && envp[i][4] == '=')
		{
			s = ft_strchr(envp[i],'=') + 1; // SHOULD BE RECODED
			paths = ft_split_normal(s, ':');
			return(paths);
		}
		i++;
	}
	return (0);
}

char	*get_correct_path(char **s, char **varg)
{
	struct	stat sb;
	char	*tmp;
	char	*tmp2;
	int		i; 

	i = 0;
	while (s[i] != NULL)
	{
		tmp = ft_strjoin(s[i], "/");
		tmp2 = ft_strjoin(tmp, varg[0]);
		free(tmp);
		if (stat(tmp2, &sb) != -1)
			return (tmp2);
		else 
			free(tmp2);
		i++;
	}
	return (0);
}

void    ft_execute(t_node *head, t_source *src, char **envp)
{
	char	**s;
	char	*path;
	static int	i;
	char	**varg;

		
	varg = ft_valide_args(head, src->count);
	if (head->cmd[0] == '/' || (head->cmd[0] == '.' && head->cmd[1] == '/'))
		path = head->cmd;
	else 
	{
		s = get_env_path(envp, src);
		path = get_correct_path(s, varg); // We should also add current PWD
	}
	i = 2;
	// STRCHR BELOW SHOULD BE PROCTED 
	// if (ft_strncmp(ft_strrchr(path,'/') + 1, "bash", sizeof("bash")) == 0)
	// 	set_x_env(envp, src, "SHLVL", ft_itoa(++i));

	if (path != 0)
	{
		if ((g_id = fork()) == 0)
		{
			signal(SIGINT,SIG_DFL);
			if (execve(path ,&varg[0], envp) == -1)
			{
				printf("bash: %s: %s\n",varg[0], strerror(errno));
				exit(1);
			}
		}
		else
			wait(&g_id);
	}
	else 
		printf("bash: %s: command not found\n",varg[0]);
}

void command_list(t_node *head, t_source *src, char **envp)
{
	if (ft_strncmp(head->cmd, "cd", 2) == 0 && head->cmd[2] == '\0')
		ft_cd(head, where_home(envp),envp);
	else if (ft_strncmp(head->cmd,"echo",4) == 0 && head->cmd[4] == '\0')
		ft_echo(head, src);
	else if (ft_strncmp(head->cmd, "env", 3) == 0 && head->cmd[3] == '\0')
		print_env(head, src, envp);
	else if (ft_strncmp(head->cmd, "export", 6) == 0 && head->cmd[6] == '\0')
		ft_export(head, src, envp);
	else if (ft_strncmp(head->cmd, "pwd", 3) == 0 && head->cmd[3] == '\0')
		ft_pwd();
	else if (ft_strncmp(head->cmd, "unset", 5) == 0 && head->cmd[5] == '\0')
		ft_unset(head, src, envp);
	else
		ft_execute(head, src, envp);
}