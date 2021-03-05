
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
  char *CLEAR_SCREEN_ANSI;
  CLEAR_SCREEN_ANSI = malloc(1024 * sizeof(char));
  CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(1, CLEAR_SCREEN_ANSI, 12);
  free(CLEAR_SCREEN_ANSI);
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

int count_argument(char *s, int offset, t_source *src) //CONVERT TO SPLIT?
{
	int i;
	int count;

	i = src->offset - 1;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' && i == 0)
			src->dquotes = 1;
		else if (s[i] == '\'' && i == 0)
			src->squotes = 1;
		else
			finding_quotes(s, i, src);
		if ((s[i] == ';' || s[i] == '|') && (src->dquotes == 0 && src->squotes == 0))
			return (count);
		if (s[i] == ' ' && src->dquotes == 0 && src->squotes == 0)
		{
			while (s[i] == ' ')
				i++;
			// if ((s[i] == '|' || s[i] == ';') && src->dquotes == 0 && src->squotes == 0)
			// 	return (count);
			if (s[i] == '\0')
				return (count);
			count++;
		}
		else
			i++;
	}
	return(count);
}
void init(t_source *src)
{
	g_find.founderror = 0;
	g_find.foundPipe = 0;
	src->offset = 0;
	// g_source.cmdlen = 0;
	// g_source.isPipe = 0;
	src->dquotes = 0;
	src->aslash = 0;
	src->offset = 0;
}


void	ms_loop(t_source *src, char **envp)
{
	char *cmd;
	int count;
	int i = 0;
	t_node *head;
	t_node *first;
	char **pipe;

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
	while(1)
	{
		print_prompt1();
		cmd = read_line();
		if (ft_strncmp(cmd,"print",5) == 0)
			printf("Hello\n");
		if (ft_strncmp(cmd,"push",4) == 0)
			push_env(envp, "abc");

		if (ft_strncmp(cmd,"exit",4) == 0)
			exit(0);
		if (ft_strncmp(cmd,"clear",5) == 0)
			system("clear");

		// if (ft_strncmp(command,"cat",3) == 0)
		// {
		// 	execve("/bin/cat","path.txt",)
		// }
		init(src);
		pipe = ft_split(cmd,';', src);
		int c = 0;
		// while (pipe[c] != NULL)
		// 	printf("%s\n",pipe[c++]);


		// push(12);
		// push(31);

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
			
			head->cmd = find_command(pipe[c], src->offset, src);
			count = count_argument(pipe[c],src->offset,src);
			src->dquotes = 0;
			src->squotes = 0;

			// printf("Number of Pipes: %d\n",g_find.nPipe);
			// printf("#%d Command: %s\n",c,head->cmd);
			// printf("Argument's Offset: %d\n",src->offset);
			// printf("Count: %d\n",count);
			i = i^i;
			head->arg = malloc((count + 1) * sizeof(char *));
			while (i < count)
			{
				head->arg[i] = find_argument(pipe[c], src->offset, src);
				i++;
			}
			head->arg[i] = NULL;
			i = i^i;
			while (head->arg[i] != NULL)
			{
				// printf("#%d Argument %d : %s\n",c,i,head->arg[i]);
				i++;
			}
			// printf("Found Error: %d\n",g_find.founderror);
			c++;
			src->offset = 0;
			if (ft_strncmp(head->cmd,"echo",4) == 0)
				ft_echo(head, src);
			else if (ft_strncmp(head->cmd, "env", 3) == 0)
				print_env(head, src, envp);
			else if (ft_strncmp(head->cmd, "export", 6) == 0)
				ft_export(head, src, envp);
			else if (ft_strncmp(head->cmd, "pwd", 3) == 0)
				ft_pwd();
			else if (ft_strncmp(head->cmd, "cd", 2) == 0)
				ft_cd(head, where_home(envp));
				// where_home(envp);
		}


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
		

		//echo \' FIX THIS
		//echo \"
		//echo \\
		//echo \'

		//echo \;
		//echo \|



		//command "\'"




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