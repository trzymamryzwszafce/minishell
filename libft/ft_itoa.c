/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:09:44 by szmadeja          #+#    #+#             */
/*   Updated: 2024/12/19 00:32:49 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

static int	ft_numlen(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_itoa(int n)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = ft_numlen(n);
	if (len == 0)
		return (ft_strdup("0"));
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	i = len - 1;
	while (n != 0)
	{
		str[i] = ft_abs(n % 10) + 48;
		n /= 10;
		i--;
	}
	str[len] = '\0';
	return (str);
}
/*
int main()
{
	printf("%s\n", ft_itoa(-1));
	return 0;
}*/
