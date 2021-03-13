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

char	*get_env_path(char **envp, t_source *src)
{
	int		i;
	int		b;
	char	*s;
	int		c;

	i = 0;
	b = 5;
	src->tmp = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			printf("Found Path\n");
			printf("%s\n",strchr(envp[i],'=') + 1);
			// while (envp[i][b] != '\0')
			// {
			// 	src->tmp++;
			// 	b++;
			// }
			// s = malloc((src->tmp + 1) * sizeof(char));
			// b = 5;
			// src->tmp = 0;
			// while (envp[i][b] != '\n' && envp[i][b] != '\0')
			// {
			// 	s[src->tmp++] = envp[i][b];
			// 	b++;
			// }
			// s[src->tmp] = '\0';
			// printf("%c %d\n",envp[i][b - 1],b);
			// src->tmp = 0;
			// return(s);
		}
		i++;
	}
	return (0);
}

void	find_path(char **envp, t_source *src)
{
	char	*s;
	char	**paths;

	s = get_env_path(envp, src);
	// printf("%s\n",s);
	paths = ft_split_normal(s, ':');
	
	int i = 0;

	// while (paths[i] != NULL)
	// {
	// 	printf("%s\n",paths[i++]);
	// }
	

}

void    ft_execute (t_node *head, t_source *src, char **envp)
{
	int id;
	id = fork ();
	char **varg;
	varg = ft_valide_args(head, src->count);
	// int i = 0;
	// while (varg[i])
	//     puts(varg[i++]);
	find_path(envp, src);
	if (id == 0)
		execve(ft_strjoin("/bin/", varg[0]),varg, NULL);
	else
		wait(&id);

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