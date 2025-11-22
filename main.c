#include "minishell.h"

void	init_cmd(t_command *cmd)
{
	cmd->arg = NULL;
	cmd->red_in = NULL;
	cmd->red_out = NULL;
	cmd->append = false;
	cmd->heredoc = NULL;
	cmd->b_heredoc = false;
	cmd->heredoc_count = 0;
	cmd->next = NULL;
}

void	ft_free_str_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_free_command_list(t_command *cmd)
{
	t_command	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		ft_free_str_array(cmd->arg);
		ft_free_str_array(cmd->red_in);
		ft_free_str_array(cmd->red_out);
		ft_free_str_array(cmd->heredoc);
		free(cmd);
		cmd = tmp;
	}
}

void	ft_free_env_list(t_envp **envp)
{
	t_envp	*tmp;

	while (*envp)
	{
		tmp = (*envp)->next;
		free((*envp)->key);
		free((*envp)->value);
		free(*envp);
		*envp = tmp;
	}
}

/* free whole token linked list (elem + node) */
void	ft_free_tokens(t_token *tokens)
{
	t_token	*cur;
	t_token	*tmp;

	cur = tokens;
	while (cur)
	{
		tmp = cur->next;
		if (cur->elem)
			free(cur->elem);
		free(cur);
		cur = tmp;
	}
}

int	ft_parsing(t_token *tokens, t_envp **envp, char *input,  int error, t_data *data)
{
	error = ft_split_input(tokens, input);
	if (error == 0)
		error = ft_type_input(tokens, envp, data);
	return (error);
}
void	ft_process_input(char *input, t_envp **envp)
{
	t_token		*tokens;
	t_data		*data;
	t_command	*cmd;
	int			error;

	add_history(input);
	tokens = ft_calloc(1, sizeof(t_token));
	data = ft_calloc(1, sizeof(t_data));
	data->cmd = NULL;
	error = ft_parsing(tokens, envp, input, 0, data);
	if (error == 0)
	{
		ft_struct_filler(tokens, data);
		//print_command_list(data->cmd);
		//egzekuzja
		//execution(data, cmd, envp);
		ft_free_command_list(data->cmd);
		data->cmd = NULL;
	}
	ft_free_tokens(tokens);
	free(data);
}

int	main(void)
{
	extern char	**environ;
	char		*input;
	t_envp		*envp;

	using_history();
	envp = ft_create_envp(environ);
	while (1)
	{
		input = readline(">>> ");
		if (!input)
			break ;
		else if (*input)
			ft_process_input(input, &envp);
		free(input);
	}
	ft_free_env_list(&envp);
	rl_clear_history();
	return (0);
}
