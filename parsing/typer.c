/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorbi <sorbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:16:19 by nadamczy          #+#    #+#             */
/*   Updated: 2025/12/05 22:13:27 by sorbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	count_and_alloc_for_cmd(t_token *start, t_command *cmd)
{
	t_token	*cur;
	int		args;
	int		rin;
	int		rout;

	cur = start;
	args = 0;
	rin = 0;
	rout = 0;
	while (cur->next != NULL && cur->type != PIPE)
	{
		if (cur->type == ARG)
			args++;
		else if (cur->type == ARG_IN)
			rin++;
		else if (cur->type == ARG_OUT)
			rout++;
		cur = cur->next;
	}
	cmd->arg = ft_calloc(args + 1, sizeof(char *));
	cmd->red_in = ft_calloc(rin + 1, sizeof(char *));
	cmd->red_out = ft_calloc(rout + 1, sizeof(char *));
	cmd->heredoc_count = 0;
}

void	ft_add_type(t_token *token)
{
	if (ft_strcmp(token->elem, "<") == 0)
		token->type = R_IN;
	else if (ft_strcmp(token->elem, ">") == 0)
		token->type = R_OUT_TRUNC;
	else if (ft_strcmp(token->elem, ">>") == 0)
		token->type = R_OUT_APP;
	else if (ft_strcmp(token->elem, "<<") == 0)
		token->type = R_HEREDOC;
	else if (ft_strcmp(token->elem, "|") == 0)
		token->type = PIPE;
	else
		token->type = ARG;
}

void	ft_add_type_arg(t_token *token)
{
	if (token->prev && token->prev->type == R_IN && token->type == ARG)
		token->type = ARG_IN;
	else if ((token->prev && token->prev->type == R_OUT_TRUNC
			&& token->type == ARG)
		|| (token->prev && token->prev->type == R_OUT_APP
			&& token->type == ARG))
		token->type = ARG_OUT;
}
