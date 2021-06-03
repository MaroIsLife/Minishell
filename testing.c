#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int ac, char **av, char **env)
{
    char *cmd[2] = { "/bin/cat", NULL};
    char *cmd2[2] = { "/bin/ls", NULL};
    int fd[2];

    // pipe(fd);
    // if (fork() == 0)
    // {
    //     dup2(fd[1], 1);
    //     close(fd[0]);
    //     close(fd[1]);
    //     execve("/bin/cat", cmd, env);
    //     exit(0);
    // }
    // // wait(NULL);
    // if (fork() == 0)
    // {
    //     dup2(fd[0], 0);
    //     close (fd[1]);
    //      close(fd[0]);
    //     execve("/bin/ls", cmd2, env);
    //     exit(0);
    // }
    // close(fd[0]);
    // close(fd[1]);
    // wait(NULL);
    // wait(NULL);

    	if (fork() == 0)
		{	
				dup2(fd[1], 1);
				close(fd[0]);
				// command_list(head->cmd, head->arg, head, src);
				execve("/bin/cat", cmd, env);
                exit(0);
		}
		close(fd[1]);
		if (fork() == 0)
		{
			dup2(fd[0], 0);
			close(fd[1]);
             execve("/bin/ls", cmd2, env);
			// command_list(head->pipe->cmd, head->pipe->arg, head, src);
			exit(0);
		}
		close(fd[0]);
		wait(NULL);
		wait(NULL); 
}