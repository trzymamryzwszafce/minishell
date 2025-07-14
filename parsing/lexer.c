#include "../minishell.h"

void	ft_process_command(t_lexer *cmd_line, char **args, int *i)
{
	if (ft_is_redirect(args[*i]) || ft_is_pipe(args[*i]))
		printf("syntax error near unexpected token `%s`\n", args[*i]);
	else if (ft_is_cmd(args[*i]))
		cmd_line->command = ft_strdup(args[(*i)++]);
	else
		ft_printf("%s: command not found\n", args[*i]);
	if (args[*i] && args[*i][0] == '-')
		cmd_line->flag = ft_strdup(args[(*i)++]);
}

void	ft_process_arguments(t_lexer *cmd_line, char **args, int *i)
{
	int	arg_count;

	arg_count = ft_count_args(&args[*i]);
	if (arg_count > 0)
	{
		cmd_line->params = ft_copy_args(args, *i, arg_count);
		*i += arg_count;
	}
}

void	ft_process_redirects(t_lexer *cmd_line, char **args, int *i)
{
	char	*redir_type;

	while (args[*i] && ft_is_redirect(args[*i]))
	{
		redir_type = args[(*i)++];
		if (!args[*i])
			printf("syntax error: expected file after redirection\n");
		cmd_line->type = add_to_str_array(cmd_line->type, redir_type);
		cmd_line->redir_targets = add_to_str_array(cmd_line->redir_targets,
				args[(*i)++]);
	}
}

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

void	ft_lexer(t_mini *mini)
{
	int		i;
	t_lexer	*cmd_line;

	cmd_line = malloc(sizeof(t_lexer));
	i = 0;
	if (!cmd_line)
		return ;
	ft_null_lexer(cmd_line);
	mini->lexer = cmd_line;
	while (mini->arg_list[i])
	{
		ft_process_command(cmd_line, mini->arg_list, &i);
		ft_process_arguments(cmd_line, mini->arg_list, &i);
		ft_process_redirects(cmd_line, mini->arg_list, &i);
		if (mini->arg_list[i] && ft_is_pipe(mini->arg_list[i]))
			i++;
		if (mini->arg_list[i])
		{
			cmd_line = ft_create_next_node(cmd_line);
			if (!cmd_line)
				return ;
		}
		else
			cmd_line->next = (NULL);
	}
}

/*void	ft_lexer(t_mini *mini)
{
	t_lexer *cmd_line = malloc(sizeof(t_lexer)), *new_node;
	int i = 0, arg_count;

	if (!cmd_line) return;
	ft_null_lexer(cmd_line);
	mini->lexer = cmd_line;
	while (mini->arg_list[i])
	{
		if (ft_is_redirect(mini->arg_list[i]) || ft_is_pipe(mini->arg_list[i]))
			printf("syntax error near unexpected token `%s`\n", mini->arg_list[i]);
		else if (ft_is_cmd(mini->arg_list[i]))
			cmd_line->command = ft_strdup(mini->arg_list[i++]);
		else
			printf("%s: command not found\n", mini->arg_list[i]);
		if (mini->arg_list[i] && mini->arg_list[i][0] == '-')
			cmd_line->flag = ft_strdup(mini->arg_list[i++]);
		if ((arg_count = ft_count_args(&mini->arg_list[i])) > 0)
			cmd_line->params = ft_copy_args(mini->arg_list, i, i += arg_count, arg_count);
		while (mini->arg_list[i] && ft_is_redirect(mini->arg_list[i]))
		{
			char *redir_type = mini->arg_list[i++];
			if (!mini->arg_list[i]) printf("syntax error: expected file after redirection\n");
			cmd_line->type = add_to_str_array(cmd_line->type, redir_type);
			cmd_line->redir_targets = add_to_str_array(cmd_line->redir_targets, mini->arg_list[i++]);
		}
		if (mini->arg_list[i] && ft_is_pipe(mini->arg_list[i]))
			i++;
		if (mini->arg_list[i])
		{
			new_node = malloc(sizeof(t_lexer));
			if (!new_node) return;
			ft_null_lexer(new_node);
			cmd_line->next = new_node;
			cmd_line = new_node;
		}
		else 
			cmd_line->next = NULL;
	}
}*/

/*void	ft_lexer(t_mini *mini)
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
}*/
