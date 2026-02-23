/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:20:41 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/10/07 13:45:11 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
/* reproduce the behaviour of strncmp
NOTE : the casting to unsigned char is only neceassry to comply on edgecases 
with the original behaviour... */
{
	while (n && *s1 && *s2)
	{
		if (*s1 != *s2)
			return ((int)((unsigned char)(*s1) - (unsigned char)(*s2)));
		s1++;
		s2++;
		n--;
	}
	if (n)
		return ((int)((unsigned char)(*s1) - (unsigned char)(*s2)));
	else
		return (0);
}
