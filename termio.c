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


//gcc termio.c -lcurses -fsanitize=address

typedef struct s_stack
{
	void            *data;
	struct s_stack    *next;
}                t_stack;
void    print_stack(const t_stack *stack, void display_data(void *data))
{
	if (stack)
	{
		display_data(stack->data);
		print_stack(stack->next, display_data);
	}
}


void    push(t_stack **stack, void *data)
{
	t_stack    *temp;

	temp = malloc(sizeof(t_stack));
	temp->data = data;
	temp->next = NULL;
	if (!(stack))
		*stack = temp;
	else
	{
		temp->next = *stack;
		*stack = temp;
	}
}

void    *pop_st(t_stack **stack)
{
	void    *data;
	t_stack    *next;

	if (!(*stack))
		return (NULL);
	data = (*stack)->data;
	next = (*stack)->next;
	free(*stack);
	*stack = next;
	return (data);
}

void    *peek(const t_stack *stack)
{
	if (stack)
		return (stack->data);
	return (NULL);
}

void    clear_stack(t_stack **stack, void free_data(void *data))
{
	if (*stack)
	{
		clear_stack(&(*stack)->next, free_data);
		free_data((*stack)->data);
		free(*stack);
		*stack = NULL;
	}
}

int             get_char()
{
		char    c;
		int		total;
		struct	termios term; //, init; //init made to reset to default

		tcgetattr(0, &term); //get terminal attributes and store them in in the struct
		// tcgetattr(0, &init); //set terminal attributes in the struct
		term.c_lflag &= ~(ICANON); //Set to Non Canonical Maximum length is 4096
		term.c_lflag &= ~(ECHO); 
		term.c_cc[VMIN] = 0;  // VMIN   Minimum number of characters for noncanonical read (MIN).
		term.c_cc[VTIME] = 0;  //VTIME Timeout in deciseconds for noncanonical read (TIME).
		tcsetattr(0, TCSANOW, &term); //Set termios to Non Canonical
		total = 0;
		while (read(0, &c, 1) <= 0);
		total += c;
		while (read(0, &c, 1) > 0)
				total += c;
		// tcsetattr(0, TCSANOW, &init); //Activate termios to default
		return (total);
}

int             ft_puts(int d)
{
		return (write(1, &d, sizeof(int)));
}
void             ft_putchar(void *dt)
{
		write(1, dt, sizeof(int));
}
/*** FUNCTION STACK***/
void from_first_to_second(t_stack **first, t_stack **second)
{
		void    *data;
		data = pop_st(second);
		while (data)
		{
				push(first, data);
				data = pop_st(second);
		}
}
void  transfer_one_char(t_stack **first, t_stack **second)
{
		void    *data;
		data = pop_st(second);
		if (data)
				push(first, data);
}
void  delete_one_char(t_stack **st)
{
		void    *data;
		data = pop_st(st);
		free(data);
}
void  iprint(void *data)
{
		write(0, data, sizeof(int));
}
void  input(t_stack **left, t_stack **right)
{
		 write(0, "\n", 1);
		print_stack(*right, iprint);
		write(0, "\n", 1);
		clear_stack(left, free);
		clear_stack(right, free);
}
/*** ***/
int             main(void)
{
		int     d;
		int     *c;
		char    *s;
		int     len;
		int     iter;
		t_stack      *left, *right;
		len = 0;
		iter = 0;
		left = NULL;
		right = NULL;
		int lala;
		lala = 0;
		tgetent(NULL, getenv("TERM")); //Getting the Terminal description since termcap functionalities differ
		while (1)
		{
				d = get_char();
				// printf("%d\n",d);
				if (d >= 32 && d < 127)
				{
						c = malloc(sizeof(int));
						*c = d;
						push(&left, c);
						write(1, &d, sizeof(int));
						s = tgetstr("sc", NULL); // 'sc' string of commands to make the terminal save the current cursor position.
						write(1, s, strlen(s));
						print_stack(right, ft_putchar);
						//from_first_to_second(&left, &right);
						len++;
						iter++;
						s = tgetstr("rc", NULL); // 'rc' string of commands to make the terminal restore the last saved cursor position.
						write(1, s, strlen(s));
				}
				else if (d == KEY_UP)
						write(1, "\nKEY_UP\n", 8);
				else if (d == KEY_DOWN)
						write(1, "\nKEY_DOWN\n", 10);
				else if (d == KEY_LEFT)
				{
						if (iter > 0)
						{
								transfer_one_char(&right, &left);
								s = tgetstr("le", NULL);
								write(1, s, strlen(s));
								iter--;
						}
				}
				else if (d == KEY_RIGHT)
				{
						if (iter < len)
						{
								transfer_one_char(&left, &right);
								s = tgetstr("nd", NULL);
								write(1, s, strlen(s));
								iter++;
						}
				}
				else if (d == KEY_REMOVE)
				{
						if (iter > 0)
						{
								delete_one_char(&left);
								s = tgetstr("le", NULL);
								write(1, s, strlen(s));
								s = tgetstr("sc", NULL);
								write(1, s, strlen(s));
								s = tgetstr("ce", NULL);
								write(1, s, strlen(s));
								print_stack(right, ft_putchar);
								s = tgetstr("rc", NULL);
								write(1, s, strlen(s));
								iter--;
								len--;
						}
				}
				else if (d == ENTER)
				{
						while (iter > 0)
						{
								s = tgetstr("le", NULL);
								write(1, s, strlen(s));
								iter--;
						}
						s = tgetstr("ce", NULL);
						write(1, s, strlen(s));
						from_first_to_second(&left, &right);
						from_first_to_second(&right, &left);
						input(&left, &right);
						break;
				}
		}
		return (0);
}