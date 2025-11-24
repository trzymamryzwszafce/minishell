/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:11:18 by szmadeja          #+#    #+#             */
/*   Updated: 2025/11/24 05:38:09 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_env(t_envp *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*get_target(t_envp *env, char *arg)
{
	char	*home;
	char	*oldpwd;

	if (!arg || !ft_strcmp(arg, "~"))
	{
		home = get_env(env, "HOME");
		if (!home)
		{
			ft_printf("bash: cd: dom nie ustawiony\n");
			return (NULL);
		}
		return (home);
	}
	if (!ft_strcmp(arg, "-"))
	{
		oldpwd = get_env(env, "OLDPWD");
		if (!oldpwd)
		{
			ft_printf("bash: cd: oldpwd nie ustawione\n");
			return (NULL);
		}
		return (oldpwd);
	}
	return (arg);
}

int	change_directory(t_envp **env, char *target)
{
	char	oldpwd[PATH_MAX];
	char	newpwd[PATH_MAX];

	if (chdir(target) == -1)
		return (ft_printf("bash: cd: \"%s\" nie istnieje\n", target), 1);
	env_update(env, "OLDPWD", oldpwd);
	if (!getcwd(newpwd, sizeof(newpwd)))
		return (ft_printf("bash: cd: błąd przy nowym katalogu\n"), 1);
	env_update(env, "PWD", newpwd);
	return (0);
}

int	ft_cd(t_envp **env, char **args)
{
	char	*target;

	if (args[1] && args[2])
		return (ft_printf("bash: cd: za duzo argumentow\n"), 1);
	target = get_target(*env, args[1]);
	if (!target)
		return (1);
	return (change_directory(env, target));
}
