/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:07:43 by kizuna            #+#    #+#             */
/*   Updated: 2025/01/25 17:05:26 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s1)
	{
	char	*ptr;
	size_t	len;

	len = ft_strlen(s1) + 1;
	ptr = (char *)malloc(len);
	if (!ptr)
		return (0);
	ft_memcpy(ptr, s1, len);
	return (ptr);
}
