#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


char		*ft_strjoin(char *dst, char *src)
{
	char	*p;
	int		size;
	int		b;
	int		i;

	if (dst == 0 || src == 0)
		return (0);
	i = -1;
	size = strlen((char *)dst) + strlen((char *)src) + 1;
	if (!(p = malloc(size * sizeof(char))))
		return (NULL);
	while (dst[++i] != '\0')
		p[i] = dst[i];
	b = 0;
	while (src[b] != '\0')
	{
		p[i] = src[b];
		i++;
		b++;
	}
	p[i] = '\0';
	// free(dst);
	// free(src);
	return (p);
}

int main(int argc, char **argv, char **envp)
{
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

    char *av[] = { "AYOUB",argv[2], argv[3], argv[4]};
    int o;
    static int  i = 99;
    if (fork () == 0)
    {   printf ("-- return : %d\n", execve(ft_strjoin("/Users/$USER/.brew/bin/", argv[1]), av ,envp));
        //write(2, &i - 48 , 1);
    }
    else
        wait(&o); 
    printf ("return : %d\n", i);
    return 0;
}