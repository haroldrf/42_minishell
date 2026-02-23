/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:29:49 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/10/16 10:39:02 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "../libft.h"

int		print_idu(va_list *args, t_format f);
int		print_pxx(va_list *args, t_format f);
int		print_cs(va_list *args, t_format f);

static int	print_rest(const char **s)
{
	int	len;

	len = 0;
	while ((*s)[len] != '%' && (*s)[len] != '\0')
		len++;
	write(2, *s, len);
	*s = (char *)(*s + len);
	return (len);
}

static int	get_nb(char **s)
{
	int	n;

	n = 0;
	while (ft_isdigit(**s))
	{
		n = n * 10 + **s - '0';
		(*s)++;
	}
	return (n);
}

static void	initialise_format(t_format *result)
{
	result->type = 0;
	result->width = 0;
	result->zero = 0;
	result->minus = 0;
	result->dot = -1;
	result->dash = 0;
	result->space = 0;
	result->plus = 0;
}

static char	*retrieve_format(t_format *result, char *s)
{
	initialise_format(result);
	s++;
	while (!is_in_set(*s, "cspdiuxX%"))
	{
		if (is_in_set(*s, "123456789"))
			result->width = get_nb(&s);
		else
		{
			if (*s == '0')
				result->zero = 1;
			if (*s == '-')
				result->minus = 1;
			if (*s == ' ')
				result->space = 1;
			if (*s == '#')
				result->dash = 1;
			if (*s == '+')
				result->plus = 1;
			s++;
			if (*(s - 1) == '.')
				result->dot = get_nb(&s);
		}
	}
	result->type = *s;
	return (s + 1);
}

int	ft_printf(const char *string, ...)
{
	va_list		args;
	t_format	f;
	int			result;

	va_start(args, string);
	result = print_rest(&string);
	while (*string == '%')
	{
		string = retrieve_format(&f, (char *)string);
		if (f.type == 'i' || f.type == 'd' || f.type == 'u')
			result += print_idu(&args, f);
		if (f.type == 'p' || f.type == 'x' || f.type == 'X')
			result += print_pxx(&args, f);
		if (f.type == 'c' || f.type == 's' || f.type == '%')
			result += print_cs(&args, f);
		result += print_rest(&string);
	}
	return (result);
}
