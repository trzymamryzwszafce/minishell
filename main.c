/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorbi <sorbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:16:29 by nadamczy          #+#    #+#             */
/*   Updated: 2025/12/05 21:51:42 by sorbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_parsing(t_token *tokens, t_envp **envp, char *input, t_data *data)
{
	int	error;

	error = 0;
	error = ft_split_input(tokens, input);
	if (error == 0)
		error = ft_type_input(tokens, envp, data);
	return (error);
}

void	ft_process_input(char *input, t_envp **envp, int *last_exit_code)
{
	t_token		*tokens;
	t_data		*data;
	int			error;

	add_history(input);
	tokens = ft_calloc(1, sizeof(t_token));
	data = ft_calloc(1, sizeof(t_data));
	data->token = tokens;
	data->ls_exit = *last_exit_code;
	data->cmd = NULL;
	error = ft_parsing(tokens, envp, input, data);
	if (error == 0)
	{
		ft_struct_filler(tokens, data);
		execution(data, envp);
		*last_exit_code = data->ls_exit;
		ft_free_command_list(data->cmd);
		data->cmd = NULL;
	}
	ft_free_tokens(tokens);
	data->token = NULL;
	free(data);
}

int	main(void)
{
	extern char	**environ;
	char		*input;
	t_envp		*envp;
	int			last_exit_code;

	idle_signals();
	using_history();
	last_exit_code = 0;
	envp = ft_create_envp(environ);
	while (1)
	{
		input = readline("\033[1;35mMINICWEL \033[0m");
		if (!input)
			break ;
		else if (*input)
			ft_process_input(input, &envp, &last_exit_code);
		free(input);
	}
	ft_free_env_list(&envp);
	rl_clear_history();
	return (0);
}
