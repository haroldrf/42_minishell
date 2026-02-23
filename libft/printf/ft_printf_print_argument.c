/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_argument.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:53:55 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/10/16 10:40:01 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "../libft.h"

static int	print_nb(unsigned long long nb, char *pre, t_format f, char *base)
{
	char	pre_len;
	char	nb_dig;

	pre_len = (char)ft_strlen(pre);
	nb_dig = max(nb_digits(nb, base), f.dot);
	if (f.minus)
	{
		write(2, pre, pre_len);
		put_nb_custom(nb, nb_dig, base);
		print_space(f.width - pre_len - nb_dig);
	}
	else
	{
		if (f.zero && f.dot == -1)
			nb_dig = max(nb_dig, f.width - pre_len);
		print_space(f.width - pre_len - nb_dig);
		write(2, pre, pre_len);
		put_nb_custom(nb, nb_dig, base);
	}
	return (max(f.width, nb_dig + pre_len));
}

static int	print_string(char *s, t_format f)
{
	if (f.type == 'c' || f.type == '%')
		f.dot = 1;
	else if (f.dot == -1)
		f.dot = ft_strlen(s);
	else
		f.dot = min(ft_strlen(s), f.dot);
	if (f.minus)
	{
		write(2, s, (size_t)f.dot);
		print_space(f.width - f.dot);
	}
	else
	{
		print_space(f.width - f.dot);
		write(2, s, (size_t)f.dot);
	}
	return (max(f.width, f.dot));
}

int	print_idu(va_list *args, t_format f)
{
	unsigned long long	nb;
	int					temp;
	char				*prefix;

	prefix = "\0";
	if (f.type == 'i' || f.type == 'd')
	{
		temp = va_arg(*args, int);
		if (temp < 0)
			prefix = "-";
		nb = (unsigned long long)(temp * (long)sign(temp));
	}
	else
		nb = (unsigned long long)va_arg(*args, unsigned);
	if (*prefix != '-')
	{
		if (f.plus)
			prefix = "+";
		else if (f.space)
			prefix = " ";
	}
	return (print_nb(nb, prefix, f, "0123456789"));
}

int	print_pxx(va_list *args, t_format f)
{
	unsigned long long	nb;
	char				*prefix;

	prefix = "\0";
	if (f.type == 'p')
		nb = (unsigned long long)va_arg(*args, void *);
	else
		nb = (unsigned long long)va_arg(*args, unsigned int);
	if ((f.type == 'p') && nb == 0)
	{
		f.dot = -1;
		return (print_string("(nil)", f));
	}
	if (f.type == 'p' || (f.type == 'x' && f.dash && nb))
		prefix = "0x";
	if (f.type == 'X' && f.dash && nb)
		prefix = "0X";
	if (f.type == 'p' || f.type == 'x')
		return (print_nb(nb, prefix, f, "0123456789abcdef"));
	return (print_nb(nb, prefix, f, "0123456789ABCDEF"));
}

int	print_cs(va_list *args, t_format f)
{
	char	s_one[1];
	char	*s;

	if (f.type == 'c')
		*s_one = va_arg(*args, int);
	if (f.type == '%')
		*s_one = '%';
	s = s_one;
	if (f.type == 's')
	{
		s = va_arg(*args, char *);
		if (s == NULL && f.dot == -1)
			s = "(null)";
	}
	return (print_string(s, f));
}
