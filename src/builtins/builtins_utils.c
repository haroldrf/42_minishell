/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:03:25 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/10/16 10:44:47 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_var_name(char *arg)
{
	char	**split;
	char	*res;
	int		i;

	split = ft_split(arg, '=');
	if (!split)
		memory_failure();
	res = split[0];
	i = 0;
	if (res)
	{
		while (split[++i])
			free(split[i]);
	}
	free(split);
	return (res);
}

void	memory_failure(void)
{
	ft_printf("Memory allocation failure. Exiting minishell.\n");
	exit(1);
}

int	get_array_size(char **arr)
/* returns the size of an char 2d array
the NULL finishing pointer is not included..*/
{
	int	i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

int	does_variable_exist(char *arg, char **env)
{
	char	**split;
	int		res;

	res = 0;
	while (*env)
	{
		split = ft_split(*env, '=');
		if (!split)
			memory_failure();
		if (!ft_strcmp(split[0], arg))
			res = 1;
		free_array(split);
		env++;
	}
	return (res);
}
