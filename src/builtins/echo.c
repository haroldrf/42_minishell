/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 07:44:14 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/10/10 15:08:35 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_echo(char **arg)
{
	char	n_opt;

	n_opt = 0;
	if (*arg && !ft_strcmp(*arg, "-n"))
	{
		n_opt = 1;
		arg++;
	}
	while (*arg)
	{
		printf("%s", *arg);
		arg++;
		if (*arg)
			printf("%c", ' ');
	}
	if (!n_opt)
		printf("\n");
	return (0);
}
