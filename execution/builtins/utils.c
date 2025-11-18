/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:20:43 by szmadeja          #+#    #+#             */
/*   Updated: 2025/11/18 19:28:02 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	valid_check(char *s)
{
	int	i;

	i = 0;
	if (!s || !(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	i++;
	while (s[i] && s[i] != '=')
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	print_expo_env(t_envp *env)
{
	t_envp	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_printf("declare -x %s", tmp->key);
		if (tmp->value)
			ft_printf("=\"%s\"", tmp->value);
		ft_printf("\n");
		tmp = tmp->next;
	}
	return (0);
}

void	env_update(t_envp **env, char *key, char *value)
{
	t_envp	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (tmp->value != NULL)
				free(tmp->value);
			if (value != NULL)
				tmp->value = ft_strdup(value);
			else
				tmp->value = NULL;
			return ;
		}
		tmp = tmp->next;
	}
	env_add(env, key, value);
}
