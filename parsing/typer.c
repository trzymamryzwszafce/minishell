#include "../minishell.h"
#include <string.h>


void ft_is_redir_pipe(t_token *token)
{
	if (ft_strcmp(token->elem, "<") == 0)
		token->type = R_IN;
	else if (ft_strcmp(token->elem, ">") == 0)
		token->type = R_OUT_TRUNC;
	else if (ft_strcmp(token->elem, ">>") == 0)
		token->type = R_OUT_APP;
	else if (ft_strcmp(token->elem, "<<") == 0)
		token->type = R_HEREDOC;
	else if (ft_strcmp(token->elem, "|") == 0)
		token->type = PIPE;
	else
		token->type = ARG;
}

void ft_add_type(t_token *token)
{
	ft_is_redir_pipe(token);
}

// void ft_error_message(int exit_code, char token)
// {
// 	if (exit_code == 258)
// 	{
// 		perror("minishell: syntax error near unexpected token ' ")
// 		if (token == '|')

// 	}
// }

int ft_quote_error(char *s)
{
	int	len;
	char deli;

	len = ft_strlen(s);
	if(s[0] == 39)
		deli = 39;
	else if (s[0] == 34)
		deli = 34;
	else 
		return (0);
	if (s[len - 1] != deli)
		return (258);
	return (0);
}

int ft_errors(t_token *token) //będzie zwracał kod błędu
{
	t_token *cur;
	int error;

	error = 0;
	cur = token;
	while (cur->next != NULL)
	{
		if (cur->type == ARG)
			error = ft_quote_error(cur->elem);
	//else if (cur->type == PIPE && error == 0)
		cur = cur->next;
	}
	return (error);
}

int ft_type_input(t_token *token)
{
	t_token *cur;

	cur = token;
	while (cur->next != NULL)
	{
		ft_add_type(cur);
		cur = cur->next;
	}
	return (ft_errors(token));
}
