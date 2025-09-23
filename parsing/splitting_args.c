#include "../minishell.h"

int	ft_count_input_words(char const *s)
{
	int	count;
	int	i;

	i = 0;
	if (!s)
		return (0);
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '>' || s[i] == '<' || s[i] == '|')
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != ' ' && s[i] != '\t' && s[i] != '>' && s[i] != '<' && s[i] != '|' && s[i] != '\0')
			i++;
	}
	return (count);
}

t_token	*ft_create_node(t_token *cur)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	if (!new_node)
		return (NULL);
	if (cur)
	{
		cur->next = new_node;
		new_node->prev = cur;
	}
	return (new_node);
}

t_token *ft_add_node(t_token *token, char *s, int *i, int n) //tu trzeba uaktualnić i, n - num of chars to add
{
	int	j;
	char	*string;

	if (n <= 0 || !token)
		return (token);
	string = ft_calloc(1, n + 1);
	j = 0;
	while (j < n && s[*i])
	{
		string[j] = s[*i];
		(*i)++;
		j++;
	}
	string[j] = '\0';
	token->elem = string;
	token->next = ft_create_node(token);
	return (token->next);
}

//n - num where to start
int ft_count_chars(char *s, int n)
{
	int	count;
	char q;

	count = 0;
	while (s[n] && s[n] != ' ' && s[n] != '\t' && s[n] != '<' && s[n] != '>' && s[n] != '|')
	{
		if (s[n] == 39 || s[n] == 34)
		{
			q = s[n++];
			count++;
			while (s[n] && s[n] != q)
			{
				n++;
				count++;
			}
			if (s[n] == q)
			{
				n++;
				count++;
			}
		}
		else
		{
			n++;
			count++;
		}
	}
	return (count);
}

t_token	*ft_quote(t_token *token, char *input, char deli, int *i)
{
	int count;
	count = 0;
	count = ft_count_until_deli(input, *i, deli, count);
	return (ft_add_node(token, input, i, count));
}

t_token	*ft_is_limiter(t_token *token, char *input, int *i)
{
	int n;
	
	if (!input[*i])
		return (token);
	if (input[*i] == 39 || input[*i] == 34)
		return (ft_quote(token, input, input[*i], i));
	if (((input[*i] == '>' && input[*i + 1] == '>' && input[*i + 1]) || (input[*i] == '<' && input[*i + 1] == '<' && input[*i + 1])) && input[*i])
		return (ft_add_node(token, input, i,  2));
	if ((input[*i] == '<' || input[*i] == '>' || input[*i] == '|') && input[*i])
		return (ft_add_node(token, input, i, 1));
	if ((input[*i] == ' ' || input[*i] == '\t') && input[*i])
	{
		while (input[*i] == ' ' || input[*i] == '\t')
			(*i)++;
        return (token);
	}
	if (!input[*i])
		return (token); //nie wiem czy to jest potrzebne 
	n = ft_count_chars(input, *i);
	if (n > 0)
		return (ft_add_node(token, input, i, n));
	(*i)++; //jeżeli n == 0 trzeba przesunąć o 1, żeby nie zaciąć pętli
	return (token);
}

void ft_split_input(t_token *tokens, char *input)
{
	int	i;
	t_token	*cur;

	cur = tokens;
	i = 0;
	while (input[i])
		cur = ft_is_limiter(cur, input, &i);
}

