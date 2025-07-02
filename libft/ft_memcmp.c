/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:54:28 by szmadeja          #+#    #+#             */
/*   Updated: 2024/12/04 19:40:10 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*z1;
	unsigned char	*z2;
	size_t			i;

	if (n == 0)
		return (0);
	z1 = (unsigned char *)s1;
	z2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (z1[i] != z2[i])
			return (z1[i] - z2[i]);
		i++;
	}
	return (0);
}

/*int main()
{
    char arr1[] = "Hellz";
    char arr2[] = "Hellz";

    int result = ft_memcmp(arr1, arr2, 5);

    if (result == 0)
        printf("Bloki pamięci są identyczne.\n");
    else if (result < 0)
        printf("Pierwszy blok pamięci jest mniejszy.\n");
    else
        printf("Pierwszy blok pamięci jest większy.\n");

    return 0;
}*/
