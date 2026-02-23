/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:58:56 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/05/01 18:35:44 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_temp;

	s_temp = (unsigned char *)s;
	while (n)
	{
		if (*s_temp == (unsigned char)c)
			return (s_temp);
		s_temp++;
		n--;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>
int main() {
    long unsigned   x = 5;
    char    *s1 = "abcdefgh";
    printf("%s\n", memchr(s1,'c',x));
    printf("%s\n", ft_memchr(s1,'c',x));

    return 0;
}
*/
