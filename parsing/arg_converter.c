/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_converter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorbi <sorbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:14:58 by nadamczy          #+#    #+#             */
/*   Updated: 2025/12/05 22:02:41 by sorbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_envp_value_converter(t_convert *sign,
	char *str, int *i, char *new_str)
{
	int		j;
	char	*temp_key;
	char	*temp_value;
	char	*tmp_dup;

	(*i)++;
	j = *i;
	if (str[*i] == '?')
		return (ft_handle_exit_code(sign, i, new_str));
	while (str[*i] && str[*i] != '\'' && str[*i] != '\"'
		&& str[*i] != '$' && str[*i] != ' ')
		(*i)++;
	temp_key = ft_substr(str, j, *i - j);
	temp_value = ft_get_envp_value(sign->envp, temp_key);
	free(temp_key);
	if (temp_value)
		tmp_dup = ft_strdup(temp_value);
	else
		tmp_dup = ft_strdup("");
	new_str = ft_join_and_free(new_str, tmp_dup);
	free(tmp_dup);
	return (new_str);
}

char	*ft_handle_single_quote(char *str, t_convert *sign,
	int *i, char *new_str)
{
	if (!sign->single_q)
	{
		sign->single_q = true;
		new_str = ft_change_arg(str, sign, i, new_str);
		sign->single_q = false;
	}
	else
	{
		sign->single_q = false;
		(*i)++;
	}
	return (new_str);
}

char	*ft_handle_double_quote(char *str, t_convert *sign,
	int *i, char *new_str)
{
	if (!sign->double_q)
	{
		sign->double_q = true;
		new_str = ft_change_arg(str, sign, i, new_str);
		sign->double_q = false;
	}
	else
	{
		sign->double_q = false;
		(*i)++;
	}
	return (new_str);
}

char	*ft_convert(t_token str, t_envp **envp, t_convert *sign)
{
	char	*new_str;
	int		i;

	new_str = ft_strdup("");
	i = 0;
	sign->double_q = false;
	sign->single_q = false;
	sign->envp = envp;
	while (i < (int )ft_strlen(str.elem))
	{
		if (str.elem[i] == '\'' && !sign->double_q)
			new_str = ft_handle_single_quote(str.elem, sign, &i, new_str);
		else if (str.elem[i] == '"' && !sign->single_q)
			new_str = ft_handle_double_quote(str.elem, sign, &i, new_str);
		else if (str.elem[i] == '$' && !sign->single_q)
			new_str = ft_envp_value_converter(sign, str.elem, &i, new_str);
		else
			new_str = ft_change_arg(str.elem, sign, &i, new_str);
	}
	return (new_str);
}

void	ft_arg_converter(t_token *token, t_envp **envp, t_data *data)
{
	t_token		*cur;
	t_convert	sign;
	char		*new_str;

	cur = token;
	sign.exit_code = data->ls_exit;
	while (cur->next != NULL)
	{
		if (cur->type == ARG || cur->type == ARG_IN || cur->type == ARG_OUT)
		{
			new_str = ft_convert(*cur, envp, &sign);
			free(cur->elem);
			cur->elem = new_str;
			new_str = NULL;
		}
		cur = cur->next;
	}
}
