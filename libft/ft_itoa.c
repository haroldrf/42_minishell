/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:58:16 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/05/20 08:50:56 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *s, size_t n);

size_t	ft_strlen(const char *s);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

static void	put_nb_custom_in_string(int n, char *s)
{
	int	divisor;

	if (n < 0)
	{
		*s = '-';
		s++;
	}
	else
		n *= -1;
	divisor = 1;
	while (n / divisor <= -10)
		divisor *= 10;
	while (divisor >= 1)
	{
		*s = '0' - (n / divisor);
		s++;
		n = n % divisor;
		divisor /= 10;
	}
}

char	*ft_itoa(int n)
{
	size_t		len;
	char		temp[50];
	char		*result;

	ft_bzero(temp, 50);
	put_nb_custom_in_string(n, temp);
	len = ft_strlen(temp);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, temp, len + 1);
	return (result);
}
/*
#include <stdio.h>
#include <limits.h>
int main()
{ 
	int nb = INT_MIN;
	char *s;

	s = ft_itoa(nb);
	printf("%s\n", s);
	printf("%p\n", s);
	return (0);
}
*/
