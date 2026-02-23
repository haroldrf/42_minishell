/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 07:44:14 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/10/10 15:09:00 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	remove_var_from_env(char **new_env, char **env, char *arg);

int	ft_unset(char **argv, char ***env)
{
	char	**new_env;

	while (*argv)
	{
		if (does_variable_exist(*argv, *env))
		{
			new_env = malloc(sizeof(char **) * get_array_size(*env));
			if (!new_env)
				memory_failure();
			remove_var_from_env(new_env, *env, *argv);
			free(*env);
			*env = new_env;
		}
		argv++;
	}
	return (0);
}

static void	remove_var_from_env(char **new_env, char **env, char *arg)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	j = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (!split)
			memory_failure();
		if (ft_strcmp(split[0], arg))
			new_env[j++] = env[i++];
		else
			free(env[i++]);
		free_array(split);
	}
	new_env[j] = NULL;
}
