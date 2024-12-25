/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:00:08 by vkostand          #+#    #+#             */
/*   Updated: 2024/02/07 17:00:10 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*add;

	add = *lst;
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		while (add->next != NULL)
			add = add->next;
		add->next = new;
	}
}
