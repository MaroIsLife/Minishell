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

int spawn_proc (int in, int out, char *cmd, char **arg,  t_node *head, t_source *src)
{
  pid_t pid;

  if ((pid = fork ()) == 0)
    {
      if (in != 0)
        {
          dup2 (in, 0);
          
          close (in);
        // write(2, "You here", 8);
        //  close(out);
        }

      if (out != 1)
        {
          dup2 (out, 1);
          close (out);
          //close (in);
        //    write(2, "Now here", 8);
        }

      command_list(cmd, arg, head, src);
      exit(0);
    }
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
      write (2, "Your Here\n", 10);
      pipe (fd);
      if (i == 0)
         { 
          // printf("%d %s\n", i, head->cmd);

           spawn_proc (in, fd [1], head->cmd, head->arg ,head, src);
          close (fd [1]);
          // if (src->npipe == 1)
          //   {
          //       in = fd[0];
          //       break;
          //       }
          }
      else 
      {  
      // printf("%d %s\n", i, tmp->cmd);
          spawn_proc(in, fd [1], tmp->cmd ,tmp->arg , head, src);
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
      command_list(tmp->cmd, tmp->arg, head, src);
      exit (0);

  }
  close(in);
  int ret;
  wait(NULL);
  
  i = -1;
  while (++i < src->npipe - 1 )
    wait(NULL);
}
