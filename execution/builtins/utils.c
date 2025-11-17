#include "../../minishell.h"

int	valid_check(char *s)
{
	int	i;

	i = 0;
	if (!s || !(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	i++;
	while (s[i] && s[i] != '=')
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	print_expo_env(t_envp *env)
{
	t_envp	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_printf("declare -x %s", tmp->key);
		if (tmp->value)
			ft_printf("=\"%s\"", tmp->value);
		ft_printf("\n");
		tmp = tmp->next;
	}
	return (0);
}
