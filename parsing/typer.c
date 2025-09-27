#include "../minishell.h"

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