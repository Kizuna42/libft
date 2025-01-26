/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:03:32 by kizuna            #+#    #+#             */
/*   Updated: 2025/01/26 18:07:08 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../include/libft.h"

static void	ft_init_format(t_format *fmt)
{
	fmt->width = 0;
	fmt->precision = -1;
	fmt->left_justify = 0;
	fmt->zero_pad = 0;
	fmt->type = 0;
}

static int	ft_parse_flags(const char *format, int i, t_format *fmt)
{
	while (format[i] == '-' || format[i] == '0')
	{
		if (format[i] == '-')
			fmt->left_justify = 1;
		if (format[i] == '0' && !fmt->left_justify)
			fmt->zero_pad = 1;
		i++;
	}
	if (ft_isdigit(format[i]))
	{
		fmt->width = ft_atoi(&format[i]);
		while (ft_isdigit(format[i]))
			i++;
	}
	if (format[i] == '.')
	{
		i++;
		fmt->precision = ft_atoi(&format[i]);
		while (ft_isdigit(format[i]))
			i++;
		if (fmt->precision >= 0)
			fmt->zero_pad = 0;
	}
	fmt->type = format[i];
	return (i);
}

static int	ft_format(va_list args, t_format *fmt)
{
	int	print_length;

	print_length = 0;
	if (fmt->type == 'c')
		print_length += ft_print_char(va_arg(args, int));
	else if (fmt->type == 's')
		print_length += ft_print_str(va_arg(args, char *), fmt);
	else if (fmt->type == 'p')
		print_length += ft_print_ptr(va_arg(args, unsigned long long));
	else if (fmt->type == 'd' || fmt->type == 'i')
		print_length += ft_print_nbr(va_arg(args, int));
	else if (fmt->type == 'u')
		print_length += ft_print_unsigned(va_arg(args, unsigned int));
	else if (fmt->type == 'x' || fmt->type == 'X')
		print_length += ft_print_hex(va_arg(args, unsigned int), fmt->type);
	else if (fmt->type == '%')
		print_length += ft_print_char('%');
	return (print_length);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			i;
	int			print_length;
	t_format	fmt;

	i = 0;
	print_length = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			ft_init_format(&fmt);
			i = ft_parse_flags(format, i + 1, &fmt);
			print_length += ft_format(args, &fmt);
		}
		else
			print_length += ft_print_char(format[i]);
		i++;
	}
	va_end(args);
	return (print_length);
}
