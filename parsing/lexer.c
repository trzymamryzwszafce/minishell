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

void	ft_lexer(t_mini *mini)
{
	t_lexer *cmd_line;
	t_lexer *new_node;
	int arg_count;
	int i = 0;

	cmd_line = malloc(sizeof(t_lexer));
	if (!cmd_line)
		return;
	ft_null_lexer(cmd_line); //cały lexer na NULL
	mini->lexer = cmd_line;

	while (mini->arg_list[i])//przechodzimy przez wszystkie argumenty z inputu
	{
		if (ft_is_redirect(mini->arg_list[i]) || ft_is_pipe(mini->arg_list[i])) //jeżeli redirect lub pipe są w złym miejscu - miejscu cmd
		{
			printf("syntax error near unexpected token `%s`\n", mini->arg_list[i]);
		}
		else if (ft_is_cmd(mini->arg_list[i]))
			cmd_line->command = ft_strdup(mini->arg_list[i++]);
		else
		{
			printf("%s: command not found\n", mini->arg_list[i]);
		}
		if (mini->arg_list[i] && mini->arg_list[i][0] == '-') //jeżeli istnieje flaga to zbieramy
			cmd_line->flag = ft_strdup(mini->arg_list[i++]);
		arg_count = ft_count_args(&mini->arg_list[i]); //dodaje argumenty
		if (arg_count > 0)
		{
			cmd_line->params = ft_copy_args(mini->arg_list, i, arg_count);
			i += arg_count;
		}
		while (mini->arg_list[i] && ft_is_redirect(mini->arg_list[i])) //redirection
		{
			char *redir_type = mini->arg_list[i++];
			if (!mini->arg_list[i]) //jak nie ma nic po znaku redirect to error
			{
				printf("syntax error: expected file after redirection\n");
			}
			cmd_line->type = add_to_str_array(cmd_line->type, redir_type); //do listy type dodaje znak redirect
			cmd_line->redir_targets = add_to_str_array(cmd_line->redir_targets, mini->arg_list[i++]); //to będzie się odnosiło do jakich plików jest to redirect
		}
		if (mini->arg_list[i] && ft_is_pipe(mini->arg_list[i])) //obsługa pipe
		{
			i++; // skip '|'
			new_node = malloc(sizeof(t_lexer));
			if (!new_node)
				return;
			ft_null_lexer(new_node);
			cmd_line->next = new_node;
			cmd_line = new_node;
			continue;
		}
		if (mini->arg_list[i]) //jak są kolejne argumenty to nowa linked lista
		{
			new_node = malloc(sizeof(t_lexer));
			if (!new_node)
				return;
			ft_null_lexer(new_node);
			cmd_line->next = new_node;
			cmd_line = new_node;
		}
		else
		cmd_line->next = NULL;
	}
}
