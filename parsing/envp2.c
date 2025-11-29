/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadamczy <nadamczy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:15:53 by nadamczy          #+#    #+#             */
/*   Updated: 2025/11/29 12:15:54 by nadamczy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_assign_key(char *str)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	j = 0;
	key = NULL;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (i == 0)
				return (NULL);
			key = malloc(i + 1);
			j = 0;
			while (j < i)
				key[j++] = str[j];
			key[j] = '\0';
			return (key);
		}
		i++;
	}
	return (key);
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
