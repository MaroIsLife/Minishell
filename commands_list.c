#include "minishell.h"

void	red_open_pipe(t_filename *tmp)
{
	int			fd;
	int			fd2;
	t_filename	*p;
	p = tmp;
	printf("%s\n",p->filename);
	while (1)
	{
		// puts(p->filename);
	if (p->c == 94)
		fd = open(p->filename, O_RDWR | O_APPEND | O_CREAT, 0777);
	else if (p->c == '>')
		fd = open(p->filename, O_RDWR | O_TRUNC | O_CREAT, 0777);
	else if (p->c == '<')
		fd2 = open(p->filename, O_RDONLY);
		if (fd == -1 || fd2 == -1)
		{
			// printf("minishell: %s: %s\n",p->filename, strerror(errno));
			char *err = strerror(errno);
			write(2, "minishell: ", 11);
			write(2, p->filename,ft_strlen(p->filename));
			write(2, " ", 1);
			write(2, err,ft_strlen(err));
			write(2, "\n", 1);
			exit(0);
		}
		if (p->next == NULL)
			break ;
		p = p->next;
	}
	if (p->fd_r_c == 50)
	{
		dup2(fd, 1);
		dup2(fd2, 0);
	}
	else if (p->c == 94 || p->c == '>')
		dup2(fd, 1);
	else if (p->c == '<')
		dup2(fd2, 0);

	close(fd);
	//Close fd2 too
}

void	red_open(t_node *head, t_source *src)
{
	int			fd;
	int			fd2;
	t_filename	*p;
	p = head->first_filename;
	// printf("%s\n",p->filename);
	while (1)
	{
		// puts(p->filename);
	if (p->c == 94)
		fd = open(p->filename, O_RDWR | O_APPEND | O_CREAT, 0777);
	else if (p->c == '>')
		fd = open(p->filename, O_RDWR | O_TRUNC | O_CREAT, 0777);
	else if (p->c == '<')
		fd2 = open(p->filename, O_RDONLY);
		if (fd == -1 || fd2 == -1)
		{
			// printf("minishell: %s: %s\n",p->filename, strerror(errno));
			char *err = strerror(errno);
			write(2, "minishell: ", 11);
			write(2, p->filename,ft_strlen(p->filename));
			write(2, " ", 1);
			write(2, err,ft_strlen(err));
			write(2, "\n", 1);
			exit(0);
		}
		if (p->next == NULL)
			break ;
		p = p->next;
	}
	if (src->fd_r_c == 50)
	{
		dup2(fd, 1);
		dup2(fd2, 0);
	}
	else if (p->c == 94 || p->c == '>')
		dup2(fd, 1);
	else if (p->c == '<')
		dup2(fd2, 0);

	close(fd);
	//Close fd2 too
}
int  calc_args (char **args)
{
	int i;

	i  = 0;
	while (args[i])
		i++;
	return (i);
}
char	**ft_valide_args(char *cmd, char **args, int count)
{
	char	**varg;
	int		i;
	int		b;

	i = 0;
	b = 1;
	varg = malloc (sizeof(char*) * (count + 2));
	varg[0] = cmd;
	while (args[i] != NULL)
		varg[b++] = args[i++];
	varg[b] = NULL;
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

int    ft_execute(char *cmd, char **args,t_source *src, char **envp)
{
	char	**s;
	char	*path;
	static int	i;
	char	**varg;

  	varg = ft_valide_args(cmd,args, calc_args(args));
	if (cmd[0] == '\0')
	{
		write(2,"minishell: ", 11);
		write(2,cmd,ft_strlen(cmd));
		write(2,": command not found\n",20);
		g_global.return_value = 127;
		return(0);
	}
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		path = cmd;
	else 
	{
		if (get_x_env(src->our_envp, src, "PATH") == 0)
		{
			// printf("minishell: %s: command not found\n", head->cmd);
			write(2,"minishell: ", 11);
			write(2,cmd,ft_strlen(cmd));
			write(2,": command not found\n",20);
			g_global.return_value = 127;
			return(0);
		}
		s = get_env_path(src->our_envp, src);
		path = get_correct_path(s, varg); // We should also add current PWD
	}
	if (path != 0)
	{	g_global.ffork = 1;
		if ((g_global.id = fork()) == 0)
		{
			// signal(SIGINT,SIG_DFL);
			if (execve(path , &varg[0], src->our_envp) == -1) //Should i send ENVP or OUR-ENV AND WHAT IS THE DIFFERENCE???!
			{
				// char *err = strerror(errno);
				// printf("minishell: %s: %s\n", varg[0], strerror(errno));
				write(2,"minishell: ",11);
				write(2,varg[0],ft_strlen(varg[0]));
				write(2,": ",2);
				write(2,strerror(errno),ft_strlen(strerror(errno)));
				write(2,"\n",1);
				exit(0);
			}
		}
		else
		{
			wait(&g_global.id);
			g_global.ffork = 0;
			if (WIFSIGNALED(g_global.id))
				g_global.return_value = WTERMSIG(g_global.id) + 128;
			else 
				g_global.return_value = WEXITSTATUS(g_global.id) % 128;
		}
	}
	else
	{
		// printf("minishell: %s: command not found\n",varg[0]);
			write(2,"minishell: ", 11);
			write(2,varg[0],ft_strlen(varg[0]));
			write(2,": command not found\n",20);
		g_global.return_value = 127;
	}
	return (0);	
}

void command_list(char *cmd, char **args,t_source *src)
{
	/*
	insted of Sending Head node only send double and single array for pips
	*/
	if (ft_strncmp(cmd, "cd", 2) == 0 && cmd[2] == '\0')
		ft_cd(args, src, where_home(src));
	else if (ft_strncmp(cmd,"echo",4) == 0 && cmd[4] == '\0')
		ft_echo(args);
	else if (ft_strncmp(cmd, "env", 3) == 0 && cmd[3] == '\0')
		print_env(src);
	else if (ft_strncmp(cmd, "pwd", 3) == 0 && cmd[3] == '\0')
		ft_pwd();
	else if (ft_strncmp(cmd, "export", 6) == 0 && cmd[6] == '\0')
		ft_export(args, src);
	else if (ft_strncmp(cmd, "unset", 5) == 0 && cmd[5] == '\0')
		ft_unset(args, src);
	else if (ft_strncmp(cmd, "exit", 4) == 0 && cmd[4] == '\0')
		ft_exit(args, src);
	else if ((src->dollarused == 1 && cmd[0] == '\0'))
		;
	else
		ft_execute(cmd, args, src, src->our_envp);
}
