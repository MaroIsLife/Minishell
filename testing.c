#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


struct command
{
  const char **argv;
};

int spawn_proc (int in,  int *out, struct command *cmd)
{
  pid_t pid;

  if ((pid = fork ()) == 0)
    {
      if (in != 0)
        {
          dup2 (in, 0);
          close (in);
          // close (out[1]);
        }

      if (out[1] != 1)
        {
          dup2 (out[1], 1);
          close (out[1]);
          close (out[0]);
          // close (in);
        }

     execvp (cmd->argv [0], (char * const *)cmd->argv);
     exit(0);
    }
  
  return pid;
}

int
fork_pipes (int n, struct command *cmd)
{
  int i;
  pid_t pid;
  int in, fd [2];

  in = 0;
  for (i = 0; i < n - 1; ++i)
    {
      pipe (fd);
      if (i == 0)
       spawn_proc (in, fd , cmd + i);
      else
        spawn_proc (in, fd , cmd + i);
      close (fd [1]); 
      close(in);
      in = fd [0];
      // close(fd[0]);
    }

pid_t x;
x = fork();
if (x == 0)
    {
    dup2 (in, 0);
    close(in);
    close (fd[0]);
    close(fd[1]);
    execvp (cmd [i].argv [0], (char * const *)cmd [i].argv);
    exit(0);
    } 
  close (in);
  close (fd[0]);
  close (fd[1]);
int ret; 
 waitpid(x,&ret, 0 );
i = 0;
while (i < n - 1)
 {
   wait(NULL);
 i++;
 }
 return (0);
}

int main(int ac, char **av, char **env)
{


  // const char *ls[] = { "ls", NULL };
  // const char *awk[] = { "cat", NULL };
  // const char *sort[] = {  "ls", NULL };
  // const char *uniq[] = {  "ls", NULL};

  const char *ls[] = { "echo","1", NULL };
  const char *awk[] = { "echo","2", NULL };
  const char *sort[] = {  "echo","3", NULL };
  const char *uniq[] = {  "echo","4", NULL};
    // struct command cmd [] = { {ls}, {awk}, {sort}, {uniq} };
  struct command cmd [] = { {awk}, {ls},  {sort}, {uniq} };

  return 
  fork_pipes (4, cmd);



}