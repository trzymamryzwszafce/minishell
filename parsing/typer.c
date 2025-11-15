#include "../minishell.h"

void ft_add_type(t_token *token)
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

void ft_add_type_arg(t_token *token)
{
	if (token->prev && token->prev->type == R_IN && token->type == ARG)
		token->type = ARG_IN;
	else if (token->prev && token->prev->type == R_OUT_TRUNC && token->type == ARG)
		token->type = ARG_OUT;
}