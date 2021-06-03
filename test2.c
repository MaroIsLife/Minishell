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
		char    c;
		int		total;
		struct	termios term , init; //init made to reset to default

		tcgetattr(0, &term); //get terminal attributes and store them in in the struct
		tcgetattr(0, &init); //set terminal attributes in the struct
		term.c_lflag &= ~(ICANON); //Set to Non Canonical, Reads instantly without waiting for "ENTER" key, Maximum length is 4096
		term.c_lflag &= ~(ECHO);  // Stops the keys read from printing in terminal
		term.c_cc[VMIN] = 0;  // VMIN   Minimum number of characters for noncanonical read (MIN).
		term.c_cc[VTIME] = 0;  //VTIME Timeout in deciseconds for noncanonical read (TIME).
		tcsetattr(0, TCSANOW, &term); //Set Atrributes of termios (Update Changes)
		total = 0;
		while (read(0, &c, 1) <= 0);
		total += c;
		while (read(0, &c, 1) > 0)
				total += c;
		tcsetattr(0, TCSANOW, &init); // Reset to Default because it doesn't work when cmd = cat, sort etc..
		return (total);
}

// void    print_prompt1()
// {
// 		write(1,"\033[0;32mMaro-&-Ma3toub$ \033[0;39m",sizeof("\033[0;32mMaro-&-Ma3toub$ \033[0;39m"));
// }


int ft_putc(int s)
{
	return write(1,&s,1);
}

char *term_loop(t_stack **head, t_stack **tmp, t_termc *termc)
{
	int		d;
	char	*s;
	// t_stack *tmp;
	// head = (t_stack *) malloc(sizeof(t_stack));
	// head->next = NULL;
	// head->prev = NULL;
	// tmp = head;
	// tmp = NULL;

	while(1)
	{
		d = get_char();
		// fprintf(stderr,"d = %d",d);
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
			g_global.ret = ft_strjoinchar(g_global.ret, d);
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
				// tputs(tgetstr("dm",NULL), 1, ft_putc);
				tputs(tgetstr("dc",NULL), 1, ft_putc);
				// tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putc);
				if (!termc->edit)
					g_global.ret = strdup(g_global.ret);
				g_global.ret[i] = '\0';
				// tputs(tgetstr("ed",NULL), 1, ft_putc);
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
				// printf("Made it here\n");
				g_global.ret = "";
				termc->help = 0;
				write(1, g_global.ret, strlen(g_global.ret));
			}
				termc->edit = 0;
			
			// else
			// 	g_global.ret[0] = 0;
			// s = tgoto(tgetstr("ch", NULL), 0 ,0);
			// write(1, s, strlen(s)); 
			// s = tgetstr("dl", NULL); //Get the string entry id 'ce' means clear from the cursor to the end of the current line.
			// write(1, s, strlen(s)); // execute the string entry id
		}
		else if (d == KEY_UP)
		{
			tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putc);
			tputs(tgetstr("dl",NULL), 1, ft_putc);
			print_prompt1();
			// if (tmp)
			// {
			// 	// fprintf(stderr, "%s", tmp->next);

			// 	write(1, tmp->data, strlen(tmp->data));
			// 	if(tmp->next != NULL)
			// 		tmp = tmp->next;
			// 	g_global.ret = tmp->data;
			// }
			if (*tmp)
				{
					// printf("made it here\n");
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
					write(1, (*tmp)->data, strlen((*tmp)->data));
				}
			termc->edit = 0;
			// else
			// 	g_global.ret = "";
			// else 
			// {
			// 	g_global.ret[0] = 0;
			// }
			// t_stack *tmp;
			// tmp = head;
			// while (tmp)
			// {
			// 	printf("%s\n", (char*)tmp->data);
			// 	tmp = tmp->next;
			// }
		}
		else if (d == ENTER)
		{
			// tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putc);
			// tputs(tgetstr("dl",NULL), 1, ft_putc);
			if (g_global.ret == NULL)
			{
				write(1,"\n",1);
				print_prompt1();
				continue ;
			}
			write(1,"\n",1);
			// print_prompt1();
			// s = tgetstr("ch", NULL);
			// write(1, s, strlen(s)); 
			// s = tgetstr("dl", NULL); //Get the string entry id 'ce' means clear from the cursor to the end of the current line.
			// write(1, s, strlen(s)); // execute the string entry id
				// fprintf(stderr, "Else made it here");
			if (g_global.ret[0] != 0)
			{
				lstadd_dlist(head, lstnewc(strdup(g_global.ret)));
				// fprintf(stderr, "%s", tmp);
				*tmp = *head;
				termc->help = 0;
				// printf("Data: %s\n",(*head)->data);
				// printf("%s\n",tmp->data);
			}
			termc->edit = 0;
			// if (termc->help == 0)
			// strcpy(s, g_global.ret);
			s = g_global.ret;
			g_global.ret = ft_strdup("");
			return (s);
			// continue ;
		}
	}
	// printf("\ng_global.ret: %s\n",ret);
    return (0);	
}