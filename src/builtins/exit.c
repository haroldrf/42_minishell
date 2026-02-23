/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 07:44:14 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/10/16 12:46:28 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_numerical(char *str);

int	ft_exit(t_shell *ms, t_xnode *node)
{
	int	exit_code;

	if (get_array_size(node->argv) > 2)
	{
		ft_printf("Error: exit : too many arguments\n");
		return (1);
	}
	if (!node->argv[1])
		exit_code = ms->last_exit_code;
	else if (!is_numerical(node->argv[1]))
	{
		ft_printf("Error: exit: %s: numeric argument required\n", node->argv[1]);
		exit_code = 2;
	}
	else
		exit_code = ft_atoi(node->argv[1]);
	exit_code %= 256;
	cleanup_shell(ms);
	printf("Exit\n");
	exit(exit_code);
}

static int	is_numerical(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
