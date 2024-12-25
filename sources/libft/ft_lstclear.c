/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:00:48 by vkostand          #+#    #+#             */
/*   Updated: 2024/02/07 17:00:50 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst1;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		lst1 = (*lst)->next;
		(*del)((*lst)->content);
		free(*lst);
		*lst = lst1;
	}
	*lst = NULL;
}
