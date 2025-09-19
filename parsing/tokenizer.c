#include "../minishell.h"


void ft_is_redir_pipe(t_token *token)
{
	if (ft_strcmp(token->elem, "<"))
		token->type = R_IN;
	else if (ft_strcmp(token->elem, ">"))
		token->type = R_OUT_TRUNC;
	else if (ft_strcmp(token->elem, ">>"))
		token->type = R_OUT_APP;
	else if (ft_strcmp(token->elem, "<<"))
		token->type = R_HEREDOC;
	else if (ft_strcmp(token->elem, "|"))
		token->type = PIPE;
}

void ft_add_type(t_token *token)
{
	ft_is_redir_pipe(token);
}

void ft_tokenizer_input(t_token *token)
{
	t_token *cur;

	cur = token;
	while (cur->next != NULL)
	{
		ft_add_type(cur);
		cur = cur->next;
	}
}
