/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:19:43 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/05/01 18:37:51 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*a;
	size_t	i;

	a = malloc(ft_strlen(s) + 1);
	if (a == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		a[i] = f(i, s[i]);
		i++;
	}
	a[i] = 0;
	return (a);
}

/*
static char	ceasar(unsigned int a, char c)
{
	if (c >= '0' && c <= '9')
		return ((c + a - '0') % 10 + '0');
	if (c >= 'a' && c <= 'z')
		return ((c + a - 'a') % 26 + 'a');
	if (c >= 'A' && c <= 'Z')
		return ((c + a - 'A') % 26 + 'A');
	return (c);
}

#include <stdio.h>
int	main(void)
{
	char *s;

	s = 	"Rnpu cebwrpg bs gur 97 Pbzzba Pber pbagnvaf na rapbqrq uvag. Sbe "
			"rnpu pvepyr, bayl bar cebwrpg cebivqrf gur pbeerpg uvag arrqrq sbe "
			"gur arkg pvepyr. Guvf punyyratr vf vaqvivqhny, gurer vf bayl n "
			"cevmr sbe bar fghqrag jvaare cebivqvat nyy qrpbqrq zrffntrf. Nal "
			"nqinagntrq crbcyr pna cynl, yvxr pheerag be sbezre fgnss, ohg gur "
			"cevmr jvyy erznva flzobyvp. Gur uvag sbe guvf svefg cebwrpg vf: "
			"Ynetr pbjf trarebfvgl pbzrf jvgu punegf naq sbhe oybaqr ungf "
			"gb qrsl hccre tenivgl ureb";
	
	printf("%s", ft_strmapi(s, ceasar));
}
*/
