#include "minishell.h"

void	lstadd_dlist(t_stack **alst, t_stack *new)
{
	if (!new)
		return ;
	new->prev = NULL;
	if ((*alst) == NULL)
		(*alst) = new;
	else
	{
		new->next = *alst;
		(*alst)->prev = new;
		*alst = new;
	}
}

t_stack	*lstnewc(void *data)
{
	t_stack	*p;

	p = (t_stack *) malloc(sizeof(t_stack));
	if (!p)
		return (NULL);
	p->data = ft_strdup((char *)data);
	p->next = NULL;
	p->prev = NULL;
	free(data);
	return (p);
}
