/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:36:23 by szmadeja          #+#    #+#             */
/*   Updated: 2025/01/11 03:15:02 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hexptr(unsigned long n)
{
	char	*hex;
	int		i;

	i = 0;
	hex = "0123456789abcdef";
	if (n >= 16)
		i += ft_hexptr(n / 16);
	ft_char(hex[n % 16]);
	i++;
	return (i);
}

int	ft_dec(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		i += ft_char('-');
		i += ft_char('2');
		n = 147483648;
	}
	if (n < 0)
	{
		i += ft_char('-');
		n *= -1;
	}
	if (n > 9)
	{
		i += ft_dec(n / 10);
		i += ft_dec(n % 10);
	}
	else
		i += ft_char(n + 48);
	return (i);
}

int	ft_udec(unsigned int n)
{
	int	i;

	i = 0;
	if (n > 9)
	{
		i += ft_udec(n / 10);
		i += ft_udec(n % 10);
	}
	else
		i += ft_char(n + 48);
	return (i);
}

int	ft_lhex(unsigned int n)
{
	char	*hex;
	int		i;

	i = 0;
	hex = "0123456789abcdef";
	if (n >= 16)
		i += ft_lhex(n / 16);
	ft_char(hex[n % 16]);
	i++;
	return (i);
}

int	ft_uhex(unsigned int n)
{
	char	*hex;
	int		i;

	i = 0;
	hex = "0123456789ABCDEF";
	if (n >= 16)
		i += ft_uhex(n / 16);
	ft_char(hex[n % 16]);
	i++;
	return (i);
}
