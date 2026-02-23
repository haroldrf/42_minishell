/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:24:09 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/05/01 18:38:32 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s);

static void	ft_strncpy(char const *src, char *dst, size_t n)
{
	while (n && *src)
	{
		*dst = *src;
		dst++;
		src++;
		n--;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
/*
Note : if the len is too big, it will stops at the end of s but 
allocated will be a too big array... ==> SHOULD BE FIXED NOW...
*/
{
	char	*new_str;
	size_t	newlen;

	if (start > ft_strlen(s))
		return (ft_substr("", 0, 0));
	newlen = ft_strlen(s) - start;
	if (newlen < len)
		len = newlen;
	new_str = malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strncpy(s + start, new_str, len);
	new_str[len] = 0;
	return (new_str);
}
