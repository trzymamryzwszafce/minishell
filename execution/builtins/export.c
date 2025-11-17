/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:15:19 by szmadeja          #+#    #+#             */
/*   Updated: 2025/11/17 02:34:32 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	env_add(t_envp **env, char *key, char *value)
{
	t_envp		*new;

	new = malloc(sizeof(t_envp));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = *env;
	*env = new;
}

void	split_value(char *arg, char **key, char **value)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	*key = ft_substr(arg, 0, i);
	if (arg[i] == '=')
		*value = ft_strdup(arg + i + 1);
	else
		*value = NULL;
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

int	process_arg(t_envp **env, char *arg)
{
	char	*key;
	char	*value;

	if (!valid_check(arg))
	{
		ft_printf("bash: export: `%s`: zly parametr\n", arg);
		return (1);
	}
	split_value(arg, &key, &value);
	env_update(env, key, value);
	free(key);
	if (value)
		free(value);
	return (0);
}

int	ft_export(t_envp **env, char **args)
{
	int		i;
	int		status;

	if (!args[1])
		return (print_expo_env(*env));
	i = 1;
	status = 0;
	while (args[i])
	{
		if (process_arg(env, args[i]))
			status = 1;
		i++;
	}
	return (status);
}
