/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:02:40 by kizuna            #+#    #+#             */
/*   Updated: 2025/01/25 16:02:50 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int ft_num_len(int num)
{
    int len;

    len = 0;
    if (num == 0)
        return (1);
    if (num < 0)
        len++;
    while (num != 0)
    {
        len++;
        num = num / 10;
    }
    return (len);
}

static void ft_put_num(int num)
{
    if (num < 0)
    {
        ft_print_char('-');
        if (num == -2147483648)
        {
            ft_print_char('2');
            num = 147483648;
        }
        else
            num = -num;
    }
    if (num >= 10)
    {
        ft_put_num(num / 10);
        ft_put_num(num % 10);
    }
    else
        ft_print_char(num + '0');
}

int ft_print_nbr(int num)
{
    ft_put_num(num);
    return (ft_num_len(num));
}