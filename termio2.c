#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <termcap.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
# define KEY_UP 183
# define KEY_DOWN 184
# define KEY_LEFT  186
# define KEY_RIGHT 185
# define ENTER 10
# define KEY_REMOVE 127
# define KEY_TAB 9
# define CTRL_D 4

typedef struct s_stack
{
	char            *data;
	struct s_stack	*prev;
	struct s_stack	*next;
}                t_stack;

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

int main()
{
	int		d;
	char	*s;
	char 	*ret;
	int		iao;
	t_stack *head;

	iao = 0;
    tgetent(NULL, getenv("TERM")); //Getting the Terminal description since termcap functionalities differ
	ret = malloc(1 * sizeof(char));
	ret[0] = '\0';
	head = (t_stack *) malloc(sizeof(t_stack));
	head->prev = NULL;
	head->next = NULL;
	t_stack *tmp;
	while(1)
	{
		d = get_char();
		if (d >= 32 && d < 127)
		{
			ret = ft_strjoinchar(ret, d);
			write(1,&d,1);
			iao++;
		}
		else if (d == KEY_UP)
		{
			s = tgetstr("ch", NULL);
			write(1, s, strlen(s)); 
			s = tgetstr("dl", NULL); //Get the string entry id 'ce' means clear from the cursor to the end of the current line.
			write(1, s, strlen(s)); // execute the string entry id
			write(1, "KEY_UP\n", 8);
			// ret = "KEY UP";
			// tmp = tmp->prev;
			// ret = tmp->data;
		}
		else if (d == KEY_DOWN)
		{
			write(1, "KEY_DOWN\n", 10);
			ret = "KEY DOWN";
		}
		else if (d == ENTER)
		{
			// s = tgetstr("ch", NULL);
			// write(1, s, strlen(s)); 
			// s = tgetstr("dl", NULL); //Get the string entry id 'ce' means clear from the cursor to the end of the current line.
			// write(1, s, strlen(s)); // execute the string entry id
			head->data = ret;
			printf("\nHead data: %s\n",head->data);
			head->next = (t_stack *) malloc(sizeof(t_stack));
			tmp = head->next;
			tmp->prev = head;
			tmp->next = NULL;
			head = head->next;



			break ;
		}
	}
	printf("\nret: %s\n",ret);

    return (0);
}