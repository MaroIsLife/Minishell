#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int fd[2];
    // fd[0] - read end
    // fd[1] - write end (Where we will write the data)

    if (pipe(fd) == -1)
        printf("Error\n");

    int id = fork();
    if (id == 0) // Child
    {
        close(fd[0]); //Closing fd 0 cause i dont use it to read on this process
        int x;
        x = 3;
        write(fd[1],&x,1); // Writing in Child proccess to Parent process
        close(fd[1]);
    }
    else // Parent 
    {
        int y;
        close(fd[1]);
        read (fd[0],&y,sizeof(int));
        close(fd[0]);
        printf("We got %d\n",y);
    }

}