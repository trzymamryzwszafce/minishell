/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:35:37 by szmadeja          #+#    #+#             */
/*   Updated: 2025/01/11 03:18:09 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_char(char c)
{
	return (write(1, &c, 1));
}

int	ft_str(char *str)
{
	int	i;

	if (str == NULL)
		return (ft_str("(null)"));
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_ptr(void *ptr)
{
	if (ptr == NULL)
		return (ft_str("(nil)"));
	ft_char('0');
	ft_char('x');
	return (ft_hexptr((unsigned long)ptr) + 2);
}

int	ft_format(char letter, va_list ap)
{
	int	i;

	i = 0;
	if (letter == 'c')
		i += ft_char(va_arg(ap, int));
	else if (letter == 's')
		i += ft_str(va_arg(ap, char *));
	else if (letter == 'p')
		i += ft_ptr(va_arg(ap, void *));
	else if (letter == 'd' || letter == 'i')
		i += ft_dec(va_arg(ap, int));
	else if (letter == 'u')
		i += ft_udec(va_arg(ap, unsigned int));
	else if (letter == 'x')
		i += ft_lhex(va_arg(ap, unsigned int));
	else if (letter == 'X')
		i += ft_uhex(va_arg(ap, unsigned int));
	else if (letter == '%')
		i += ft_char('%');
	else
		i += write(1, &letter, 1);
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;

	va_start(ap, format);
	i = 0;
	while (*format)
	{
		if (*format == '%')
			i += ft_format(*(++format), ap);
		else
			i += write(1, format, 1);
		++format;
	}
	va_end(ap);
	return (i);
}
