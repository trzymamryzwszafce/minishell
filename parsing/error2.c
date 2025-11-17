#include "../minishell.h"

int ft_quote_error(char *s)
{
	int	len;
	char deli;
	int i;

	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (s[i] == 34 || s[i] == 39)
		{
			deli = s[i];
			i++;
			while (s[i] != deli && s[i])
				i++;
			if (!s[i])
				return (258);
		}
		i++;
	}
	return (0);
}

int ft_pipe_error(int position, char *current, char *next, enum s_type next_type)
{
	if (position == 0 && ft_strcmp(current, "|") == 0)
		return (258);
	if (!next && ft_strcmp(current, "|") == 0)
		return (258);
	if (current && ft_strcmp(current, "|") == 0 && ft_strcmp(next, "|") == 0)
		return (258);
	if (current && ft_strcmp(current, "|") == 0 && (next_type == R_IN || next_type == R_OUT_APP || next_type == R_OUT_TRUNC || next_type == R_HEREDOC))
		return (258);
	return (0);
}

int ft_redir_error(enum s_type cur_type, enum s_type next_type)
{
	if ((cur_type == R_IN || cur_type == R_OUT_APP || cur_type == R_OUT_TRUNC || cur_type == R_HEREDOC) && 
		(next_type == R_IN || next_type == R_OUT_APP || next_type == R_OUT_TRUNC || next_type == R_HEREDOC || next_type == PIPE))
		return (258);
	return (0);
}

int ft_type_input(t_token *token, t_envp **envp, t_data *data)
{
	t_token *cur;
	if (!token)
		return (0);

	cur = token;
	while (cur->next != NULL)
	{
		ft_add_type(cur);
		cur = cur->next;
	}
	cur = token;
	while (cur->next != NULL)
	{
		ft_add_type_arg(cur);
		cur = cur->next;
	}
	//function to take care of envs
	ft_arg_converter(token, envp, data);
	return (ft_errors(token));
}
