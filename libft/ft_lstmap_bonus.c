/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:00:33 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/05/06 17:01:18 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	create_new_node(t_list *lst, t_list **new_node,
					void *(*f)(void *), void (*del)(void *))
{
	void	*new_content;

	new_content = f(lst -> content);
	*new_node = ft_lstnew(new_content);
	if (!*new_node)
	{
		del(new_content);
		return (1);
	}
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
/*
Parameters :
  lst: The address of a pointer to a node.
  f: The address of the function used to iterate on the list.
  del: The address of the function used to delete the 
        content of a node if needed
Returns :
  The new list.
  NULL if the allocation fails.

Iterates the list ’lst’ and applies the function
’f’ on the content of each node. Creates a new
list resulting of the successive applications of
the function ’f’. The ’del’ function is used to
delete the content of a node if needed.
*/
{
	t_list	*new_lst;
	t_list	*new_node;
	t_list	*last_node;

	if (!lst)
		return (NULL);
	if (create_new_node(lst, &new_lst, f, del))
		return (NULL);
	last_node = new_lst;
	lst = lst -> next;
	while (lst)
	{
		if (create_new_node(lst, &new_node, f, del))
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		else
		{
			ft_lstadd_back(&last_node, new_node);
			last_node = new_node;
		}
		lst = lst -> next;
	}
	return (new_lst);
}
