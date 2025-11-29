/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadamczy <nadamczy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:16:24 by nadamczy          #+#    #+#             */
/*   Updated: 2025/11/29 12:16:25 by nadamczy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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