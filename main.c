
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "minishell.h"

char *where_home(char **envp)
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
void ft_pwd (void)
{
	char* s = malloc (100);

	printf ("%s\n",getcwd(s, 100));
	free (s);
}
void ft_cd(t_node *head, char *home)
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
void clearScreen()
{
  write(1, "\e[1;1H\e[2J", 10);
}

void push_env(char **envp, char *s)
{
	int i;
	
	i = 0;
	while (envp[i] != NULL)
		i++;
	
	envp[i] = "abc";
	envp[++i] = NULL;
}

// void	print_list() {
   
//    t_node *first;

//    first = head;
// 	while(head != NULL)
// 	{
// 		printf("%d\n",head->number);
// 		head = head->next;
// 	}
// 	head = first;
//     // while (head != NULL) {
//     //     printf("%d\n", head->number);
//     //     head = head->next;
//     // }
// }

// void	push(char *cmd, char *arg, int num) 
// {
// 	t_node		*tmp;
	
// 	tmp = head;
//     while (head->next != NULL) {
//         head = head->next;
//     }

//     head->next = (t_node *) malloc(sizeof(t_node));
//     head->next->number = num;
// 	// head->next->arg = arg;
//     head->next->cmd = cmd;
//     // head->next->pipe = num;
//     head->next->next = NULL;
// 	head = tmp;
// }


void init(t_source *src)
{
	src->founderror = 0;
	src->offset = 0;
	// g_source.cmdlen = 0;
	// g_source.isPipe = 0;
	src->dquotes = 0;
	src->squotes = 0;
	src->aslash = 0;
	src->offset = 0;
}
void init_env(t_source *src,char **envp)
{
	int i;

	i = 0;
	src->lastenv = 0;
	while (envp[i] != NULL)
	{
		src->lastenv++;
		i++;
	}
	src->lastexp = src->lastenv;
	i = 0;
	while (envp[i] != NULL)
	{
		src->export[i] = envp[i];
		i++;
	}
	src->export[i] = NULL;

	
}


void	ms_loop(t_source *src, char **envp)
{
	char *cmd;
	int count;
	int i = 0;
	t_node *head;
	t_node *first;
	char **pipe;
	init_env(src,envp);
	while(1)
	{
		print_prompt1();
		signal(SIGINT,handler); // ^C
		// signal(SIGQUIT,handler2); // ^/
		cmd = read_line();
		if (cmd == NULL) // ^D
		{
			write(1,"exit\n",6);
			exit(0);
		}
		if (ft_strncmp(cmd,"print",5) == 0)
			printf("Hello\n");
		if (ft_strncmp(cmd,"push",4) == 0)
			push_env(envp, "abc");

		if (ft_strncmp(cmd,"exit",4) == 0)
			exit(0);
		if (ft_strncmp(cmd,"clear",5) == 0)
			clearScreen();
			// system("clear");

		// if (ft_strncmp(command,"cat",3) == 0)
		// {
		// 	execve("/bin/cat","path.txt",envp)
		// }
		init(src); // MOVE INIT() TO WHILE PIPE != NULL??
		pipe = ft_split(cmd,';', src);
		int c = 0;

		
		c = 0;
		char **realpipes;
		while (pipe[c] != NULL)
		{
			head = (t_node *) malloc(sizeof(t_node));
			head->next = NULL;
			head->pipe = (t_pipe *) malloc(sizeof(t_pipe));
			head->pipe->next = NULL;
			first = head;
			find_for_split(pipe[c], src);
			src->dquotes = 0;
			src->squotes = 0;

			
			i = i^i;
			// while (realpipes[i] != NULL)
			// {
			// 	printf("%s\n",realpipes[i]);
			// 	i++;
			// }
			
			
			// head->cmd = find_command(pipe[c], src->offset, src, envp);
			// // head->cmd = find_argument(pipe[c], src->offset, src, envp);
			// count = count_argument(pipe[c],src->offset,src);
			// src->dquotes = 0;
			// src->squotes = 0;
			// i = i^i;
			// head->arg = malloc((count + 1) * sizeof(char *));
			// while (i < count)
			// {
			// 	head->arg[i] = find_argument(pipe[c], src->offset, src, envp);
			// 	i++;
			// }
			// head->arg[i] = NULL;
			src->c = c;
			init_parse(src, head, envp, pipe);
			i = i^i;
			src->offset = 0;
			// printf("Command: %s\n",head->cmd);
			// while (head->arg[i] != NULL)
			// {
			// 	printf("#%d Argument %d : %s\n",c,i,head->arg[i]);
			// 	i++;
			// }
			// printf("%s",pipe[c]);
			// printf("%c\n",pipe[c][src->offset + 1]);
			
			// int id = fork();
			// int ge_id;

			// if (id == 0)
			// {
				// printf ("child %d\n", getpid());
			if (src->foundpipe == 0)
			{
				if (ft_strncmp(head->cmd, "cd", 2) == 0)
					ft_cd(head, where_home(envp));
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
			}
			//exit(0);
			// }
			// else 
			// {
			// 	wait(&ge_id);
			// 	printf ("parent %d\n", getpid());

			// }
				// where_home(envp);
			c++;
		}

	//	echo 'hello         a'  bye
	////echo "\$ \| \; \" "
	
		//FIX "echo" "hello" !!!
		//echo "\hello\\\""
		//echo "hello\\
		//echo "hello\\"  FIX THIS
		//echo "hello\"
		//echo hello\"
		//ls | grep "file" < file
		//> file ls
		//\e\c\h\o \e\a\c
		//"e""c""h""o" hi

		//echo 'a    b      c ' FIX THIS
		

		//echo \' FIX THIS
		//echo \"
		//echo \\
		//echo \'

		//echo \;
		//echo \|



		//command "\'"

		//FIX '\' = EVERYTHING INSIDE '' is written and not escaped



		//e\c\h\o b\y\e FIX THIS
		// echo bye; FIX THIS
		// echo "hello"\a\c FIX THIS
		//echo "'jjj'"'""\'
		// echo '"'"ll'\'" FOUND ERROR = 1
		//echo "$USERjjjjj$SHLVL"
		//echo ' "ab" '

	

		// free(command);
		// free(cmd);
		// free(argument);
		// free(token);
	}
}


int     main(int argc, char **argv, char **envp)
{
	t_source src;
	// clear();
	ms_loop(&src, envp);

	return (0);
} 