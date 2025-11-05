#include "../minishell.h"

char *ft_join_and_free(char *s1, char *s2) //to do zmiany
{
    char *res;
    char *a = s1 ? s1 : ft_strdup("");
    char *b = s2 ? s2 : ft_strdup("");

    res = ft_strjoin(a, b);
    if (s1)
        free(s1);
    if (!s2) // jeśli stworzyliśmy b (ft_strdup("")) to musimy je zwolnić
        free(b);
    // nie free(s2) tutaj, bo caller (ten który stworzył s2) powinien je zwolnić
    return (res);
}

char *ft_double_quote(char *str, t_convert *sign, int *i, char *new_str)
{80
	char *temp;
	int j;

	(void)sign;
	if (str[*i] == '"')
		(*i)++;
	j = *i;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			break;
		(*i)++;
	}
	if (*i > j)
	{
		temp = ft_substr(str, j, *i - j);
		new_str = ft_join_and_free(new_str, temp);
		free(temp);
	}
	if (str[*i] == '"')
		(*i)++;
	return (new_str);
}

char *ft_no_quote(char *str, t_convert *sign, int *i, char *new_str)
{
	char *temp;
	int j;//przechowalnia dla i na chwile

	j = *i;//początek
	if (!sign->double_q)
	{
		while (str[*i] && str[*i] != '$' && str[*i] != '\'' && str[*i] != '\"')
			(*i)++;
		temp = ft_substr(str, j, *i - j);
		new_str = ft_join_and_free(new_str, temp);
		free(temp);
	}
	else
	{
		while (str[*i] && str[*i] != '$' && str[*i] != '\"')
			(*i)++;
		temp = ft_substr(str, j, *i - j);
		new_str = ft_join_and_free(new_str, temp);
		free(temp);
	}
	return (new_str);
}

char *ft_change_arg(char *str, t_convert *sign, int *i, char *new_str)
{
	if (!str)
        return (NULL);
	if (!new_str)
		return (ft_strdup(""));
	if (!sign->double_q && !sign->single_q)
		new_str = ft_no_quote(str, sign, i, new_str);
	if (sign->double_q)
		new_str = ft_double_quote(str, sign, i, new_str);
	else if (sign->single_q)
	{
		/* copy literally until next single quote */
		char *temp;
		int start;
		if (str[*i] == '\'')
			(*i)++;
		start = *i;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
		temp = ft_substr(str, start, *i - start);
		new_str = ft_join_and_free(new_str, temp);
		free(temp);
		if (str[*i] == '\'')
			(*i)++;
	}
	return (new_str);
}