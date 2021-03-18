#include "minishell.h"
int		arg_if_space(char *s,int *i, t_source *src)
{
	if (s[*i] == ' ' && (src->dquotes == 1 || src->squotes == 1))
		src->re[src->re_b++] = s[*i];
	while (s[*i + 1] == ' ' && !(src->dquotes == 0 || src->squotes == 0))
		(*i)++;
	return (*i);
}
int count_argument(char *s, int offset, t_source *src) //CONVERT TO SPLIT?
{
	int i;
	int jump;
	int count;
	i = src->offset - 1;
	count = 0;
	jump = 0;
	if (s[0] == '\n')
		return 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' && i == 0)
		{
			src->dquotes = 1;
		}
		else if (s[i] == '\'' && i == 0)
			src->squotes = 1;
		else
			finding_quotes(s, i, src);
		if ((s[i] == ';' || s[i] == '|') && (src->dquotes == 0 && src->squotes == 0 && src->aslash == 0))
			return (count);
		if (s[i] == ' ' && src->dquotes == 0 && src->squotes == 0)
		{
			while (s[i] == ' ')
				i++;
			if ((s[i] == '|' || s[i] == ';') && src->dquotes == 0 && src->squotes == 0 && src->aslash == 0)
				return (count);
			if (s[i] == '\0' || s[i] == '\n')
				return (count);
			if (s[i] != '>' && jump == 0)
				count++;
			else
				jump = 0;
		}
		else if (s[i] == '>')
		{
			jump = 1;
			i++;
		}
		else
			i++;
	}
	return(count);
}
char	*find_file_name(int *i, char *s, t_source *src, t_node *head)
{
	int			b;
	static int 	allocate;
	(*i)++;
	b = 0;
	if (allocate == 1)
	{
		src->p->next = (t_filename *) malloc(sizeof(t_filename));
		src->p->next->next = NULL;
		src->p = src->p->next;
	}
	if (s[*i] == '>')
		printf("another >\n"); //Variable of double Red should be 1 and *i should be incremented
	while (s[*i] == ' ')
		(*i)++;	
	b = *i;
	while (s[b] != ' ' && s[b] != '\0' && s[b] != '\n')
		b++;
	src->p->filename = malloc((b + 1) * sizeof(char));
	b = 0;
	while (s[*i] != ' ' && s[*i] != '\0' && s[*i] != '\n')
		src->p->filename[b++] = s[(*i)++];
	src->p->filename[b] = '\0';
	allocate = 1;
	return (0);
}
char	*find_argument(char *s, t_node *head, t_source *src, char **envp)
{
	int		i;
	char	*re;
	i = src->offset;
	while (s[i] == ' ')
		i++;
	src->re = malloc((1024) * sizeof(char));
	src->re_b = 0;
	while (s[i] != '\n' && s[i] != '\0')
	{
		if (s[i] == ' ')
		{
			if (s[i] == ' ' && (src->dquotes == 1 || src->squotes == 1))
				arg_if_space(s, &i, src);
			else if (s[i] == ' ' && (src->dquotes == 0 || src->squotes == 0))
				break ;
		}
		else if ((s[i] == '|' || s[i] == ';') && (src->dquotes == 0 && src->aslash == 0 ))
		{
			if (src->squotes == 1)
				src->re[src->re_b++] = s[i];
			else
				break ;
		}
		else if (s[i] == '\"' && src->squotes == 0 && src->aslash == 0)
			finding_quotes(s, i, src);
		else if (s[i] == '\'' && src->dquotes == 0 && src->aslash == 0)
			finding_quotes(s, i, src);
		else if (s[i] == '$' && src->aslash == 0 && ft_isalpha(s[i + 1]) == 1 && src->squotes == 0)
			i = get_env_value_arg(s, envp, src, i) - 1;
		else if (s[i] == '\\' && src->aslash == 0)
		{
			src->tmp = finding_aslash(s,i, src);
			if (src->aslash == 0 && src->tmp != 1)
			{
				src->re[src->re_b++] = s[i];
				src->tmp = 0;
			}
		}
		else if (s[i] == '>' && src->aslash == 0 && src->dquotes == 0 && src->squotes == 0)
		{
			find_file_name(&i, s, src, head);
			// printf("%s\n",src->p->filename);
			continue ;
		}
		else if ((s[i] == '\"' || s[i] == '\'' || s[i] == '\\' || s[i] == ';' || s[i] == '|' || s[i] == '$' || s[i] == '>' || s[i] == '<') && src->aslash == 1)
		{
			src->re[src->re_b++] = s[i];
			src->aslash = 0;
		}
		else
			src->re[src->re_b++] = s[i];
		i++;
	}
	if (src->dquotes == 1 || src->squotes == 1 || src->aslash == 1)
	{
		printf("Error\n");
		printf("Dquotes: %d, Squotes: %d, Aslash: %d\n",src->dquotes,src->squotes,src->aslash);
	}
	src->offset = i;
	src->re[src->re_b] = '\0';
	return (src->re);
}