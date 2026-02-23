/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:59:59 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/05/01 18:35:50 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_temp;
	unsigned char	*s2_temp;

	s1_temp = (unsigned char *)s1;
	s2_temp = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n > 1)
	{
		if (*s1_temp != *s2_temp)
			return ((int)(*s1_temp - *s2_temp));
		s1_temp++;
		s2_temp++;
		n--;
	}
	return ((int)(*s1_temp - *s2_temp));
}
/*
#include <stdio.h>
#include <string.h>
int main() {
    long unsigned   x = 3;
    char    *s1 = "aba";
    char    *s2 = "abc";
    printf("%i\n", memcmp(s1,s2,x));
    printf("%i\n", ft_memcmp(s1,s2,x));

    x = 4;
    int    x1 = 1000;
    int    x2 = 1010;
    printf("%i\n", memcmp(&x1,&x2,x));
    printf("%i\n", ft_memcmp(&x1,&x2,x));

    return 0;
}
*/
