#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



int main(int argc, char **argv, char **envp)
{

    struct stat sb;

    printf("%d\n",stat("/Users/mougnou/Desktop/minishell/path.txt",&sb));
    // int fd[2];
    // // fd[0] - read end
    // // fd[1] - write end (Where we will write the data)

    // if (pipe(fd) == -1)
    //     printf("Error\n");

    // int id = fork();
    // if (id == 0) // Child
    // {
    //     close(fd[0]); //Closing fd 0 cause i dont use it to read on this process
    //     int x;
    //     x = 3;
    //     write(fd[1],&x,1); // Writing in Child proccess to Parent process
    //     close(fd[1]);
    // }
    // else // Parent 
    // {
    //     int y;
    //     close(fd[1]);
    //     read (fd[0],&y,sizeof(int));
    //     close(fd[0]);
    //     printf("We got %d\n",y);
    // }

    // char *av[] = { "AYOUB",argv[2], argv[3], argv[4]};
    // int o;
    // static int  i = 99;
    // if (fork () == 0)
    // {   printf ("-- return : %d\n", execve(ft_strjoin("/Users/$USER/.brew/bin/", argv[1]), av ,envp));
    //     //write(2, &i - 48 , 1);
    // }
    // else
    //     wait(&o); 
    // printf ("return : %d\n", i);
    // return 0;
}