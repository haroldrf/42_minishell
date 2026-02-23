/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:00:59 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/05/06 17:01:18 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
/*
lst: The address of a pointer to a node.
f: The address of the function used to iterate on the list.

Iterates the list ’lst’ and applies the function
’f’ on the content of each node.
*/
{
	while (lst)
	{
		f(lst -> content);
		lst = lst -> next;
	}
}
