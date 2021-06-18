#include "minishell.h"

void	ft_key_up_norm(t_stack **tmp, t_var *var)
{
	char	*tmp2;

	tmp2 = g_global.ret;
	g_global.ret = ft_strdup((char *)(*tmp)->data);
	free(tmp2);
	var->help = 1;
}

void	ft_key_up(t_stack **tmp, t_var *var)
{
	char	*tmp2;	

	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putc);
	tputs(tgetstr("dl", NULL), 1, ft_putc);
	print_prompt1();
	if (*tmp)
	{
		if (!(*tmp)->prev && !var->help)
			ft_key_up_norm(tmp, var);
		else
		{
			tmp2 = g_global.ret;
			if ((*tmp)->next)
				*tmp = (*tmp)->next;
			g_global.ret = ft_strdup((char *)(*tmp)->data);
			free(tmp2);
		}
		if ((*tmp)->data != NULL)
		{
			write(1, (*tmp)->data, strlen((*tmp)->data));
		}
	}
	var->edit = 0;
}

char	*ft_key_enter(t_stack **head, t_stack **tmp, t_var *var)
{
	char	*s;

	write(1, "\n", 1);
	if (g_global.ret[0] != 0)
	{
		lstadd_dlist(head, lstnewc(strdup(g_global.ret)));
		*tmp = *head;
		var->help = 0;
	}
	var->edit = 0;
	s = ft_strdup(g_global.ret);
	return (s);
}

int ret_d(void)
{
	int		d;
	char	*tmp;

	d = get_char();
	if (d == 4)
	{
		if (g_global.ret == NULL)
		{
			write(1, "exit", 4);
			exit(0);
		}
	}
	if (d >= 32 && d < 127)
	{
		tmp = g_global.ret;
		g_global.ret = ft_strjoinchar(g_global.ret, d);
		free (tmp);
		write(1, &d, 1);
	}
	return (d);
}

char	*term_loop(t_stack **head, t_stack **tmp, t_var *var)
{
	while (1)
	{
		var->d = ret_d();
		if (var->d == KEY_REMOVE)
		{
			if (g_global.ret == NULL)
				continue ;
			ft_key_remove (var);
		}
		else if (var->d == KEY_DOWN)
			ft_key_down(tmp, var);
		else if (var->d == KEY_UP)
			ft_key_up(tmp, var);
		else if (var->d == ENTER)
		{
			if (g_global.ret == NULL)
			{
				write(1, "\n", 1);
				print_prompt1();
				continue ;
			}
			return (ft_key_enter(head, tmp, var));
		}
	}
	return (0);
}
