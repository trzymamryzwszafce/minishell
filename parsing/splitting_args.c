#include "../minishell.h"

int	ft_count_chars(char *s, int n)
{
	int	count;

	count = 0;
	while (s[n] && s[n] != ' ' && s[n] != '\t' && s[n] != '<'
		&& s[n] != '>' && s[n] != '|')
	{
		if (s[n] == '\'' || s[n] == '\"')
			count += ft_skip_quotes(s, &n);
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
	int	count;

	count = 0;
	count = ft_count_until_deli(input, *i, deli, count);
	return (ft_add_node(token, input, i, count));
}

t_token	*ft_is_limiter(t_token *token, char *input, int *i)
{
	int	n;

	if (!input[*i])
		return (token);
	if (input[*i] == 39 || input[*i] == 34)
		return (ft_quote(token, input, input[*i], i));
	if (((input[*i] == '>' && input[*i + 1] == '>' && input[*i + 1])
			|| (input[*i] == '<' && input[*i + 1] == '<'
				&& input[*i + 1])) && input[*i])
		return (ft_add_node(token, input, i, 2));
	if ((input[*i] == '<' || input[*i] == '>' || input[*i] == '|') && input[*i])
		return (ft_add_node(token, input, i, 1));
	if ((input[*i] == ' ' || input[*i] == '\t') && input[*i])
	{
		while (input[*i] == ' ' || input[*i] == '\t')
			(*i)++;
		return (token);
	}
	if (!input[*i])
		return (token);
	n = ft_count_chars(input, *i);
	if (n > 0)
		return (ft_add_node(token, input, i, n));
	(*i)++;
	return (token);
}

int	ft_check_syntax_errors(char *input, int input_len)
{
	if (ft_strnstr(input, ">><>", input_len) != NULL
		|| ft_strnstr(input, ">> <>", input_len) != NULL
		|| ft_strnstr(input, "<< <>", input_len) != NULL
		|| ft_strnstr(input, "><>", input_len) != NULL
		|| ft_strnstr(input, "> <>", input_len) != NULL
		|| ft_strnstr(input, "< <>", input_len) != NULL)
	{
		write(2, "minishell: syntax error near unexpected token `<>'\n", 51);
		return (258);
	}
	if (ft_strnstr(input, "<>>", input_len) != NULL)
	{
		write(2, "minishell: syntax error near unexpected token `>'\n", 50);
		return (258);
	}
	if (ft_strnstr(input, "<>", input_len) != NULL)
	{
		write(2,
			"minishell: syntax error near unexpected token `newline'\n", 56);
		return (258);
	}
	return (0);
}

int	ft_split_input(t_token *tokens, char *input)
{
	int		i;
	t_token	*cur;
	int		input_len;
	char	*found;
	int		error;

	i = 0;
	input_len = ft_strlen(input);
	error = ft_check_syntax_errors(input, input_len);
	if (error != 0)
		return (error);
	cur = tokens;
	while (input[i])
		cur = ft_is_limiter(cur, input, &i);
	return (0);
}
