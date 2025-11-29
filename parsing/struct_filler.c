/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_filler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadamczy <nadamczy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:16:15 by nadamczy          #+#    #+#             */
/*   Updated: 2025/11/29 12:16:16 by nadamczy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_search_for_append(t_type type, t_command *cmd)
{
	if (type == R_OUT_APP)
		cmd->append = true;
	else
		cmd->append = false;
}

void	ft_heredoc(t_token *start, t_command *cmd)
{
	t_token	*cur;
	int		i;

	if (cmd->heredoc_count == 0)
		return ;
	cur = start;
	i = 0;
	cmd->heredoc = calloc(cmd->heredoc_count + 1, sizeof(char *));
	while (cur && cur->type != PIPE)
	{
		if (cur->type == R_HEREDOC && cur->next != NULL)
		{
			cmd->heredoc[i++] = strdup(cur->next->elem);
			cur->next->type = HEREDOC_DELI;
			cmd->b_heredoc = true;
		}
		if (cur->type == R_IN && cur->next != NULL)
			cmd->b_heredoc = false;
		cur = cur->next;
	}
}

static void	handle_heredoc_token(t_token **cur, t_command *cmd)
{
	cmd->heredoc_count++;
	if (*cur && (*cur)->next)
		*cur = (*cur)->next;
}

t_token	*fill_one_cmd(t_token *start, t_command *cmd)
{
	t_token	*cur;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	cur = start;
	while (cur->next != NULL && cur->type != PIPE)
	{
		if (cur->type == ARG)
			cmd->arg[i++] = strdup(cur->elem);
		else if (cur->type == ARG_IN)
			cmd->red_in[j++] = strdup(cur->elem);
		else if (cur->type == ARG_OUT)
			cmd->red_out[k++] = strdup(cur->elem);
		else if (cur->type == R_OUT_APP || cur->type == R_OUT_TRUNC)
			ft_search_for_append(cur->type, cmd);
		else if (cur->type == R_HEREDOC)
			handle_heredoc_token(&cur, cmd);
		cur = cur->next;
	}
	return (cur);
}

void	ft_struct_filler(t_token *tokens, t_data *data)
{
	t_token		*cur;
	t_token		*next;
	t_command	*cmd;

	cur = tokens;
	data->cmd = malloc(sizeof(t_command));
	init_cmd(data->cmd);
	cmd = data->cmd;
	while (cur->next != NULL)
	{
		count_and_alloc_for_cmd(cur, cmd);
		next = fill_one_cmd(cur, cmd);
		ft_heredoc(cur, cmd);
		if (!next)
			break ;
		if (next->type == PIPE)
			cur = next->next;
		else
			cur = next;
		if (cur->next == NULL)
			break ;
		cmd->next = malloc(sizeof(t_command));
		init_cmd(cmd->next);
		cmd = cmd->next;
	}
}
