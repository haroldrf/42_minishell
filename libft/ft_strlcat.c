/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:37:31 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/05/01 18:41:49 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *s);

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
/*	https://linux.die.net/man/3/strlcpy  
	REWRITE THIS MESS .... 
*/
{
	size_t	len_src;
	size_t	len_dst;
	size_t	i;

	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (dstsize > len_dst)
	{
		dst += len_dst;
		i = 0;
		while (src[i] && i < dstsize - len_dst - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
		return (len_src + len_dst);
	}
	return (dstsize + len_src);
}
