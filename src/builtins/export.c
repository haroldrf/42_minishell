/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 07:44:14 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/10/16 10:46:48 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_arguments(char **arg, char **env, int *exit);
static void	fill_new_env(char **new_env, char **env, char **arg, int nb_arg);
static int	is_valid_env_identifier(char *str);
static void	replace_existing_variable(char *arg, char *var_name, char **env);

int	ft_export(char **arg, char ***env)
{
	int		nb_arg;
	char	**new_env;
	int		env_size;
	int		exit;

	if (*arg == NULL)
	{
		ft_printf("Error: export: without argument is not supported\n");
		return (1);
	}
	nb_arg = check_arguments(arg, *env, &exit);
	env_size = get_array_size(*env);
	if (nb_arg)
	{
		new_env = malloc(sizeof(char *) * (env_size + nb_arg + 1));
		if (!new_env)
			memory_failure();
		fill_new_env(new_env, *env, arg, nb_arg);
		free(*env);
		*env = new_env;
	}
	return (exit);
}

static int	check_arguments(char **arg, char **env, int *exit)
/* also replace the already existing variables*/
{
	int		nb_arg;
	char	*var_name;

	*exit = 0;
	nb_arg = get_array_size(arg);
	while (*arg)
	{
		var_name = get_var_name(*arg);
		if (!is_valid_env_identifier(var_name))
		{
			nb_arg--;
			ft_printf("Error: export: %s: not a valid identifier\n", *arg);
			*exit = 1;
		}
		else if (ft_strchr(*arg, '=') == NULL)
			nb_arg--;
		else if (does_variable_exist(var_name, env))
		{
			replace_existing_variable(*arg, var_name, env);
			nb_arg--;
		}
		free(var_name);
		arg++;
	}
	return (nb_arg);
}

static void	fill_new_env(char **new_env, char **env, char **arg, int nb_arg)
{
	int		i;
	int		j;
	int		env_size;
	char	*var_name;

	i = -1;
	while (env[++i])
		new_env[i] = env[i];
	env_size = i;
	j = 0;
	while (i < env_size + nb_arg)
	{
		var_name = get_var_name(arg[j]);
		if (is_valid_env_identifier(var_name)
			&& !does_variable_exist(var_name, env) && ft_strchr(arg[j], '='))
		{
			new_env[i] = ft_strdup(arg[j]);
			if (!new_env[i])
				memory_failure();
			i++;
		}
		free(var_name);
		j++;
	}
	new_env[i] = NULL;
}

static int	is_valid_env_identifier(char *var_name)
{
	int		i;

	if (!var_name)
		return (0);
	i = 0;
	if (!(ft_isalpha(var_name[i]) || var_name[i] == '_'))
		return (0);
	while (var_name[++i])
	{
		if (!(ft_isalnum(var_name[i]) || var_name[i] == '_'))
			return (0);
	}
	return (1);
}

static void	replace_existing_variable(char *arg, char *var_name, char **env)
{
	char	**split;

	while (*env)
	{
		split = ft_split(*env, '=');
		if (!split)
			memory_failure();
		if (!ft_strcmp(split[0], var_name))
		{
			free(*env);
			*env = ft_strdup(arg);
			if (!*env)
				memory_failure();
			free_array(split);
			return ;
		}
		free_array(split);
		env++;
	}
}
