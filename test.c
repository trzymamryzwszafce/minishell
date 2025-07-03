#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

/*void	ft_check_white_spaces(char *str)
{
	int i;
	int len;

	len = ft_strlen(str);
	i = 0;
	while (str[i] == 32 || str[i] == 9)
	{

	}
}*/

int main(void)
{
	char *input;

	using_history(); //historia tego co było wcześniej wpisywane w >>>

	while (1) {
		input = readline(">>> ");
		if (!input)
			return (0); //potrzebne
//		ft_check_white_spaces(input);
		if (strcmp(input, "/log") == 0)
			printf("LOG: This is a message\n"); 
		else if (*input)
		{
			add_history(input); //dodajemy historię
			printf("You typed: %s\n", input);
		}
		free(input);
	}
	rl_clear_history(); //czyścimy historie z >>>
	return (0);
}

