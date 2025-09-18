#include "../minishell.h"

int	ft_count_args(char **args) //dodaje do listy arguments argumenty tak długo aż znajdzie NULL, pipe lub redirect - jak znajdzie kolejną komendę to doda ją do argumentów - to do naprawy!!!
{
	int	count;

	count = 0;
	while (args[count] && !ft_is_redirect(args[count]) && !ft_is_pipe(args[count]))
		count++;
	return (count);
}

int 	ft_count_only_args(char **args, int *i)
{
	int cnt;
	int k;

	cnt = 0;
	k  = *i;
	while (args[k] && !ft_is_redirect(args[k]) && !ft_is_pipe(args[k]))
	{
    	if (args[k][0] == '-')
        	;
    	else
        	cnt++;
    	k++;
	}
	return (cnt);
}

char	**ft_copy_args(char **arg_list, int start, int count)
{
	char	**result;
	int		i;

	result = malloc(sizeof(char *) * (count + 1));
	i = 0;
	if (!result)
		return (NULL);
	while (i < count)
	{
		result[i] = ft_strdup(arg_list[start + i]);
		i++;
	}
	result[i] = (NULL);
	return (result);
}

char	**add_to_str_array(char **array, char *str)
{
	int		i;
	char	**new_array;

	i = 0;
	if (array)
		while (array[i])
			i++;
	new_array = malloc(sizeof(char *) * (i + 2));
	if (!new_array)
		return (NULL);
	i = 0;
	while (array && array[i])
	{
		new_array[i] = array[i];
		i++;
	}
	new_array[i++] = ft_strdup(str);
	new_array[i] = NULL;
	free(array);
	return (new_array);
}

