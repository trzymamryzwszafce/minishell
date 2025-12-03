/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:15:40 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/03 01:56:09 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_env_node(t_envp *node)
{
	free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

void	env_remove(t_envp **env, char *key)
{
	t_envp	*tmp;
	t_envp	*prev;

	if (!env || !*env)
		return ;
	tmp = *env;
	if (!ft_strcmp(tmp->key, key))
	{
		*env = tmp->next;
		free_env_node(tmp);
		return ;
	}
	prev = tmp;
	tmp = tmp->next;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			prev->next = tmp->next;
			free_env_node(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(t_envp **env, char **args)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (args[i])
	{
		if (!valid_check(args[i]))
		{
			ft_putstr_fd("bash: unset: '", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			status = 1;
		}
		else
			env_remove(env, args[i]);
		i++;
	}
	return (status);
}
