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
// char *ft_double_quote(char *str, t_convert *sign, int *i, char *new_str) //te dosłowne
// {
// 	char deli;

// 	deli = str[*i];
// }

char *ft_no_quote(char *str, t_convert *sign, int *i, char *new_str)
{
	char *temp;
	int j;//przechowalnia dla i na chwile

	j = *i;//początek
	while (str[*i] && str[*i] != '$' && str[*i] != '\'' && str[*i] != '\"')
		(*i)++;
	temp = ft_substr(str, j, *i - j);
	new_str = ft_join_and_free(new_str, temp);
	free(temp);
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
	// if (sign->double_q)
	// {
	// 	new_str = ft_double_quote(str, sign, &i, new_str);
	// }
	//dalej musze ogarnąć przypadki z quotami
	return (new_str);
}

char *ft_envp_value_converter(t_envp **envp, char *str, int *i, char *new_str)
{
	int j; //początek str
	char *temp_key; //bedzie przechowywał od znaku dolara do końca envp

	char *temp_value;
	char *tmp_dup;

	(*i)++;
	j = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '\"' && str[*i] != '$')
		(*i)++;
	temp_key = ft_substr(str, j, *i - j);
	temp_value = ft_get_envp_value(envp, temp_key);
	free(temp_key);
	/* duplicate value (or empty string) so we own the buffer passed to ft_join_and_free */
	if (temp_value)
		tmp_dup = ft_strdup(temp_value);
	else
		tmp_dup = ft_strdup("");
	new_str = ft_join_and_free(new_str, tmp_dup);
	free(tmp_dup);
	return (new_str);
}

char *ft_convert(t_token str, t_envp **envp, t_convert *sign)
{
	char *new_str;
	int i;
	
	new_str = ft_strdup("");
	i = 0;
	sign->double_q = false;
	sign->single_q = false;
	sign->dolar_sign = false;
	while (i < (int )ft_strlen(str.elem))
	{
		if (str.elem[i] == '\'' && !sign->double_q)
			sign->single_q = !sign->single_q;
		else if (str.elem[i] == '\"' && !sign->single_q)
			sign->double_q = !sign->double_q;
		else if (str.elem[i] == '$' && !sign->double_q && !sign->single_q)
		{
			sign->dolar_sign = true; //pomyslec nad logiką tu
			new_str = ft_envp_value_converter(envp, str.elem, &i, new_str); //tutaj trzeba pamiętać że jeżeli po envp znajde quoty to musze się cofnąć o jedno i do tylu żeby moja funkcja mogła potem zaznaczyć że znalazła quota - w tej nie mam struktury quotowej
			sign->dolar_sign = false;
		}
		else
			new_str = ft_change_arg(str.elem, sign, &i, new_str);
	}
	return (new_str);
}

void ft_arg_converter(t_token *token, t_envp **envp)
{
	t_token *cur;
	t_convert sign;
	char *new_str;

	cur = token;
	while (cur->next != NULL) //cur != NULL
	{
		if (cur->type == ARG)
		{
			new_str = ft_convert(*cur, envp, &sign);
			free(cur->elem);
			cur->elem = new_str;
			new_str = NULL;
			printf("%s\n",cur->elem);
		}
		cur = cur->next;
	}
}