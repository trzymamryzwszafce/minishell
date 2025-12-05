/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_converter2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorbi <sorbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:15:30 by nadamczy          #+#    #+#             */
/*   Updated: 2025/12/05 21:59:49 by sorbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_join_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

char	*ft_substr_join_free(char *new_str, char *str, int start, int len)
{
	char	*temp;

	temp = ft_substr(str, start, len);
	if (!temp)
		return (new_str);
	new_str = ft_join_and_free(new_str, temp);
	free(temp);
	return (new_str);
}

char	*ft_double_quote(char *str, int *i, char *new_str, t_convert *sign)
{
	int		j;

	if (str[*i] == '"')
		(*i)++;
	j = *i;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			new_str = ft_substr_join_free(new_str, str, j, *i - j);
			new_str = ft_envp_value_converter(sign, str, i, new_str);
			j = *i;
		}
		else
			(*i)++;
	}
	if (*i > j)
		new_str = ft_substr_join_free(new_str, str, j, *i - j);
	if (str[*i] == '"')
		(*i)++;
	return (new_str);
}

char	*ft_no_quote(char *str, t_convert *sign, int *i, char *new_str)
{
	int		j;

	j = *i;
	if (!sign->double_q)
	{
		while (str[*i] && str[*i] != '$' && str[*i] != '\'' && str[*i] != '\"')
			(*i)++;
		new_str = ft_substr_join_free(new_str, str, j, *i - j);
	}
	else
	{
		while (str[*i] && str[*i] != '$' && str[*i] != '\"')
			(*i)++;
		new_str = ft_substr_join_free(new_str, str, j, *i - j);
	}
	return (new_str);
}

char	*ft_change_arg(char *str, t_convert *sign, int *i, char *new_str)
{
	int		start;

	if (!str)
		return (NULL);
	if (!new_str)
		return (ft_strdup(""));
	if (!sign->double_q && !sign->single_q)
		new_str = ft_no_quote(str, sign, i, new_str);
	if (sign->double_q)
		new_str = ft_double_quote(str, i, new_str, sign);
	else if (sign->single_q)
	{
		if (str[*i] == '\'')
			(*i)++;
		start = *i;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
		new_str = ft_substr_join_free(new_str, str, start, *i - start);
		if (str[*i] == '\'')
			(*i)++;
	}
	return (new_str);
}
