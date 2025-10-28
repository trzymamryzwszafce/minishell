#include "../minishell.h"

void    ft_error_message(int exit_code, char *message)
{
	if (exit_code == 258)
	{
		if (ft_strcmp(message, "unclosed quotes") == 0)
		{
			write(2, "minishell: syntax error: unclosed quotes\n", 41);
			return ;
		}
		write(2, "minishell: syntax error near unexpected token `", 47);
		if (ft_strcmp(message, ">>") == 0 || ft_strcmp(message, "<<") == 0)
			write(2, message, 2);
		else if (ft_strcmp(message, "|") == 0 || ft_strcmp(message, ">") == 0
        || ft_strcmp(message, "<") == 0)
			write(2, message, 1);
		else if (ft_strcmp(message, "newline") == 0)
			write(2, message, 7);
		write(2, "'\n", 2);
	}
	return ;
}

int ft_quote_error(char *s)
{
	int	len;
	char deli;
	int i;

	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (s[i] == 34 || s[i] == 39)
		{
			deli = s[i];
			i++;
			while (s[i] != deli && s[i])
			{
				i++;
			}
			if (!s[i])
				return (258);
		}
		i++;
	}
	return (0);
}

int ft_pipe_error(int position, char *current, char *next, enum s_type next_type)
{
	if (position == 0 && ft_strcmp(current, "|") == 0)
		return (258);
	if (!next && ft_strcmp(current, "|") == 0)
		return (258);
	if (current && ft_strcmp(current, "|") == 0 && ft_strcmp(next, "|") == 0)
		return (258);
	if (current && ft_strcmp(current, "|") == 0 && (next_type == R_IN || next_type == R_OUT_APP || next_type == R_OUT_TRUNC || next_type == R_HEREDOC))
		return (258);
	return (0);
}

int ft_redir_error(enum s_type cur_type, enum s_type next_type)
{
	if ((cur_type == R_IN || cur_type == R_OUT_APP || cur_type == R_OUT_TRUNC || cur_type == R_HEREDOC) && 
		(next_type == R_IN || next_type == R_OUT_APP || next_type == R_OUT_TRUNC || next_type == R_HEREDOC || next_type == PIPE))
		return (258);
	return (0);
}

int ft_errors(t_token *token) //będzie zwracał kod błędu
{
	t_token *cur;
	int error;
	int i;
	char *message;

	error = 0;
	i = 0;
	cur = token;
	message = NULL;
	while (cur->next != NULL)
	{
		if (cur->type == ARG)
		{
			error = ft_quote_error(cur->elem);
			if (error)
				message = "unclosed quotes";
		}
		else if (cur->type == PIPE && error == 0)
		{
			error = ft_pipe_error(i, cur->elem, cur->next->elem, cur->next->type);
			if (error)
			{
				message = "|";
				break;
			}
		}
		else if ((cur->type == R_IN || cur->type == R_OUT_APP || cur->type == R_OUT_TRUNC || cur->type == R_HEREDOC) && error == 0)
		{
			if (cur->next->elem == NULL) //ostatni redir tutaj jest handlowany
			{
				error = 258;
				message = "newline";
				break;
			}
			error = ft_redir_error(cur->type, cur->next->type);
			if (error)
			{
				message = cur->next->elem;
				break;
			}
		}
		i++;
		cur = cur->next;
	}
	ft_error_message(error, message);
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

