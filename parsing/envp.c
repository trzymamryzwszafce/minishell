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
			while (str[++i])
				value[k++] = str[i];
			value[k] = '\0';
			return (value);
		}
	}
	return (NULL);
}
void ft_add_envp_list(t_envp **envp, char *key, char *value)
{
    t_envp *new;
	t_envp *node;

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

char *ft_get_envp_value(t_envp **envp, char *key)
{
	t_envp *node;

	if (!envp || !key)
		return (NULL);
	node = *envp;
	while (node != NULL)
	{
		if (!ft_strcmp(node->key, key)) //sa takie same
		{
			if (node->value == NULL)
				return (ft_strdup(""));
			return (node->value);
		}
		node = node->next;
	}
	return (NULL);
}

void ft_new_envp_value(t_envp **envp, char *key, char *value)
{
	t_envp *node;

	node = *envp;
	while (node != NULL)
	{
		if (!ft_strcmp(node->key, key))
		{
			free(node->value);
			node->value = ft_strdup(value);
			return ;
		}
		node = node->next;
	}
}

void ft_add_to_envp(t_envp **envp, char *key, char *value)
{
    if (!key)
        return ;
	if (ft_get_envp_value(envp, key) == NULL)
		ft_add_envp_list(envp, key, value);
	 else
	 	ft_new_envp_value(envp, key, value);
    
}
//debug
void	print_envs(t_envp *list)
{
	t_envp	*node;

	node = list;
	while (node)
	{
		printf("%s=", node->key);
		if (node->value)
			printf("%s", node->value);
		printf("\n");
		node = node->next;
	}
}

t_envp *ft_create_envp(char **environ)
{
	int i;
	t_envp *envp;
	char *key;
	char *value;  

	i = 0;
	envp = NULL;
	while (environ[i])
	{
		key = ft_assign_key(environ[i]);
		value = ft_assign_value(environ[i]);
		if (key && value)
		{
			ft_add_to_envp(&envp, key, value);
			free(key);
			free(value);
		}
		else
		{
		 	free(key);
		 	free(value);
		 }
	 	i++;
	}
	//print_envs(envp);
	return (envp);
}

