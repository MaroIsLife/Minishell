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
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			s = strchr(envp[i],'=') + 1; // SHOULD BE RECODED
			// s = ft_strjoin(src->pwd, s);
			// printf("%s\n",s);
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
	char	**varg;

	varg = ft_valide_args(head, src->count);
	s = get_env_path(envp, src);
	path = get_correct_path(s, varg); // We should also add current PWD

	// printf("%s\n",path);
	
	if (path != 0)
	{
		g_id = fork();
		if (g_id == 0)
			execve(ft_strjoin(path, varg[0]),varg, NULL);
		else
			wait(&g_id);
	}
}

void command_list(t_node *head, t_source *src, char **envp)
{
	if (ft_strncmp(head->cmd, "cd", 2) == 0)
		ft_cd(head, where_home(envp),envp);
	else if (ft_strncmp(head->cmd,"echo",4) == 0)
		ft_echo(head, src);
	else if (ft_strncmp(head->cmd, "env", 3) == 0)
		print_env(head, src, envp);
	else if (ft_strncmp(head->cmd, "export", 6) == 0)
		ft_export(head, src, envp);
	else if (ft_strncmp(head->cmd, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(head->cmd, "unset", 5) == 0)
		ft_unset(head, src, envp);
	else
		ft_execute(head, src, envp);
}