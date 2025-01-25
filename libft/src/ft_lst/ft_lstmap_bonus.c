/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishino <kishino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:14:03 by kishino           #+#    #+#             */
/*   Updated: 2024/12/02 18:14:26 by kishino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*ptr;

	if (!lst)
		return (0);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (0);
	ptr = new;
	lst = lst->next;
	while (lst)
	{
		ptr->next = ft_lstnew(f(lst->content));
		if (!ptr->next)
		{
			ft_lstclear(&new, del);
			return (0);
		}
		ptr = ptr->next;
		lst = lst->next;
	}
	return (new);
}
