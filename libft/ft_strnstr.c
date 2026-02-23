/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:21:10 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/05/01 18:38:03 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if(!*little)
		return ((char *)big);
	if (len == 0)
		return (NULL);
	i = 0;
	while (big[i] && i != len)
	{
		j = 0;
		while (big[i] && i != len && little[j] && little[j] == big[i])
		{
			i++;
			j++;
		}
		if (little[j] == 0 && i)
			return ((char *)(big + i - j));
		if (j == 0)
			i++;
	}
	return (NULL);
}
*/

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
/*reproduce strnstr
NOTE : dammed segment fault generation for the edgecase NULL haystack ...*/
{
	size_t	i;
	size_t	needle_len;
	int		*dummy;

	if (!*needle)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	dummy = NULL;
	if (!haystack)
		*dummy = 666;
	needle_len = ft_strlen(needle);
	i = 0;
	while (i + needle_len <= len)
	{
		if (haystack[i] == '\0')
			break ;
		if (ft_strncmp(haystack + i, needle, needle_len) == 0)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
int main() 
{
    char    *s1 = "abcbcedebcefgh";
    char    *s2 = "bc";
    //printf("%s\n", strnstr(s1,s2,x));
    printf("%s\n", ft_strnstr(s1,s2,-1));
    printf("%i\n", (ft_strnstr(s1,s2,-1) == s1 +1));
}
*/
