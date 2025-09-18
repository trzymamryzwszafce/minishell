#include "minishell.h"

int	ft_count_input_words(char const *s)
{
	int	count;
	int	i;

	i = 0;
	if (!s)
		return (0);
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '>' || s[i] == '<')
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != ' ' && s[i] != '\t' && s[i] != '>' && s[i] != '<' && s[i] != '\0')
			i++;
	}
	return (count);
}

/*void ft_ultimate_split(char *input)
{
	int	i;
	char	**splited_input;

	splited_input = (char **)malloc(sizeof(char *) * ft_count_input_words(input) + 1);
	if (!splited_input)
		return ;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t' || input[i] == '>' || input[i] == '<')
		{
			i++;
		}
	}
}*/

t_token	*ft_create_node(t_token *cur)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	if (!new_node)
		return (NULL);
	if (cur)
		cur->next = new_node;
	return (new_node);
}

void ft_add_node(t_token *token, char *s, int *i, int n) //tu trzeba uaktualnić i, n - num of chars to add
{
	int	j;
	char	*string;

	j = 0;
	string = (char *)malloc(sizeof(char *) * (n + 1));
	while (j < n)
	{
		string[j] = s[*i];
		(*i)++;
		j++;
	}
	string[j] = '\0';
	token->elem = string;
	token->next = ft_create_node(token);
}

int ft_count_chars(char *s, int n) //n - num where to start
{
	int	count;

	count = 0;
	while (s[n] != ' ' && s[n] != '\t' && s[n] != '<' && s[n] != '>' && s[n] != '|' && s[n])
	{
		count++;
		n++;
	}
	return (count);
}

void	ft_is_limiter(t_token *token, char *input, int *i)
{
	int n;
	
	if (!input[*i])
		return ;
	if ((input[*i] == '>' && input[*i + 1] == '>' && input[*i + 1]) || (input[*i] == '<' && input[*i + 1] == '<' && input[*i + 1]))
	{
		printf("dupa");
		ft_add_node(token, input, i,  2);
			return ;
	}
	if (input[*i] == '<' || input[*i] == '>' || input[*i] == '|')
	{
		ft_add_node(token, input, i, 1);
		return ;
	}
	if (input[*i] == ' ' || input[*i] == '\t')
	{
		while (input[*i] == ' ' || input[*i] == '\t')
			(*i)++;
        	return;
	}
	n = ft_count_chars(input, *i);
	ft_add_node(token, input, i, n);
}

void ft_split_input(t_token *tokens, char *input)
{
	int	i;

	i = 0;
	printf("wypierdalaj");
	while (input[i])
	{
		printf("dupsko");
		ft_is_limiter(tokens, input, &i);
      		i++;
	}
}

/*void	ft_split_input(t_mini *arguments, char *input)
{
	int		i;
	int		count;
	char	**splited_input;

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
}*/

void ft_free_mini(t_mini *arguments)
{
	t_lexer *tmp;
	ft_free_split(arguments->arg_list);
	while (arguments->lexer)
	{
		tmp = arguments->lexer->next;
		free(arguments->lexer->command);
		free(arguments->lexer->flag);
		if (arguments->lexer->params)
			ft_free_split(arguments->lexer->params);
		if (arguments->lexer->type)
			ft_free_split(arguments->lexer->type);
		if (arguments->lexer->redir_targets)
			ft_free_split(arguments->lexer->redir_targets);
		free(arguments->lexer);
		arguments->lexer = tmp;
	}
	free(arguments);
}

int main(void)
{
	t_mini *arguments;
	char *input;
	t_token *tokens;
	using_history();
	while (1)
	{
		input = readline(">>> ");
		if (!input)
			return (0);
		else if (*input)
		{
			add_history(input);
			arguments = malloc(sizeof(t_mini));
			if (!arguments)
				return (1);
			tokens = malloc(sizeof(t_token));
			if (!tokens)
				return (1);
			printf("dupaa");
			ft_split_input(tokens, input);
		}
		free(input);
//		ft_lexer(arguments);
//		ft_parse_lexer(arguments); <- to będzie żeby parsing zrobić struktury na strukture juz koncową
		

		for (t_token *p = tokens; p; p = p->next) {
			printf("node: %s\n", p->elem ? p->elem : "(null)");
		}

	//	ft_free_mini(arguments);
	}
	rl_clear_history(); //czyścimy historie z >>> - nie wiem czy potrzebne
	return (0);
}

