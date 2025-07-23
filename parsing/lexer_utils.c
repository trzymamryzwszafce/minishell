#include "../minishell.h"

t_lexer	*ft_create_next_node(t_lexer *current)
{
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	ft_null_lexer(new_node);
	current->next = new_node;
	return (new_node);
}

int	ft_is_redirect(char *token)
{
	return (!ft_strcmp(token, ">") || !ft_strcmp(token, ">>")
		|| !ft_strcmp(token, "<") || !ft_strcmp(token, "<<"));
}

int	ft_is_pipe(char *token)
{
	return (!ft_strcmp(token, "|"));
}

void	ft_null_lexer(t_lexer *cmd_line)
{
	cmd_line->command = NULL;
	cmd_line->flag = NULL;
	cmd_line->params = NULL;
	cmd_line->type = NULL;
	cmd_line->redir_targets = NULL;
	cmd_line->next = NULL;
}
