#include "minishell.h"

void	lstadd_dlist(t_stack **alst, t_stack *new)
{
	// t_stack	*last;

	if (!new)
		return ;
	// last = *alst;
	new->prev = NULL;
	if ((*alst) == NULL)
		(*alst) = new;
	else
	{
		new->next = *alst;
		(*alst)->prev = new;
		*alst = new;
	}
	// if (alst)
	// {
	// 	new->next = *alst;
	// 	(*alst)->prev = new;
	// 	*alst = new;
	// }
	// else if (new)
	// 	*alst = new;
}

void	next_node(t_stack **list)
{
	if (!*list)
		return ;
	if ((*list)->next != NULL)
		(*list) = (*list)->next;
}
void	prev_node(t_stack **list)
{
	if (!*list)
		return ;
	if ((*list)->prev != NULL)
		(*list) = (*list)->prev;
}

t_stack	*lstnewc(void *data)
{
	t_stack	*p;
	p = (t_stack*)malloc(sizeof(t_stack));
	if (!p)
		return (NULL);
	p->data = data;
	p->next = NULL;
	p->prev = NULL;
	return (p);
}