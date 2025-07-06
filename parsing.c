#include "minishell.h"

int	ft_count_words(char **array)
{
	int count;

	count = 0;
	if (!array)
		return (0);
	while (array[count])
		count++;
	return (count);
}

void ft_null_lexer(t_lexer *cmd_line)
{
	cmd_line->command = NULL;
	cmd_line->flag = NULL;
	cmd_line->argument = NULL;
	cmd_line->type = NULL;
	cmd_line->next = NULL;
}

int ft_is_cmd(char *cmd)
{
	return (1); //true - potem napisze porządne sprawdzenie
}

int ft_is_type(char *cmd)
{
	if (ft_strcmp(cmd, "|") == 0)
		return (1);
	else if (ft_strcmp(cmd, "<") == 0)
		return (1);
	else if (ft_strcmp(cmd, ">") == 0)
		return (1);
	else if (ft_strcmp(cmd, "<<") == 0)
		return (1);
	else if (ft_strcmp(cmd, ">>") == 0)
		return (1);
	else
		return (0);
}

void ft_lexer(t_mini *arguments)
{
	t_lexer *cmd_line;
	t_lexer *new_node;
	int num_of_args;
	int i;

	i = 0;
	num_of_args = ft_count_words(arguments->arg_list);
	// pierwszy node
	cmd_line = malloc(sizeof(t_lexer));
	if (!cmd_line)
    	return ;
	ft_null_lexer(cmd_line);
	arguments->lexer = cmd_line;
	while (i < num_of_args)
	{
		if (ft_is_cmd(arguments->arg_list[i]) == 1) //czy pierwszy argument jest command - problem z redirect!!!!!!!!!
		{
			cmd_line->command = ft_strdup(arguments->arg_list[i]);
			i++;
		}
		else
		{
			printf("%s: command not found\n", arguments->arg_list[i]);
			exit(1);
		}
		if (arguments->arg_list[i] && arguments->arg_list[i][0] == '-')
		{
			cmd_line->flag = ft_strdup(arguments->arg_list[i]);
			i++;
		}
		if (arguments->arg_list[i])
		{
			cmd_line->argument = ft_strdup(arguments->arg_list[i]);
			i++;
		}
		if (arguments->arg_list[i] && ft_is_type(arguments->arg_list[i]))
		{
			cmd_line->type = ft_strdup(arguments->arg_list[i]);
			i++;
		}
		else
			return ;
		if (i < num_of_args)
		{
			new_node = malloc(sizeof(t_lexer));
			if (!new_node)
				return ;
			ft_null_lexer(new_node);
			cmd_line->next = new_node;
			cmd_line = new_node;
		}
		else
			cmd_line->next = NULL;
	}
}

void ft_split_input(t_mini *arguments, char *input)
{
	int i;
	int count;
	char **splited_input;

	i = 0;
	count = 0;
	splited_input = ft_split(input, ' ');
	if (!splited_input)
		return ;
	while (splited_input[count])
		count++;
	arguments->arg_list = malloc(sizeof(char *) * (count + 1));
	if (!arguments->arg_list)
		return ;
	while (i < count)
	{
		arguments->arg_list[i] = ft_strdup(splited_input[i]);
		i++;
	}
	arguments->arg_list[i] = NULL;
    ft_free_split(splited_input);
}
