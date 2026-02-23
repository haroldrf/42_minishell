/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:22:09 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/05/01 18:38:25 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s);

static int	is_in_set(char const c, char const *s)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

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

char	*ft_strtrim(char const *s, char const *set)
{
	char const	*s_backward;
	char		*array;
	size_t		new_len;

	s_backward = s + ft_strlen(s) - 1;
	while (is_in_set(*s, set))
		s++;
	while (is_in_set(*s_backward, set) && s_backward > s)
		s_backward--;
	new_len = s_backward - s + 1;
	array = malloc(new_len + 1);
	if (!array)
		return (NULL);
	ft_strncpy(s, array, new_len);
	array[new_len] = 0;
	return (array);
}
/*
#include <stdio.h>
int	main(void)
{
	char	s[] = "  # 6TeSt that thing##########";
	//char	s[] = "6666   ###";
	char	*array = ft_strtrim(s, "6# ");

	printf("old string : %s\n", s);
	printf("new string : %s\n", array);
}
*/
