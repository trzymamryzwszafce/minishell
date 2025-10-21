#include "../minishell.h"

char *ft_assign_key(char *str)
{
	int i;
	int j;
	char *key;

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
			{
				key[j] = str[j];
				j++;
			}
			key[j] = '\0';
			return (key);
		}
		i++;
	}
	return (key);
}

char *ft_assign_value(char *str)
{
	int i;
	int j;
	int k;
	char *value;

	i = -1; //samo key i = bez value
	j = 0; //na całość
	k = 0; //na value
	while(str[++i])
	{
		if (str[i] == '=')
		{
			j = i;
			while (str[j])
				j++;
			if (j - i < 2)
				return (NULL);
			value = malloc(j - 1 + 1);
			while (str[i])
				value[k++] = str[i++];
			value[k] = '\0';
			return (value);
		}
	}
	return (NULL);
}
void ft_add_envp_list(t_envp *envp, char *key, char *value)
{
    t_envp *new;
    

    new = malloc(sizeof(t_envp));
    new->key = ft_strdup(key);
    new->value = ft_strdup(value);
    new->next = NULL;
    if (envp == NULL)
    {
        envp = new;
        return ;
    }
}

void ft_add_to_envp(t_envp *envp, char *key, char *value)
{
    if (!key)
        return ;
    ft_add_envp_list(envp, key, value);
    
}

void ft_create_envp(char **environ)
{
	int i;
	t_envp *envp;
	char *key;
	char *value;  

	i = 0;
	envp = malloc(sizeof(t_envp));
	while (environ[i])
	{
		key = ft_assign_key(environ[i]);
		value = ft_assign_value(environ[i]);
		if (key && value)
		{
			ft_add_to_envp(envp, key, value);
			free(key);
			free(value);
		}
		i++;
	}


}
