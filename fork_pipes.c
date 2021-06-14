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

void  red_open_with_pipe (t_filename *tmp)
{
 

  while (1)
  {
      write (2 , "filename: ", 10);
      write (2, tmp->filename, strlen(tmp->filename));
      write (2 , "\n", 1);
      if (tmp->next == NULL)
        break ;
      printf ("filename: %s\n",tmp->filename);
      tmp = tmp->next;
  }
}

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
      close(out[0]);
      if (tmp->first_filename != NULL)
       {
         write(2, "You are here 1\n", 15);; 
          red_open_pipe(tmp->first_filename);
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
      close(out[0]);
      if (tmp->pipef != NULL)
        { write(2, "You are here 2\n", 15);
          red_open_pipe(tmp->pipef);
        }
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
          pid = spawn_proc (in, fd , head ,src);
      else
      {
        if (tmp->next == NULL)
            break;
          pid = spawn_proc2 (in, fd , tmp, src);
        tmp = tmp->next;
       }
      close (fd [1]); 
      if (i != 0)
        close(in);
      in = fd [0];
    }

pid_t x;
x = fork();
if (x == 0)
    {
    dup2 (in, 0);
    close(in);
    close (fd[0]);

    if (tmp->pipef != NULL)
        { 
          write(2, "You are here 3\n", 15);
         red_open_pipe(tmp->pipef);
        }
    command_list(tmp->cmd, tmp->arg, src);

    exit(0);
    } 
int ret; 
 waitpid(x,&ret, 0 );

  close (fd[0]);
  i = 0;
  while (i < n - 1)
  {
   wait(NULL);
    i++;
  }
 return (0);
}




































