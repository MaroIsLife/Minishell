# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include "minishell.h"

void clearScreen()
{
  write(1, "\e[1;1H\e[2J", 10);
}

void	get_user_env(char **envp, t_source *src)
{
	int i;
	int b;
	int c;

	b = 0;
	c = 0;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "USER", 4) == 0)
		{
			while (envp[i][b + 5] != '\0')
				b++;
			src->user = malloc((b + 1) * sizeof(char));
			b = 5;
			while (envp[i][b] != '\0')
			{
				src->user[c++] = envp[i][b++];
			}
			src->user[c] = '\0';
			break ;
		}
		i++;
	}
}

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
	get_user_env(envp, src); // This Retrieves the USER's logname and stores it in src->user
	while(1)
	{
		print_prompt1();
		// printf("\U0001F600"); //Useless Emoji
		signal(SIGINT,handler); // ^C
		// signal(SIGQUIT,handler2); // ^/
		cmd = read_line();
		if (cmd == NULL) // ^D
		{
			write(1,"exit\n",6);
			exit(0);
		}
		if (ft_strncmp(cmd,"exit",4) == 0)
			exit(0);
		if (ft_strncmp(cmd,"clear",5) == 0)
			clearScreen();
			// system("clear");
	
		init(src); // MOVE INIT() TO WHILE PIPE != NULL??
		pipe = ft_split(cmd,';', src);
		int c = 0;

		c = 0;
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
			src->c = c;
			init_parse(src, head, envp, pipe);
			i = i^i;
			src->offset = 0;
			if (src->foundpipe == 0)
				command_list(head, src, envp);
			else {
					int id = fork();
					int ge_id;
					if (id == 0)
					{
						command_list(head, src, envp);
					}
					else 
					{
						wait(&ge_id);
					}
			}	
			c++;
		}


		//Use Stat to find Paths and get the paths from Environement
		//

	//export abc=123
	//export abc
	// then env
	//echo $HOMEHA



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