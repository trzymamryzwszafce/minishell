#include "../minishell.h"

int	ft_process_command(t_lexer *cmd_line, char **args, int *i)
{
	if (ft_is_redirect(args[*i]) || ft_is_pipe(args[*i]))
	{
		printf("syntax error near unexpected token `%s`\n", args[*i]);
		return (0);
	}
	else
		cmd_line->command = ft_strdup(args[(*i)++]);
	if (args[*i] && args[*i][0] == '-')
		cmd_line->flag = ft_strdup(args[(*i)++]);
	return (1);
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

int	ft_process_redirects(t_lexer *cmd_line, char **args, int *i)
{
	char	*redir_type;

	while (args[*i] && ft_is_redirect(args[*i]))
	{
		redir_type = args[(*i)++];
		if (!args[*i])
		{
			printf("syntax error: expected file after redirection\n");
			return (0);
		}
		cmd_line->type = add_to_str_array(cmd_line->type, redir_type);
		cmd_line->redir_targets = add_to_str_array(cmd_line->redir_targets,
				args[(*i)++]);
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
		return ; //tez czyszczenie? - jednak w żadnym z tych returnów nie muszę czyscic pamięci - wszystko bedzie się na koniec czyścic tak czy inaczej
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
