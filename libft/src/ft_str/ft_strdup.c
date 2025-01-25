/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishino <kishino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:07:43 by kizuna            #+#    #+#             */
/*   Updated: 2024/12/02 20:11:44 by kishino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

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
