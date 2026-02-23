/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 08:34:02 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/10/16 10:39:35 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libft.h"

void	put_nb_custom(unsigned long long nb, int precision, char *base)
{
	char				base_size;
	unsigned long long	divisor;

	base_size = ft_strlen(base);
	divisor = 1;
	while (precision-- > 1)
		divisor *= base_size;
	while (divisor >= 1)
	{
		write(2, base + nb / divisor, 1);
		nb = nb % divisor;
		divisor /= base_size;
	}
}

char	nb_digits(unsigned long long nb, char *base)
{
	char				nb_dig;
	unsigned long long	divisor;

	nb_dig = 1;
	divisor = 1;
	while (nb / divisor >= ft_strlen(base))
	{
		nb_dig++;
		divisor *= ft_strlen(base);
	}
	return (nb_dig);
}
