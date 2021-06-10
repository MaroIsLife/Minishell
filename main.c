# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include "minishell.h"



char	*get_x_env(char **envp, t_source *src, char *envv_name)
{
	int 	i;
	int		b;
	int		c;
	char	*s;

	b = 0;
	c = 0;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], envv_name, ft_strlen(envv_name)) == 0 && envp[i][ft_strlen(envv_name)] == '=')
			return (ft_strrchr(envp[i],'=') + 1);
		i++;
	}
	return (0);
}

void	set_x_env(char **envp, t_source *src, char *envv_name, char *value)
{
	int 	i;
	int		b;
	int		c;
	char	*s;

	b = 0;
	c = 0;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], envv_name, ft_strlen(envv_name)) == 0 && envp[i][ft_strlen(envv_name)] == '=')
		{
			while (envp[i][c] != '=' && envp[i][c] != '\0')
				c++;
			c++;
			while (value[b] != '\0')
				envp[i][c++] = value[b++];
			envp[i][c] = '\0';
			break ;
		}
		i++;
	}
}

void	init(t_source *src)
{
	src->founderror = 0;
	src->offset = 0;
	src->dquotes = 0;
	src->squotes = 0;
	src->aslash = 0;
	src->offset = 0;
}

void	init_env(t_source *src, char **envp)
{
	int	i;

	i = 0;
	src->lastenv = 0;
	src->lastexp = 0;
	while (envp[i] != NULL)
	{
		src->lastenv++;
		src->lastexp++;
		i++;
	}
	src->our_envp = malloc(sizeof(char *) * (i + 2)); /* New ENV */
	src->export = malloc(sizeof(char *) * (i + 2));
	src->our_envp[i] = "\0";
	i = 0;
	src->export[i] = ft_strdup("OLDPWD");
	while (envp[i] != NULL)
	{
		src->our_envp[i] = ft_strdup(envp[i]);
		src->export[i + 1] = ft_strdup(envp[i]);
		i++;
	}
	src->our_envp[i + 1] = NULL;
	src->export[i + 1] = NULL;
	src->lastenv++;
	src->lastexp++;
}


void	ms_loop(t_source *src, char **envp)
{
	char	*cmd;
	int		count;
	int		i = 0;
	t_node	*head;
	t_node	*first;
	char	**pipes;
	int		fsignal;

	init_env(src,envp);
	src->user = get_x_env(src->our_envp, src, "USER"); 
	src->pwd = get_x_env(src->our_envp, src, "PWD");
	 // This Retrieves the USER's logname and stores it in src->user NOT ALLOCATED
	// set_x_env(envp, src, "TESST", "test");
	g_global.return_value = 0;
	//............................
	t_termc *termc;
	t_stack *head1;
	t_stack *tmp;
	char	*ret;

	termc = (t_termc *) malloc(sizeof(t_termc));
	termc->edit = 0;
	termc->help = 0;
	// g_global.ret = malloc(1 * sizeof(char));
	// g_global.ret[0] = '\0';
	g_global.ret = NULL;
	tgetent(NULL, getenv("TERM"));
	tmp = NULL;
	head1 = NULL;
	signal(SIGTERM, SIG_IGN);
	while(1)
	{
		// printf("\U0001F600"); //Useless Emoji
		signal(SIGINT,handler); // ^C
		signal(SIGQUIT,handler2);
		if (g_global.fsignal  == 0)
		{
			print_prompt1();
			g_global.fsignal  = 1;
		}
		// signal(SIGQUIT,handler); // ^/
		// cmd = read_line();
		g_global.ret = NULL;
		cmd = term_loop(&head1, &tmp, termc);
		// free(g_global.ret);
		int b = 0;
		while (cmd[b] == ' ') // space as a command
			b++;
		if (cmd[b] == '\0')
		{
			print_prompt1();
			continue ;
		}
		// printf("cmd: %s\n",cmd);
		g_global.fsignal  = 0;
		if (cmd == NULL) // ^D
		{
			write(1,"exit\n",6);
			exit(0);
		}
		// if (ft_strncmp(cmd, "exit", 4) == 0)
		// 	exit(0);export
		// 	clearScreen();
	
		init(src); // MOVE INIT() TO WHILE PIPE != NULL??
		pipes = my_ft_split(cmd,';', src);
		free(cmd);
		int c;
		int o =0;
		c = 0;
		src->fd_r_c = 0;


		/**
		 * PIPE implumetation : Craete FD{2} and it redirect from 1>0 then use dup to dup 
		 * EZPZ 
		 * */
		while (pipes[c] != NULL)
		{
			head = (t_node *) malloc(sizeof(t_node));
			head->next = NULL;
			head->pipe = NULL;
			head->first_filename = NULL;
			first = head;

			find_for_split(pipes[c], src);
			src->allocate = 0;

			if (src->foundred == 1)
			{
				head->first_filename = (t_filename *)malloc(sizeof(t_filename));
				head->first_filename->next = NULL;
				src->p = head->first_filename;
			}

			src->dquotes = 0;
			src->squotes = 0;
			src->fd_r_c = 0;
			i = 0;
			src->c = c;
			init_parse(src, head, src->our_envp, pipes); //CHANGED FROM ENVP TO OUR_ENVP
			i = 0;
			// if (ft_strncmp(head->cmd,"\0", 1) == 0)
				// printf("Cmd: %s\n",head->cmd);
			if (!head->cmd)
			{
				c++;
				continue ;
			}
			// while (head->arg[i] != NULL)
			// 	printf("Arg: %s\n",head->arg[i++]);
			src->offset = 0;
			g_global.return_value = 0;
		/*
		commande list should only take t_source and cmd and args
		to make it accepet out-put from standard and from pipe NODE.
		*/
			if (src->foundred == 0 && src->foundpipe == 0)
				command_list(head->cmd ,head->arg,  src);
			else
			{
			
					if (src->foundpipe == 1)
					{ 
					// fork_pips(src, head);
						fork_pips (src->npipe + 1, head, src);
					}
					if (src->foundred && !src->foundpipe)
					{	
						int id = fork();
						int ge_id;
						if (id == 0)
						{
							red_open(head, src);
						command_list(head->cmd ,head->arg, src);
						exit(0);
						}
						wait(&id);
					}
			}
			// free(head->cmd);	
			c++;
		}
		int p = 0;
		while (pipes[p] != NULL)
		{
			free(pipes[p]);
			p++;
		}
		free(pipes);
		system("leaks a.out");
	}
}

int     main(int argc, char **argv, char **envp)
{
	t_source src;
	// clear();

	ms_loop(&src, envp);
	
	//echo kjlkj l> bl$lkjlkjlkj
	//Enter then Delete without any Value
	//Space then Enter
	return (0);
}