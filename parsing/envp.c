/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadamczy <nadamczy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:15:49 by nadamczy          #+#    #+#             */
/*   Updated: 2025/11/29 12:21:20 by nadamczy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_envp_value(t_envp **envp, char *key)
{
	t_envp	*node;

	if (!envp || !key)
		return (NULL);
	node = *envp;
	while (node != NULL)
	{
		if (!ft_strcmp(node->key, key))
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

void	ft_new_envp_value(t_envp **envp, char *key, char *value)
{
	t_envp	*node;

	node = *envp;
	while (node != NULL)
	{
		if (!ft_strcmp(node->key, key))
		{
			free(node->value);
			node->value = ft_strdup(value);
			return ;
		}
		node = node->next;
	}
}

void	ft_add_to_envp(t_envp **envp, char *key, char *value)
{
	if (!key)
		return ;
	if (ft_get_envp_value(envp, key) == NULL)
		ft_add_envp_list(envp, key, value);
	else
		ft_new_envp_value(envp, key, value);
}

t_envp	*ft_create_envp(char **environ)
{
	int		i;
	t_envp	*envp;
	char	*key;
	char	*value;

	i = 0;
	envp = NULL;
	while (environ[i])
	{
		key = ft_assign_key(environ[i]);
		value = ft_assign_value(environ[i]);
		if (key && value)
		{
			ft_add_to_envp(&envp, key, value);
			free(key);
			free(value);
		}
		else
		{
			free(key);
			free(value);
		}
		i++;
	}
	return (envp);
}
