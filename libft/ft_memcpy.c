/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:02:14 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/05/01 18:36:03 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
/*
The  memcpy() function copies n bytes from memory area src to memory area dest.
The memory areas must not overlap.  Use memmove(3) if the memory areas do overlap.

NOTE : Reproduce the behaviour of memcpy. Note : it would be safer with a && test... 
*/
{
	size_t			i;
	unsigned char	*dest_temp;
	unsigned char	*src_temp;

	dest_temp = (unsigned char *)dest;
	src_temp = (unsigned char *)src;
	i = 0;
	if (dest_temp || src_temp)
	{
		while (i < n)
		{
			dest_temp[i] = src_temp[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	s1[20];
	char	*s2 = "teSt";

	//memcpy(NULL, s2, 3);
	printf("memcpy works !\n");
	ft_memcpy(NULL, NULL, 3);
	printf("ft_memcpy works !\n");
}
*/