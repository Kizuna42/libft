/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:03:04 by kizuna            #+#    #+#             */
/*   Updated: 2025/01/25 18:15:28 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../include/libft.h"

static int	ft_get_str_len(char *str, t_format *fmt)
{
	int	len;

	if (!str)
		len = 6;
	else
		len = ft_strlen(str);
	if (fmt->precision >= 0 && fmt->precision < len)
		len = fmt->precision;
	return (len);
}

static void	ft_put_width(int width, int len, char c)
{
	while (width > len)
	{
		write(1, &c, 1);
		width--;
	}
}

static void	ft_put_str(char *str, int len)
{
	int	i;

	i = 0;
	while (i < len && str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_print_str(char *str, t_format *fmt)
{
	int		len;
	int		print_len;
	char	padding;

	if (!str)
		str = "(null)";
	len = ft_get_str_len(str, fmt);
	print_len = len;
	if (fmt->width > len)
		print_len = fmt->width;
	padding = ' ';
	if (fmt->zero_pad && !fmt->left_justify)
		padding = '0';
	if (!fmt->left_justify)
		ft_put_width(fmt->width, len, padding);
	ft_put_str(str, len);
	if (fmt->left_justify)
		ft_put_width(fmt->width, len, ' ');
	return (print_len);
}
