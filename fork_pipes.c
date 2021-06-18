/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 15:30:30 by aymaatou          #+#    #+#             */
/*   Updated: 2021/06/18 23:36:05 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/**
 *  TO DO: SWICH BETWEEN FILE DISCREPTORS (in out) with (fd - fd2)
 */
void  return_fun()
{
  if (WIFSIGNALED(g_global.id))
		g_global.return_value = WTERMSIG(g_global.id) + 128;
	if (WIFEXITED(g_global.id))
		g_global.return_value = WEXITSTATUS(g_global.id);
}

int first_child (int in,  int *out, t_node *tmp, t_source *src)
{
  int pid;
  
  pid = fork ();
  if (pid== 0)
    {
      if (tmp->first_filename != NULL)
          red_open_pipe(tmp->first_filename);
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
     command_list(tmp->cmd, tmp->arg, src);
     exit(g_global.return_value);
    }
  return pid;
}

int inner_childs(int in,  int *out, t_pipe *tmp, t_source *src)
{
  int pid;
  
  pid = fork ();
  if (pid== 0)
    {
      if (tmp->pipef != NULL)
          red_open_pipe(tmp->pipef);
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
     command_list(tmp->cmd, tmp->arg, src);
     exit(g_global.return_value);
    }
  return pid;
}

void	last_child(int in, int *fd, t_pipe *tmp, t_source *src)
{
	int x;
 	int i;
	int ret; 
	
	x = fork();
	if (x == 0)
    {
		if (tmp->pipef != NULL)
			red_open_pipe(tmp->pipef);
    	dup2 (in, 0);
    	close(in);
    	close (fd[0]);
		command_list(tmp->cmd, tmp->arg, src);
    	exit(g_global.return_value);
    } 
  	close (fd[0]);
 	i = 0;
 	while (i < src->npipe + 1)
  	{
   		wait(&g_global.id);
    	i++;
      return_fun();
   }
}

void fork_pips (int n, t_node *head,  t_source *src)
{
  int i;
  int in;
  t_pipe *tmp;
  
  tmp = head->pipe;
  in = 0;
  i = 0;	
  while(i < n - 1)
    {
      pipe (src->fd);
      if (i == 0)
          first_child (in, src->fd , head ,src);
      else
      {
        if (tmp->next == NULL)
            break;
          inner_childs (in, src->fd , tmp, src);
        tmp = tmp->next;
       }
      close (src->fd [1]); 
      if (i++ != 0)
        close(in);
      in = src->fd [0];
    }
	last_child(in, src->fd, tmp, src);
}
