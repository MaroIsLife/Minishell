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
        }

      if (out != 1)
        {
          dup2 (out, 1);
          close (out);
        //    write(2, "Now here", 8);
        }

      command_list(cmd, arg, head, src);
      exit(0);
    }
     wait(&pid);
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
 int nb = src-> npipe == 1 ? 1 : src->npipe - 1;
  while(i < nb )
    {
      pipe (fd);
      if (i == 0)
         { spawn_proc (in, fd [1], head->cmd, head->arg ,head, src);
          close (fd [1]);
          if (src->npipe == 1)
            {
                in = dup(fd[0]);
                close(fd[0]);
                break;}
         }
      else 
      {  
        //   printf("%s\n", tmp->cmd);
          spawn_proc(in, fd [1], tmp->cmd ,tmp->arg , head, src);
          close (fd [1]);
         }
      tmp = tmp->next;
      if (tmp->next == NULL)
        break;
      in = fd [0];
      close (fd[0]);
    i++;
    }

    if (in != 0)
        dup2 (in, 0);
  command_list(tmp->cmd, tmp->arg, head, src);
  exit (0);
  wait(NULL);
  i = -1;
//   while (++i < src->npipe)
//     wait(NULL);
}
