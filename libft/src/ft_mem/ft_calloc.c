/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishino <kishino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:06:14 by kizuna            #+#    #+#             */
/*   Updated: 2024/12/02 17:23:13 by kishino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	len;

	if (count && size > SIZE_MAX / count)
		return (NULL);
	if (count == 0 || size == 0)
		len = 1;
	len = count * size;
	ptr = malloc(len);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, len);
	return (ptr);
}
