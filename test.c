#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// typedef struct node {
//     int val;
//     struct node *next;
// }   node_t;

// void print_list(node_t *head) {

//     while (head != NULL) {
//         printf("%d\n", head->val);
//         head = head->next;
//     }
// }

void ft_wr_eq(char *s)
{
	if (s != NULL)
	{	int i = 0;
		int sign = 0;
		while (s[i] != 0)
		{
			if (s[i] == '=' && s[i + 1])
				{
					sign = 1;
					write(1,&s[i++], 1);
					write(1,"\"",1);
				}
			write(1,&s[i], 1);
                if (s[i] == '=' && !s[i + 1])
				{
                    write(1,"\"\"",2);
                    break ;
                }
		i++;
			if (!s[i] && sign == 1)
					write(1,"\"",1);
		}
	}
}
// void push(node_t *head, int val) {
//     while (head->next != NULL) {
//         head = head->next;
//     }

//     head->next = (node_t *) malloc(sizeof(node_t));
//     head->next->val = val;
//     head->next->next = NULL;
// }

int main() {
  
//   node_t *head;

// // head = NULL;
// head = (node_t *) malloc(sizeof(node_t));
// head->val = 23;
// head->next = NULL;

// push(head,8);
// head = head->next;

// printf("%d\n",head->val);

// // head->val = 1;
// // head->next = (node_t *) malloc(sizeof(node_t));
// // head->next->val = 2;
// // head->next->next = NULL;
// // push(head,9);
// // push(head,8);
// // print_list(head);
// // printf("%d\n",head->val);

    ft_wr_eq("Hello=abc");
    
  return 0;
}