// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   terminal2.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: abenouda <abenouda@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/04/25 14:25:30 by abenouda          #+#    #+#             */
// /*   Updated: 2021/04/26 13:52:33 by abenouda         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// # define KEY_UP 183
// # define KEY_DOWN 184
// # define KEY_LEFT  186
// # define KEY_RIGHT 185
// # define ENTER 10
// # define KEY_REMOVE 127
// # define BOLD_CYAN "\e[1;36m"
// # define RESET_CLR "\e[0m"

// int ft_putc(int c)
// {
// 	return write(1, &c, 1);
// }

// void printstr(char *s)
// {
// 	int i;
	
// 	i = -1;
// 	while (s[++i])
// 		ft_putc(s[i]);
// }

// void term_prompt()
// {
// 	write(1, BOLD_CYAN"Minishell->>> "RESET_CLR, 25);
// }

// int		get_char()
// {
// 	char			c;
// 	int				total;
// 	struct termios	term;
// 	struct termios	backup;
	
// 	tgetent(NULL, getenv("TERM"));
// 	tcgetattr(0, &term);
// 	tcgetattr(0, &backup);
// 	term.c_lflag &= ~(ICANON | ECHO);
// 	term.c_cc[VMIN] = 0; 
// 	term.c_cc[VTIME] = 0; 
// 	tcsetattr(0, TCSANOW, &term);
// 	total = 0;
// 	while (read(0, &c, 1) <= 0);
// 	total += c;
// 	while (read(0, &c, 1) > 0)
// 			total += c;
// 	tcsetattr(0, TCSANOW, &backup);
// 	return (total);
// }

// int term_loop(t_all *all)
// {
// 	t_dlist	*tmp;
// 	int		c;
// 	int		help;
// 	int		edit;
// 	char	*s;
	
// 	help = edit = 0;
// 	s = "";
// 	term_prompt();
// 	tmp = all->l_history;
// 	while (1)
// 	{
// 		c = get_char();
// 		if (c == KEY_UP)
// 		{
// 			tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putc);
// 			tputs(tgetstr("dl", NULL), 1, ft_putc);
// 			term_prompt();
// 			if (tmp)
// 			{
// 				if (!tmp->prev && !help)
// 				{
// 					s = (char*)tmp->cam;
// 					help = 1;
// 				}
// 				else
// 				{
// 					if(tmp->next)
// 						next_node(&tmp);
// 					s = (char*)tmp->cam;		
// 				}
// 				printstr(s);
// 			}
// 			edit = 0;
// 			continue ;
// 		}
// 		else if (c == KEY_DOWN)
// 		{
// 			tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putc);
// 			tputs(tgetstr("dl", NULL), 1, ft_putc);
// 			term_prompt();
// 			if (tmp && tmp->prev)
// 			{
// 				prev_node(&tmp);
// 				s = (char*)tmp->cam;
// 			}
// 			else
// 			{
// 				s = all->line;
// 				help = 0;
// 			}
// 			printstr(s);
// 			edit = 0;
// 			continue ;
// 		}
// 		else if (c == KEY_LEFT)   
// 		{
// 			// tputs(all->tccmd->nd, 1, ft_putc);
// 			continue ;
// 		}
// 		else if (c == KEY_RIGHT)
// 		{
// 			// tputs(all->tccmd->le, 1, ft_putc);
// 			continue ;
// 		}
// 		else if (c == KEY_REMOVE)
// 		{
// 			int l;
			
// 			if (!help)
// 			{
// 				l = ft_strlen(all->line);
// 				if (l > 0)
// 				{
// 					tputs(tgetstr("le", NULL), 1, ft_putc);
// 					tputs(tgetstr("dm", NULL), 1, ft_putc);
// 					tputs(tgetstr("dc", NULL), 1, ft_putc);
// 					tputs(tgetstr("ed", NULL), 1, ft_putc);
// 					tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putc);
// 					term_prompt();
// 					all->line[l - 1] = '\0';
// 					write(1, all->line, l - 1);
// 				}
// 			}
// 			else
// 			{
// 				l = ft_strlen(s);
// 				if (l > 0)
// 				{
// 					tputs(tgetstr("le", NULL), 1, ft_putc);
// 					// tputs(tgetstr("dm", NULL), 1, ft_putc);
// 					tputs(tgetstr("dc", NULL), 1, ft_putc);
// 					// tputs(tgetstr("ed", NULL), 1, ft_putc);
// 					tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putc);
// 					term_prompt();
// 					if (!edit)
// 						s = ft_strdup(s);
// 					s[l - 1] = '\0';
// 					write(1, s, l - 1);
// 				}
// 			}
// 			edit = 1;
// 		}
// 		else if (c == ENTER)
// 		{
// 			if (tmp && help)
// 			{
// 				free(all->line);
// 				if (edit)
// 					all->line = s;
// 				else
// 					all->line = ft_strdup(s);
// 			} 
// 			write(1, "\n", 1);
// 			edit = 0;
// 			return (1);
// 		}
// 		else if (c >= 32 && c < 127)
// 		{
// 			write(1, &c, 1);
// 			if (!help)
// 				all->line = ft_strjoinchar(all->line, c);
// 			else
// 				s = ft_strjoinchar(s, c);
// 		}
// 	}
// }


//BENOUDA'S TERMINAL 2