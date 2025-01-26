/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:03:14 by kizuna            #+#    #+#             */
/*   Updated: 2025/01/26 18:07:10 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../include/libft.h"

static int	ft_num_len(unsigned int num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

static void	ft_put_num(unsigned int num)
{
	if (num >= 10)
	{
		ft_put_num(num / 10);
		ft_put_num(num % 10);
	}
	else
		ft_print_char(num + '0');
}

int	ft_print_unsigned(unsigned int num)
{
	ft_put_num(num);
	return (ft_num_len(num));
}
