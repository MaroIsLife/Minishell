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

char *term_loop(t_stack **head, t_stack **tmp, t_termc *termc)
{
	int		d;
	char	*s;

	while(1)
	{
		d = get_char();
		if (d == 4)
		{
			if (g_global.ret == NULL)
			{
				write(1,"exit",4);
				exit(0);
			}
		}
		else if (d >= 32 && d < 127)
		{
			char *tmp;
			tmp = g_global.ret;
			g_global.ret = ft_strjoinchar(g_global.ret, d);
			free (tmp);
			write(1, &d ,1);
		}
		else if (d == KEY_REMOVE)
		{
			int i;

			i = 0;
			if (g_global.ret == NULL)
				continue ;
			if (strlen(g_global.ret) > 0)
			{
				while (i < (strlen(g_global.ret) - 1))
					i++;
				tputs(tgetstr("le",NULL), 1, ft_putc);
				tputs(tgetstr("dc",NULL), 1, ft_putc);
				//check Heeeere.
				if (!termc->edit)
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
		else if (d == KEY_DOWN)
		{
			tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putc);
			tputs(tgetstr("dl",NULL), 1, ft_putc);
			print_prompt1();
			if (*tmp && (*tmp)->prev)
			{
				*tmp = (*tmp)->prev;
				g_global.ret = (char *)(*tmp)->data;
				write(1, (*tmp)->data, strlen((*tmp)->data));
			}
			else
			{
				g_global.ret = ft_strdup("");
				termc->help = 0;
				write(1, g_global.ret, strlen(g_global.ret));
			}
				termc->edit = 0;
		}
		else if (d == KEY_UP)
		{
			tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putc);
			tputs(tgetstr("dl",NULL), 1, ft_putc);
			print_prompt1();
			if (*tmp)
				{
					if (!(*tmp)->prev && !termc->help)
					{
						g_global.ret = (char*)(*tmp)->data;
						termc->help = 1;
					}
					else
					{
						if((*tmp)->next)
							*tmp = (*tmp)->next;
						g_global.ret = (char*)(*tmp)->data;
					}
					if ((*tmp)->data != NULL)
					{
			
						write(1, (*tmp)->data, strlen((*tmp)->data));}
				}
			termc->edit = 0;
		}
		else if (d == ENTER)
		{
			if (g_global.ret == NULL)
			{
				write(1,"\n",1);
				print_prompt1();
				continue ;
			}
			write(1,"\n",1);
			if (g_global.ret[0] != 0)
			{
				lstadd_dlist(head, lstnewc(strdup(g_global.ret)));
				*tmp = *head;
				termc->help = 0;
			}
			termc->edit = 0;
			s = ft_strdup(g_global.ret);
			free(g_global.ret);
			return (s);
		}
	}
    return (0);	
}