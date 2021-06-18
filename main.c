#include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include "minishell.h"

	void freeList(t_node* head)
	{
	t_node* tmp;
		char *c_tmp;
		int i;

	while (head != NULL)
		{
		tmp = head;
		head = head->next;
		free(tmp->cmd);
			i = 0;
		if (tmp->arg)
		{
			while (tmp->arg[i])
				free(tmp->arg[i++]);}
			free(tmp->arg);
		}
		free(tmp);

	}
int num_of_node(t_pipe *tmp)
{
	int i;

	i = 0;
	while (tmp)
	{
		if (tmp->next == NULL)
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (i);
}
void freeList_pipe(t_pipe* head)
{
 	t_pipe* tmp;
	char *c_tmp;
	int i;
	int n = num_of_node(head);

	// printf ("===========%d=========\n", n);
	i = 0;
   while (head != NULL)
    {
		write (2, "how here\n", 9);
	   tmp = head;
       head = head->next;
       free(tmp->cmd);
	   if (tmp->pipef)
	   	free(tmp->pipef);
	
	if (tmp->arg)
	{
		while (tmp->arg[i])
			free(tmp->arg[i++]);}
		free(tmp->arg);
    }

	free(tmp);


}

char	*get_x_env(char **envp, t_source *src, char *envv_name)
{
	int		i;
	int		b;
	int		c;
	char	*s;

	b = 0;
	c = 0;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], envv_name, ft_strlen(envv_name)) == 0
			&& envp[i][ft_strlen(envv_name)] == '=')
			return (ft_strrchr(envp[i], '=') + 1);
		i++;
	}
	return (0);
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
	src->our_envp = malloc(sizeof(char *) * (i + 2));
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

void	sigs()
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler2);
	if (g_global.fsignal == 0)
	{
		print_prompt1();
		g_global.fsignal = 1;
	}
	g_global.ret = NULL;
}


void	ms_loop(t_source *src, char **envp, t_var *var)
{
	char	*cmd;
	int		count;
	int		i = 0;
	t_node	*head;
	t_node	*first;
	char	**pipes;
	int		fsignal;
	t_stack *head1;
	t_stack *tmp;
	char	*ret;

	init_env(src,envp);
	g_global.return_value = 0;
	var->edit = 0;
	var->help = 0;
	g_global.ret = NULL;
  	tgetent(NULL, getenv("TERM"));
	tmp = NULL;
	head1 = NULL;
	while(1)
	{
		sigs();
		cmd = term_loop(&head1, &tmp, var);
		int b = 0;
		while (cmd[b] == ' ')
			b++;
		if (cmd[b] == '\0')
		{
			print_prompt1();
			free(cmd);
			free(g_global.ret);
			continue ;
		}
		g_global.fsignal = 0;
		init(src);
		pipes = my_ft_split(cmd, ';', src);
		free(cmd);
		free(g_global.ret);
		int c;
		int o = 0;
		c = 0;
		src->fd_r_c = 0;
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
			init_parse(src, head, src->our_envp, pipes);
			if (src->founderror == 1)
				write(1, "Found error\n", 12);
			i = 0;
			if (!head->cmd)
			{
				c++;
				continue ;
			}
			src->offset = 0;
			g_global.return_value = 0;
			if (src->foundred == 0 && src->foundpipe == 0)
				command_list(head->cmd, head->arg, src);
			else
			{
					if (src->foundpipe == 1)
						{
							fork_pips (src->npipe + 1, head, src);
							t_pipe *here;
							
							t_pipe *next;
							int cont;

							here = head->pipe;
							while (here != NULL)
							{
								cont = 0;
								next = here->next;
								free (here->cmd);
								while (here->arg[cont])
									free(here->arg[cont++]);		
								free(here->arg);
								free(here);
								here = next;

							}
							head->pipe = NULL;

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
			c++;
		}
		// free(termc);
		// freeList(head);
			t_filename *here;
			t_filename *next;

			here = head->first_filename;
			while (here != NULL)
			{
				next = here->next;
				free(here->filename);
				free(here);
				here = next;
			}
		free(head->cmd);
		int n = 0;
		while (head->arg[n])
			free(head->arg[n++]);
		free(head->arg);
	
		free(head);
		int p = 0;
		while (pipes[p] != NULL)
		{
			free(pipes[p]);
			p++;
		}
		// printf("\np: %d\n",p);
		free(pipes);
		// system("leaks a.out");
	}
}

int     main(int argc, char **argv, char **envp)
{
	t_source src;
	t_var	var;
	// clear();

	ms_loop(&src, envp, &var);
	
	return (0);
}