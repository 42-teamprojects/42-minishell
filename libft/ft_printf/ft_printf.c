/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:52:04 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/18 14:27:09 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// format specification
int	formatspecs(va_list ap, char format)
{
	int	size;

	size = 0;
	if (format == 'c')
		size = ft_putchar(va_arg(ap, int));
	else if (format == 's')
		size = ft_putstr(va_arg(ap, char *));
	else if (format == 'd' || format == 'i')
		size = ft_put_itoa(va_arg(ap, int));
	else if (format == 'u')
		size = ft_put_uitoa(va_arg(ap, int));
	else if (format == 'x' || format == 'X')
		size = ft_put_hexa(va_arg(ap, int), format);
	else if (format == 'p')
		size += ft_put_pointer(va_arg(ap, unsigned long long int));
	return (size);
}

int	ft_printf(const char *s, ...)
{
	size_t	printed;
	va_list	ap;
	int		i;

	i = 0;
	printed = 0;
	va_start(ap, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			if (!s[i])
				break ;
			if (s[i] == '%' && s[i])
				printed += ft_putchar('%');
			printed += formatspecs(ap, s[i]);
		}
		else
			printed += ft_putchar(s[i]);
		i++;
	}
	va_end(ap);
	return (printed);
}

int	ft_printf_fd(int fd, const char *s, ...)
{
	size_t	printed;
	va_list	ap;
	int		i;

	i = 0;
	printed = 0;
	va_start(ap, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			if (!s[i])
				break ;
			if (s[i] == '%' && s[i])
				printed += write(fd, "%", 1);
			printed += formatspecs(ap, s[i]);
		}
		else
			printed += write(fd, &s[i], 1);
		i++;
	}
	va_end(ap);
	return (printed);
}
