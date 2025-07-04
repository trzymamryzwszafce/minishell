/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 03:37:01 by szmadeja          #+#    #+#             */
/*   Updated: 2024/12/18 20:22:46 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *head)
{
	t_list	*last;

	if (!head)
		return ;
	if (!*lst)
	{
		*lst = head;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = head;
}
