#include "minishell.h"

// char    *read_line()
// {
// 	char    *cmd;
// 	char	buf[1024];
// 	int 	cmdlen;


// cmd = malloc(1024 * sizeof(char));
// cmdlen = read(0,&buf,1024); //leaks
// while (cmdlen != 0)
// {
// 	if (cmdlen == -1)
// 	{
// 		printf("Error: %s\n",strerror(errno));
// 		exit(1);
// 	}
// 	strcpy(cmd, buf);
// 	if (cmd == NULL)
// 	{
// 		printf("Error: %s\n",strerror(errno));
// 		exit(1);
// 	}
// 	if (cmd[cmdlen - 1] == '\n')
// 	{
// 			cmd[cmdlen] = '\0';
// 			return cmd;
// 	}
// 	cmdlen = read(0,&buf,1024);
// }
// 	 return (0);
// }

char    *ft_strjoinchar(char *s, char c)
{
    int        i;
    char    *str;
    i = 0;
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
		struct	termios term; //, init; //init made to reset to default

		tcgetattr(0, &term); //get terminal attributes and store them in in the struct
		// tcgetattr(0, &init); //set terminal attributes in the struct
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
		// tcsetattr(0, TCSANOW, &init); //WA ZABI ACH HAD L9LAWI!?!?!
		return (total);
}

int ft_putc(int s)
{
	return write(1,&s,1);
}

char    *read_line()
{

	int		d;
	char	*s;
	char 	*ret;
	t_stack *head;
	t_stack *tmp;
	int help = 0;
	int edit = 0;
    tgetent(NULL, getenv("TERM")); //Getting the Terminal description since termcap functionalities differ
	ret = malloc(1 * sizeof(char));
	ret[0] = '\0';
	// t_stack *tmp;
	// head = (t_stack *) malloc(sizeof(t_stack));
	// head->next = NULL;
	// head->prev = NULL;
	// tmp = head;
		print_prompt1();
	head = NULL;
	tmp = NULL;
	while(1)
	{
		d = get_char();
		if (d >= 32 && d < 127)
		{
			ret = ft_strjoinchar(ret, d);
			write(1,&d,1);
		}
		else if (d == KEY_REMOVE)
		{
			int i;

			i = 0;
			if (strlen(ret) > 0)
			{
				while (i < (strlen(ret) - 1))
					i++;
				ret[i] = '\0';
				tputs(tgetstr("le",NULL), 1, ft_putc);
				// tputs(tgetstr("dm",NULL), 1, ft_putc);
				tputs(tgetstr("dc",NULL), 1, ft_putc);
				// tputs(tgetstr("ed",NULL), 1, ft_putc);
			}
		}
		else if (d == KEY_DOWN)
		{
			tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putc);
			tputs(tgetstr("dl",NULL), 1, ft_putc);
			print_prompt1();
			// if (tmp)
			// {
	
			// 	write(1, tmp->data, strlen(tmp->data));
			// 	if (tmp->prev != NULL)
			// 		tmp = tmp->prev;
			// 	ret = tmp->data;
			// }
			if (tmp && tmp->prev)
				{
					tmp = tmp->prev;
					ret = (char*)tmp->data;
					write(1, tmp->data, strlen(tmp->data));
				}
				else
				{
					ret = "";
					help = 0;
					write(1, ret, strlen(ret));
				}

			// else
			// 	ret[0] = 0;
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
			// 	ret = tmp->data;
			// }
			if (tmp)
				{
					if (!tmp->prev && !help)
					{
						ret = (char*)tmp->data;
						help = 1;
					}
					else
					{
						if(tmp->next)
							tmp = tmp->next;
						ret = (char*)tmp->data;		
					}
					write(1, tmp->data, strlen(tmp->data));
				}
			// else 
			// {
			// 	// fprintf(stderr, "Else made it here");
			// 	ret[0] = 0;
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
			write(1,"\n",1);
			print_prompt1();
			// s = tgetstr("ch", NULL);
			// write(1, s, strlen(s)); 
			// s = tgetstr("dl", NULL); //Get the string entry id 'ce' means clear from the cursor to the end of the current line.
			// write(1, s, strlen(s)); // execute the string entry id
			if (ret[0] != 0)
			{
				// head->data = ret;
				// head->next = (t_stack *) malloc(sizeof(t_stack));
				// head->next->next = NULL;
				// head->next->prev = head;
				// head = head->next;
				// tmp = head;
				lstadd_dlist(&head, lstnewc(ret));
				tmp = head;
			}
			ret = "";

			// tmp = head->next;
			// tmp->prev = head;
			// tmp->next = NULL;
			// head = head->next;
			return (ret);
		}
	}
	// printf("\nret: %s\n",ret);
    return (ret);	
}