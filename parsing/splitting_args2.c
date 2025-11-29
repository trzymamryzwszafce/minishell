/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting_args2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadamczy <nadamczy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:16:11 by nadamczy          #+#    #+#             */
/*   Updated: 2025/11/29 12:16:12 by nadamczy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_input_words(char const *s)
{
	int	count;
	int	i;

	i = 0;
	if (!s)
		return (0);
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '>'
			|| s[i] == '<' || s[i] == '|')
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != ' ' && s[i] != '\t' && s[i] != '>'
			&& s[i] != '<' && s[i] != '|' && s[i] != '\0')
			i++;
	}
	return (count);
}

t_token	*ft_create_node(t_token *cur)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	if (!new_node)
		return (NULL);
	if (cur)
	{
		cur->next = new_node;
		new_node->prev = cur;
	}
	return (new_node);
}

t_token	*ft_add_node(t_token *token, char *s, int *i, int n)
{
	int		j;
	char	*string;

	if (n <= 0 || !token)
		return (token);
	string = ft_calloc(1, n + 1);
	j = 0;
	while (j < n && s[*i])
	{
		string[j] = s[*i];
		(*i)++;
		j++;
	}
	string[j] = '\0';
	token->elem = string;
	token->next = ft_create_node(token);
	return (token->next);
}

int	ft_skip_quotes(char *s, int *n)
{
	char	q;
	int		count;

	count = 0;
	q = s[*n];
	(*n)++;
	count++;
	while (s[*n] && s[*n] != q)
	{
		(*n)++;
		count++;
	}
	if (s[*n] == q)
	{
		(*n)++;
		count++;
	}
	return (count);
}
