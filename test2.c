# include <stdio.h>
# include <termios.h>
#include <stdio.h>
# include <termcap.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include "minishell.h"
# define KEY_UP 183
# define KEY_DOWN 184
# define KEY_LEFT  186
# define KEY_RIGHT 185
# define ENTER 10
# define KEY_REMOVE 127
# define KEY_TAB 9
# define CTRL_D 4



char    *ft_strjoinchar(char *s, char c)
{
    int        i;
    char    *str;
    i = 0;

	if (s == NULL)
	{
		str = malloc(2);
		str[0] = c;
		str[1] = 0;
		return (str);
	}
    while (s[i])
		i++;
    if (!(str = (char *)malloc(i + 2)))
        return (0);
    i = 0;
    while (s[i] != '\0')
	{
        str[i] = s[i];
		i++;
	}
    str[i] = c;
    str[i + 1] = '\0';
    // free(s);
    return (str);
}

int             get_char()
{
	char			c;
	int				total;
	struct termios	term;
	struct termios	init;

	tcgetattr(0, &term);
	tcgetattr(0, &init);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	total = 0;
	while (read(0, &c, 1) <= 0)
		;
	total += c;
	while (read(0, &c, 1) > 0)
		total += c;
	tcsetattr(0, TCSANOW, &init);
	return (total);
}

int	ft_putc(int s)
{
	return (write(1, &s, 1));
}


void	ft_key_remove (t_var *var)
{
	int i;

	i = 0;
	
	if (strlen(g_global.ret) > 0)
	{
		while (i < (strlen(g_global.ret) - 1))
			i++;
		tputs(tgetstr("le",NULL), 1, ft_putc);
		tputs(tgetstr("dc",NULL), 1, ft_putc);
		//check Heeeere.
		if (!var->edit)
			{
				// free (g_global.ret);
				// g_global.ret = NULL;
				// puts(g_global.ret);
				// g_global.ret = strdup(g_global.ret);
				// puts(g_global.ret);
			}
		g_global.ret[i] = '\0';
	}
}
void 	ft_key_down(t_stack **tmp, t_var *var)
{
	char *tmp2;

	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putc);
	tputs(tgetstr("dl",NULL), 1, ft_putc);
	print_prompt1();
	if (*tmp && (*tmp)->prev)
	{
		*tmp = (*tmp)->prev;
		tmp2 = g_global.ret;
		g_global.ret = ft_strdup((char *)(*tmp)->data);
		free(tmp2);
		write(1, (*tmp)->data, strlen((*tmp)->data));
	}
	else
	{
		tmp2 = g_global.ret;
		g_global.ret = ft_strdup("");
		var->help = 0;
		free(tmp2);
		write(1, g_global.ret, strlen(g_global.ret));
	}
		var->edit = 0;
}

void	ft_key_up_norm(t_stack **tmp, t_var *var)
{
	char *tmp2;

	tmp2 = g_global.ret;
	g_global.ret = ft_strdup((char*)(*tmp)->data);
	free(tmp2);
	var->help = 1;
}

void ft_key_up(t_stack **tmp, t_var *var)
{
	char *tmp2;	
	
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putc);
	tputs(tgetstr("dl",NULL), 1, ft_putc);
	print_prompt1();
	if (*tmp)
		{
			if (!(*tmp)->prev && !var->help)
				ft_key_up_norm(tmp, var);
			else
			{
				tmp2 = g_global.ret;
				if((*tmp)->next)
					*tmp = (*tmp)->next;
				g_global.ret = ft_strdup((char*)(*tmp)->data);
				free(tmp2);
			}
			if ((*tmp)->data != NULL)
			{
				write(1, (*tmp)->data, strlen((*tmp)->data));
			}
		}
	var->edit = 0;
}

char *ft_key_enter(t_stack **head, t_stack **tmp, t_var *var)
{
	char *s;

	write(1,"\n",1);
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
	int d;

	d = get_char();
	if (d == 4)
		{
			if (g_global.ret == NULL)
			{
				write(1,"exit",4);
				exit(0);
			}
		}
	if (d >= 32 && d < 127)
		{
			char *tmp;
			tmp = g_global.ret;
			g_global.ret = ft_strjoinchar(g_global.ret, d);
			free (tmp);
			write(1, &d ,1);
		}
	return (d);
}
char *term_loop(t_stack **head, t_stack **tmp, t_var *var)
{
	while(1)
	{
		var->d = ret_d();	
		if (var->d == KEY_REMOVE)
		{
			if (g_global.ret == NULL)
				continue ;
			ft_key_remove (var);
		}
		else if (var->d== KEY_DOWN)
			ft_key_down(tmp, var);
		else if (var->d == KEY_UP)
			ft_key_up(tmp, var);
		else if (var->d == ENTER)
		{
			if (g_global.ret == NULL)
			{
				write(1,"\n",1);
				print_prompt1();
				continue ;
			}
			return (ft_key_enter(head, tmp, var));
		}
	}
    return (0);	
}