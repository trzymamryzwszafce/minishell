#include "minishell.h"



int main(void)
{
	int error;

	error = ft_parsing();
	//if error -> program zwraca nową linijkę ale nie kończy programu
	return (error);
}
