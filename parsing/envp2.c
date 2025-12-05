/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorbi <sorbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:15:53 by nadamczy          #+#    #+#             */
/*   Updated: 2025/12/05 22:05:53 by sorbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_handle_exit_code(t_convert *sign, int *i, char *new_str)
{
	char	*tmp_dup;

	(*i)++;
	tmp_dup = ft_itoa(sign->exit_code);
	new_str = ft_join_and_free(new_str, tmp_dup);
	free(tmp_dup);
	return (new_str);
}

static char	*ft_copy_key(char *str, int len)
{
	char	*key;
	int		j;

	key = malloc(len + 1);
	if (!key)
		return (NULL);
	j = 0;
	while (j < len)
	{
		key[j] = str[j];
		j++;
	}
	key[j] = '\0';
	return (key);
}

char	*ft_assign_key(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (i == 0)
				return (NULL);
			return (ft_copy_key(str, i));
		}
		i++;
	}
	return (NULL);
}

char	*ft_assign_value(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*value;

	i = -1;
	j = 0;
	k = 0;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			j = i;
			while (str[j])
				j++;
			if (j - i < 2)
				return (NULL);
			value = malloc(j - 1 + 1);
			while (str[++i])
				value[k++] = str[i];
			value[k] = '\0';
			return (value);
		}
	}
	return (NULL);
}

void	ft_add_envp_list(t_envp **envp, char *key, char *value)
{
	t_envp	*new;
	t_envp	*node;

	new = malloc(sizeof(t_envp));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (*envp == NULL)
	{
		*envp = new;
		return ;
	}
	node = *envp;
	while (node->next != NULL)
		node = node->next;
	node->next = new;
}
