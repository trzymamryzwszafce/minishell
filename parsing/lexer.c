#include "../minishell.h"

void ft_process_flag(t_lexer *cmd_line, char **args, int *i)
{
	char *clean_flag;
	char *tmp;

	while (args[*i] && args[*i][0] == '-')
	{
		clean_flag = ft_strdup(args[*i] + 1);
		tmp = ft_strjoin(cmd_line->flag, clean_flag);
		free(cmd_line->flag);
		cmd_line->flag = tmp;
		free(clean_flag);
		(*i)++;
	}
}

int	ft_process_command(t_lexer *cmd_line, char **args, int *i)
{
	if (ft_is_pipe(args[*i]))
	{
		printf("syntax error near unexpected token `%s`\n", args[*i]);
		return (0);
	}
	else if (cmd_line->command)
	{
		printf("%s: cannot access '%s': No such file or directory", cmd_line->command, args[*i]);
		return (0);
	}
	else if (ft_is_redirect(args[*i]))
		return (1);
	else
		cmd_line->command = ft_strdup(args[(*i)++]);
	return (1);
}

void ft_process_arguments(t_lexer *cmd_line, char **args, int *i)
{
	int arg_count;
	int j;

	j = 0;
	arg_count = ft_count_only_args(args, i);
	if (!args[*i] || ft_is_redirect(args[*i]) || ft_is_pipe(args[*i]))
		return;
	cmd_line->params = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd_line->params)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (args[*i] && !ft_is_redirect(args[*i]) && !ft_is_pipe(args[*i]))
	{
		if (args[*i][0] == '-')
			ft_process_flag(cmd_line, args, i);
		else
			cmd_line->params[j++] = strdup(args[(*i)++]);
	}
	cmd_line->params[j] = NULL;
}

int	ft_process_redirects(t_lexer *cmd_line, char **args, int *i)
{
	char	*redir_type;
	char	*target;

	while (args[*i] && ft_is_redirect(args[*i]))
	{
		if (!args[*i + 1])
		{
			printf("syntax error: expected file after redirection\n");
			return (0);
		}
		redir_type = args[*i];
		target = args[*i + 1];
		cmd_line->type = add_to_str_array(cmd_line->type, redir_type);
		cmd_line->redir_targets = add_to_str_array(cmd_line->redir_targets, target);
		*i += 2;
	}
	return (1);
}

void	ft_lexer(t_mini *mini)
{
	int		i;
	t_lexer *cur;

	mini->lexer = malloc(sizeof(t_lexer));
	i = 0;
	if (!mini->lexer)
		return ;
	ft_null_lexer(mini->lexer);
	cur = mini->lexer;
	while (mini->arg_list[i])
	{
		if (ft_process_command(cur, mini->arg_list, &i) == 0)
			return ;
		ft_process_arguments(cur, mini->arg_list, &i);
		if (ft_process_redirects(cur, mini->arg_list, &i) == 0)
			return ;
		if (mini->arg_list[i] && ft_is_pipe(mini->arg_list[i]))
		{
			i++;
			if (mini->arg_list[i])
			{
				cur = ft_create_next_node(cur);
				if (!cur)
					return ;
			}
			else
				cur->next = (NULL);
		}
	}
}
