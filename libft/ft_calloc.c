/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 01:34:47 by szmadeja          #+#    #+#             */
/*   Updated: 2024/12/07 02:47:29 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmem, size_t n)
{
	void	*ptr;

	if (nmem != 0 && n > SIZE_MAX / nmem)
		return (NULL);
	ptr = (void *)malloc(nmem * n);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmem * n);
	return (ptr);
}
