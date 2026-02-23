/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:03:40 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/05/01 18:36:14 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
/*
Similar to  memcpy(), the function copies n bytes from memory area src to memory area dest.  
The memory areas might overlap : if (dest > src) -> backward copy ; forward copy otherwise.
*/
{
	size_t			i;
	unsigned char	*dest_temp;
	unsigned char	*src_temp;

	dest_temp = (unsigned char *)dest;
	src_temp = (unsigned char *)src;
	if (dest == src)
		return (dest);
	if (dest > src)
	{
		i = n;
		while (i-- > 0)
			dest_temp[i] = src_temp[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			dest_temp[i] = src_temp[i];
			i++;
		}
	}
	return (dest);
}
