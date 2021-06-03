/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 15:30:30 by aymaatou          #+#    #+#             */
/*   Updated: 2021/05/27 15:30:31 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int wait_proc (int in, int out,int fd,  char *cmd, char **arg,  t_node *head, t_source *src)
{
  pid_t pid;

  if ((pid = fork ()) == 0)
    {
      if (in != 0)
        {
          dup2 (in, 0);   
          close (in);
          // close (out);

        }

      else if (out != 1)
        {
          dup2 (out, 1);
          close (out);
          close (fd);
        //    write(2, "Now here", 8);
        }
      // if (src->foundred)
      //   red_open(head, src);
      // close(in);
      command_list(cmd, arg, head, src);
      exit(0);
    }
    // close (in);
    //  wait(&pid);
  return pid;
}

void fork_pips(t_source *src, t_node *head)
{
int i;
// pid_t pid;
int in, fd [2];
in = 0;
t_pipe *tmp;

tmp = head->pipe;
  i = 0;
  // int nb = src-> npipe == 1 ? 1 : src->npipe - 1;
  while(i < src->npipe)
    {
      pipe (fd);
      if (i == 0)
         { 
           wait_proc (in, fd [1], fd[0], head->cmd, head->arg ,head, src);
          close (fd [1]);
      
          }
      else 
      {  
          wait_proc(in, fd [1], fd[0], tmp->cmd ,tmp->arg , head, src);
          close (fd [1]);
          close (in);
         
      if (tmp->next == NULL)
        break;
      tmp = tmp->next;
      }
      in = fd[0];
    i++;
    }
    // write(2, "You here", 8);
  int pid = fork();
  if (pid == 0)
  {
      dup2 (in, 0);
      close(in);
      if (src->foundred)
        red_open(head, src);
      command_list(tmp->cmd, tmp->arg, head, src);
      exit (0);

  }
  close(in);
  close(fd[0]);
  close(fd[1]);
  // wait(NULL);
  
  i = -1;
  int status;
  while (++i < src->npipe + 1)
  {


    if (wait(&status) >= 0)
    {
        if (WIFEXITED(status))
        {
            /* Child process exited normally, through `return` or `exit` */
            // printf("\nChild process exited with %d status\n", WEXITSTATUS(status));
        }
    }
  }
  //   wait(NULL);
}
