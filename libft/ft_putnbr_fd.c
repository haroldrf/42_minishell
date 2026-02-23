/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:05:41 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/05/01 18:36:44 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	int		divisor;
	char	q;

	if (n < 0)
		write(fd, "-", 1);
	else
		n *= -1;
	divisor = 1;
	while (n / divisor <= -10)
		divisor *= 10;
	while (divisor >= 1)
	{
		q = '0' - (n / divisor);
		write(fd, &q, 1);
		n = n % divisor;
		divisor /= 10;
	}
}
/*
#include <limits.h>
int	main(void)
{
	ft_putchar_fd('z', 1);
	ft_putstr_fd("-> is a test : ", 1);
	ft_putendl_fd("with end of line!", 1);
	ft_putnbr_fd(0, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(INT_MIN, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(INT_MAX, 1);
	write(1, "\n", 1);
}
*/
