/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:02:29 by kizuna            #+#    #+#             */
/*   Updated: 2025/01/25 16:02:36 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int ft_hex_len(unsigned int num)
{
    int len;

    len = 0;
    if (num == 0)
        return (1);
    while (num != 0)
    {
        len++;
        num = num / 16;
    }
    return (len);
}

static void ft_put_hex(unsigned int num, const char format)
{
    if (num >= 16)
    {
        ft_put_hex(num / 16, format);
        ft_put_hex(num % 16, format);
    }
    else
    {
        if (num <= 9)
            ft_print_char(num + '0');
        else
        {
            if (format == 'x')
                ft_print_char(num - 10 + 'a');
            else if (format == 'X')
                ft_print_char(num - 10 + 'A');
        }
    }
}

int ft_print_hex(unsigned int num, const char format)
{
    ft_put_hex(num, format);
    return (ft_hex_len(num));
}