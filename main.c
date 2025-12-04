/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:16:29 by nadamczy          #+#    #+#             */
/*   Updated: 2025/12/04 11:17:56 by szmadeja         ###   ########.fr       */
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
		execution(data, envp, tokens);
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

	idle_signals();
	using_history();
	envp = ft_create_envp(environ);
	while (1)
	{
		input = readline("\033[1;35mMINICWEL \033[0m");
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
