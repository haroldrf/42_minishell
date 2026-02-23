/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:04:25 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/08/12 17:54:04 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_temp;
	unsigned char	c_temp;

	s_temp = s;
	c_temp = c;
	while (n-- > 0)
		s_temp[n] = c_temp;
	return (s);
}
