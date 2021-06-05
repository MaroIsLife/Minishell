/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 15:30:30 by aymaatou          #+#    #+#             */
/*   Updated: 2021/06/03 18:51:29 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int spawn_proc (int in,  int *out, t_node *tmp, t_source *src)
{
  pid_t pid;

  if ((pid = fork ()) == 0)
    {
      if (in != 0)
        {
          dup2 (in, 0);
          close (in);
        }

      if (out[1] != 1)
        {
          dup2 (out[1], 1);
          close (out[1]);
          close (out[0]);
        }
     command_list(tmp->cmd, tmp->arg, src);
     exit(0);
    }

  return pid;
}

int spawn_proc2 (int in,  int *out, t_pipe *tmp, t_source *src)
{
  pid_t pid;

  if ((pid = fork ()) == 0)
    {
      if (in != 0)
        {
          dup2 (in, 0);
          close (in);
        }

      if (out[1] != 1)
        {
          dup2 (out[1], 1);
          close (out[1]);
          close (out[0]);
        }
    //  execvp (cmd->argv [0], (char * const *)cmd->argv);
     command_list(tmp->cmd, tmp->arg, src);
     exit(0);
    }

  return pid;
}

int
fork_pips (int n, t_node *head,  t_source *src)
{
  int i;
  pid_t pid;
  int in, fd [2];
  t_pipe *tmp = head->pipe;
  in = 0;
  for (i = 0; i < n - 1; ++i)
    {
      pipe (fd);
      if (i == 0)
        {
          pid = spawn_proc (in, fd , head ,src);
        // printf ("cmd: %s arg %s filename %s\n", tmp->cmd, tmp->arg[0], tmp->filename);
        }
      else
       {
       if (tmp->next == NULL)
          break;
         pid = spawn_proc2 (in, fd , tmp, src);
      //  printf ("cmd: %s arg %s filename %s\n", tmp->cmd, tmp->arg[0], tmp->filename);
       tmp = tmp->next;
       }
      close (fd [1]);
      in = fd [0];
      close(fd[0]);
    }

pid_t x;
x = fork();
if (x == 0)
    {
    dup2 (in, 0);
    close(in);
    // close (fd[0]);
    // close (fd[1]);
    // printf ("cmd: %s arg %s filename %s\n", tmp->cmd, tmp->arg[0], tmp->filename);
    command_list(tmp->cmd, tmp->arg, src);
    exit(0);
    } 
int ret; 
 waitpid(x,&ret, 0 );

int status;
i = -1;
 while (++i < src->npipe)
  {
    if ( waitpid(pid,&ret, 0 ) >= 0)
    {
        if (WIFEXITED(pid))
        {
            /* Child process exited normally, through `return` or `exit` */
            printf("\nChild process exited with %d status\n", WEXITSTATUS(status));
        }
    }
  }
  close (in);
  close (fd[0]);
  close (fd[1]);
 return (0);
}












































// int wait_proc (int in, int out,int fd,  char *cmd, char **arg,  t_node *head, t_source *src, int i)
// {
//   pid_t pid;

//   if ((pid = fork ()) == 0)
//     {
//       if (in != 0)
//         {
//           dup2 (in, 0);   
//           close (in);
//           close (fd);
//         }

//        if (out != 1)
//         {
//           dup2 (out, 1);
//           close (out);
//           close (fd);
       
//         }
//       if (src->foundred)
//         red_open(head, src);
//       // close(in);
//       command_list(cmd, arg, src);
//       // char *rc[] = {"/bin/echo"  , ft_itoa(i), NULL};
//       // execve("/bin/echo", rc, src->our_envp);
//       exit(0);
//           }
//       // close (fd);
//     //  wait(&pid);
//   return pid;
// }

// void fork_pips(t_source *src, t_node *head)
// {
// int i;
// // pid_t pid;
// int in, fd [2];
// in = 0;
// t_pipe *tmp;

// tmp = head->pipe;
//   i = 0;
//   // int nb = src-> npipe == 1 ? 1 : src->npipe - 1;
//   while(i < src->npipe)
//     {
//       pipe(fd);
//       if (i == 0)
//         {
//          printf( "here1 : cmd %s arg %s\n", head->cmd, head->arg[0]);
         
//          wait_proc (in, fd [1], fd[0], head->cmd, head->arg ,head, src, i);
//          close (fd [1]);
         
//         in = fd[0];
//         close (fd[0]);
//         }
//       else 
//       {  
//           if (tmp->next == NULL)
//             break;
//         printf("here2 : cmd %s arg %s\n", tmp->cmd, tmp->arg[0]);
          

//           wait_proc(in, fd [1], fd[0], tmp->cmd ,tmp->arg , head, src, i);
//           close (fd [1]);
//           close (in);
         
//            in = fd[0];
//           tmp = tmp->next;
//           }
//     i++;
//     }
//   int pid = fork();
//   if (pid == 0)
//   {
//       dup2 (in, 0);
//       close(in);
//        printf("here3 : cmd %s arg %s\n", tmp->cmd, tmp->arg[0]);
//       if (src->foundred)
//         red_open(head, src);
//       command_list(tmp->cmd, tmp->arg,src);
//       // char *rc[] = {"/bin/echo"  , ft_itoa(i), NULL};
//       // execve("/bin/echo", rc, src->our_envp);
//       exit (0);

//   }
//   close(in);
//   close (fd[1]);
//   close (fd[0]);
//   int ret;
//   waitpid(pid, &ret, 0);
//   i = -1;
//   int status;
//   while (++i < src->npipe)
//   {
//     if (wait(&status) >= 0)
//     {
//         if (WIFEXITED(status))
//         {
//             /* Child process exited normally, through `return` or `exit` */
//             // printf("\nChild process exited with %d status\n", WEXITSTATUS(status));
//         }
//     }
//   }
//   //   wait(NULL);
// }
