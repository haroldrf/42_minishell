/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:45:17 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/05/17 11:00:31 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(const char c)
/* 
checks for white-space characters.   In  the  "C"  and "POSIX"  locales, 
these are: space, form-feed ('\f'),newline ('\n'), carriage return ('\r'), horizontal tab
('\t'), and vertical tab ('\v').
*/
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	ft_isdigit(unsigned char c);

int	ft_atoi(const char *s)
{
	int	sign;
	int	n;

	sign = 1;
	n = 0;
	while (ft_isspace(*s))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	while (ft_isdigit(*s))
	{
		n = n * 10 + *s - '0';
		s++;
	}
	return (n * sign);
}

/*
#include <stdio.h>
#include <stdlib.h>
int	main(void)
{
	char	s[] = " \n -+123456d ";

	printf("%i\n", atoi(s));
	printf("%i\n", ft_atoi(s));
}
*/
