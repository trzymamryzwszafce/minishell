/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:11:18 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/03 02:31:13 by szmadeja         ###   ########.fr       */
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
			ft_putendl_fd("bash: cd: HOME not set", 2);
			return (NULL);
		}
		return (home);
	}
	if (!ft_strcmp(arg, "-"))
	{
		oldpwd = get_env(env, "OLDPWD");
		if (!oldpwd)
		{
			ft_putendl_fd("bash: cd: OLDPWD not set", 2);
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

	getcwd(oldpwd, sizeof(oldpwd));
	if (chdir(target) == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(target, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	env_update(env, "OLDPWD", oldpwd);
	if (!getcwd(newpwd, sizeof(newpwd)))
	{
		ft_putendl_fd("bash: cd: Error with new directory", 2);
		return (1);
	}
	env_update(env, "PWD", newpwd);
	return (0);
}

int	ft_cd(t_envp **env, char **args)
{
	char	*target;

	if (args[1] && args[2])
	{
		ft_putendl_fd("bash: cd: too many arguments", 2);
		return (1);
	}
	target = get_target(*env, args[1]);
	if (!target)
		return (1);
	return (change_directory(env, target));
}
