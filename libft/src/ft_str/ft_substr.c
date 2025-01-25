/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishino <kishino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 00:40:15 by kizuna            #+#    #+#             */
/*   Updated: 2024/12/02 15:30:15 by kishino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	s_len;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (s_len < start)
		return (ft_strdup(""));
	if (s_len < start + len)
		len = s_len - start;
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (0);
	ft_memcpy(ptr, s + start, len);
	ptr[len] = 0;
	return (ptr);
}
