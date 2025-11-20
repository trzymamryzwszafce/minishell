#include "../minishell.h"

void	ft_error_message(int exit_code, char *message)
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

void	ft_check_quotes(t_token *cur, int *error, char **message)
{
	if (cur->type != ARG)
		return ;
	*error = ft_quote_error(cur->elem);
	if (*error)
		*message = "unclosed quotes";
}

int	ft_check_pipe(t_token *cur, int i, int *error, char **message)
{
	if (cur->type != PIPE || *error != 0)
		return (0);
	*error = ft_pipe_error(i, cur->elem, cur->next->elem, cur->next->type);
	if (*error)
	{
		*message = "|";
		return (1);
	}
	return (0);
}

int	ft_check_redir(t_token *cur, int *error, char **message)
{
	if ((cur->type != R_IN && cur->type != R_OUT_APP && cur->type != R_OUT_TRUNC
			&& cur->type != R_HEREDOC) || *error != 0)
		return (0);
	if (cur->next->elem == NULL)
	{
		*error = 258;
		*message = "newline";
		return (1);
	}
	*error = ft_redir_error(cur->type, cur->next->type);
	if (*error)
	{
		*message = cur->next->elem;
		return (1);
	}
	return (0);
}

int	ft_errors(t_token *token)
{
	t_token	*cur;
	int		error;
	int		i;
	char	*message;

	error = 0;
	i = 0;
	cur = token;
	message = NULL;
	while (cur->next != NULL)
	{
		ft_check_quotes(cur, &error, &message);
		if (ft_check_pipe(cur, i, &error, &message))
			break ;
		if (ft_check_redir(cur, &error, &message))
			break ;
		i++;
		cur = cur->next;
	}
	ft_error_message(error, message);
	return (error);
}
