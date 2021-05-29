#include "minishell.h"

int finding_quotes_cmd(char *s,int i, t_source *src)
{
	if (s[i] == '\"' && i == 0)
		src->dquotes = 1;
	else if (s[i] == '\'' && i == 0 && src->dquotes == 0)
		src->squotes = 1;
	else if (s[i] == '\"' && src->squotes == 0 && src->aslash == 0)
		{
			if (src->dquotes == 0)
			{
				src->dquotes = 1;
			}
			else
				src->dquotes = 0;
		}
		else if (s[i] == '\'' && src->dquotes == 0)
		{
			if (src->squotes == 0)
				src->squotes = 1;
			else
				src->squotes = 0;
		}
		finding_aslash(s, i, src);
	return 0;
}

int finding_quotes(char *s,int i, t_source *src)
{
	if (s[i] == '\"' && src->squotes == 0 && src->aslash == 0)
	{
			if (src->dquotes == 0)
			{
				src->dquotes = 1;
			}
			else
				src->dquotes = 0;
	}
	else if (s[i] == '\'' && src->dquotes == 0 && src->aslash == 0)
	{
			if (src->squotes == 0)
			{
				src->squotes = 1;
			}
			else
				src->squotes = 0;
	}
	finding_aslash(s, i, src);
	return 0;
}

int		finding_aslash(char *s, int i, t_source *src)
{
		if (s[i] == '\\' && s[i + 1] == '\'' && src->dquotes == 1)
			src->aslash = 0;
		else if (s[i] == '\\' && (s[i + 1] == '\"' || s[i + 1] == '\\' || s[i + 1] == '\'' || s[i + 1] == '$' || s[i + 1] == '>' || s[i + 1] == '<' || s[i + 1] == ';') && src->aslash == 0 && src->squotes == 0)
		{
			src->aslash = 1;
		}
		else if (s[i] == '\\' && (src->dquotes == 0 && src->squotes == 0))
		{
			if (ft_isascii(s[i + 1]) == 0)
				src->founderror = 1;
			else
				return (1);
		}
		else
			src->aslash = 0; //convert to return 0 or 1 for norminette?
	return 0;
}
int		finding_aslash2(char *s, int i, t_source *src)
{
		if (s[i] == '\\' && s[i + 1] == '\'' && src->dquotes == 1)
			src->aslash = 0;
		else if (s[i] == '\\' && (s[i + 1] == '\"' || s[i + 1] == '\\' || s[i + 1] == '\'' || s[i + 1] == '$' || s[i + 1] == '>' || s[i + 1] == '<' || s[i + 1] == ';') && src->aslash == 0 && src->squotes == 0)
		{
			src->aslash = 1;
		}
		else
			src->aslash = 0; //convert to return 0 or 1 for norminette?
	return 0;
}
int finding_quotes2(char *s,int i, t_source *src)
{
	if (s[i] == '\"' && src->squotes == 0 && src->aslash == 0)
	{
			if (src->dquotes == 0)
			{
				src->dquotes = 1;
			}
			else
				src->dquotes = 0;
	}
	else if (s[i] == '\'' && src->dquotes == 0 && src->aslash == 0)
	{
			if (src->squotes == 0)
			{
				src->squotes = 1;
			}
			else
				src->squotes = 0;
	}
	finding_aslash2(s, i, src);
	return 0;
}

void	find_for_split(char *cmd, t_source *src)
{
	int i;
	char **token;

	i = 0;
	src->foundpipe = 0;
	src->npipe = 0;
	src->nred = 0;
	src->dquotes = 0;
	src->foundred = 0;
	src->squotes = 0;

	while (cmd[i] != '\0')
	{
		finding_quotes_cmd(cmd,i, src);
		if (cmd[i] == '|' && src->dquotes == 0 && src->squotes == 0 && src->aslash == 0)
		{
			src->foundpipe = 1;
			src->npipe++;
		}
		else if ((cmd[i] == '>'|| cmd[i] == '<') && src->dquotes == 0 && src->squotes == 0 && src->aslash == 0)
		{
			src->foundred = 1;
			src->nred++;
		}
		i++;
	}
	if (src->dquotes == 1 || src->squotes == 1 || src->aslash == 1)
		src->founderror = 1;
	// printf("%d\n",g_find.ndquotes); //Bugged to fix later
}

int		find_equal_length(char **envp,int c, int b)
{
	int length;

	length = 0;

	while (envp[c][b] != '=' && envp[c][b] != '\0')
	{
		b++;
		length++;
	}
	
	return length; 
}

int		init_question_arg(t_source *src, int ret)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_itoa(g_global.return_value);
	while (s[i] != '\0')
		src->re[src->re_b++] = s[i++];
	free(s);
	return (ret + 1);
}

int		init_question_cmd(t_source *src,int ret)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_itoa(g_global.return_value);
	while (s[i] != '\0')
		src->ra[src->ra_b++] = s[i++];
	free(s);
	return (ret + 1);
}
int		init_question_red(t_source *src,int ret)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_itoa(g_global.return_value);
	while (s[i] != '\0')
		src->ra[src->ra_b++] = s[i++];
	free(s);
	return (ret + 1);
}




int		get_env_value_arg(char *s, char **envp, t_source *src, int i)
{
	char	*temp;
	int		b;
	int 	length;
	int		c;

	i = i + 1;
	b = 0;
	c = 0;

	if (s[i] == '?')
		return(init_question_arg(src, i));
	temp = malloc(4096 * sizeof(char));
	while (s[i] != '$' && s[i] != '\n' && s[i] != '\0' && s[i] != ' ')
	{
		temp[b++] = s[i++];
		if (ft_isdollar(s[i]) != 1)
			break ;
	}
	temp[b] = '\0';
	b = 0;
	length = ft_strlen(temp);
	while (src->our_envp[c] != NULL)
	{
		// if (ft_strncmp(envp[c], temp, find_equal_length(envp, c, b)) == 0)
		if (ft_strncmp(src->our_envp[c], temp, length) == 0 && src->our_envp[c][length] == '=')
		{
			while (src->our_envp[c][b] != '=' && src->our_envp[c][b] != '\0')
				b++;
				while (src->our_envp[c][++b] != '\0')
					src->re[src->re_b++] = src->our_envp[c][b];
				break ;
		}
		c++;
	}
	free(temp);
	// if (src->re == '\0')
		// printf("ZEROOO %s\n",src->re);
	return (i);
}


int		get_env_value_red(char *s, int *z, t_source *src, int i)
{
	char	*temp;
	int		b;
	int 	length;
	int		c;

	i = i + 1;
	b = 0;
	c = 0;

	if (s[i] == '?')
		return(init_question_red(src, i));
	temp = malloc(4096 * sizeof(char));
	while (s[i] != '$' && s[i] != '\n' && s[i] != '\0' && s[i] != ' ')
	{
		temp[b++] = s[i++];
		if (ft_isdollar(s[i]) != 1)
			break ;
	}
	temp[b] = '\0';
	b = 0;
	length = ft_strlen(temp);
	while (src->our_envp[c] != NULL)
	{
		// if (ft_strncmp(envp[c], temp, find_equal_length(envp, c, b)) == 0)
		if (ft_strncmp(src->our_envp[c], temp, length) == 0 && src->our_envp[c][length] == '=')
		{
			while (src->our_envp[c][b] != '=' && src->our_envp[c][b] != '\0')
				b++;
				while (src->our_envp[c][++b] != '\0')
					src->p->filename[*z] = src->our_envp[c][b];
				break ;
		}
		c++;
	}
	free(temp);
	// if (src->re == '\0')
		// printf("ZEROOO %s\n",src->re);
	return (i);
}
