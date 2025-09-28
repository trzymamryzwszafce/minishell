#include "../minishell.h"

// void ft_error_message(int exit_code, char token)
// {
// 	if (exit_code == 258)
// 	{
// 		perror("minishell: syntax error near unexpected token ' ")
// 		if (token == '|')

// 	}
// }

// int ft_quote_error(char *s)
// {
// 	int	len;
// 	char deli;
// 	int i;

// 	i = 0;
// 	len = ft_strlen(s);
// 	while (i < len)
// 	{
// 		if (s[i] == 34 || s[i] == 39)
// 		{
// 			//dupa
// 		}
// 	}
// 		return (258);
// 	return (0);
// }

// int ft_errors(t_token *token) //będzie zwracał kod błędu
// {
// 	t_token *cur;
// 	int error;

// 	error = 0;
// 	cur = token;
// 	while (cur->next != NULL)
// 	{
// 		if (cur->type == ARG)
// 			error = ft_quote_error(cur->elem);
// 	//else if (cur->type == PIPE && error == 0)
// 		cur = cur->next;
// 	}
// 	return (error);
// }

// int ft_type_input(t_token *token)
// {
// 	t_token *cur;

// 	cur = token;
// 	while (cur->next != NULL)
// 	{
// 		ft_add_type(cur);
// 		cur = cur->next;
// 	}
// 	return (ft_errors(token));
// }
