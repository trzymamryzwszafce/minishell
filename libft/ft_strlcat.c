/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:05:13 by szmadeja          #+#    #+#             */
/*   Updated: 2024/12/18 22:12:33 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	if ((!dest || !src) && n == 0)
		return (0);
	i = 0;
	j = 0;
	while (dest[i] && i < n)
		i++;
	while (src[j] && (i + j + 1) < n)
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i < n)
		dest[i + j] = '\0';
	return (i + ft_strlen(src));
}
