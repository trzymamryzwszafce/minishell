#include "../minishell.h"

int	ft_is_cmd(char *cmd)
{
	if (ft_strcmp(cmd, "cmd") == 0)
		return (1); // tylko do testów, obsługuje tylko  cmp
	else
		return (0);
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
