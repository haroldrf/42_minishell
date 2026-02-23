/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 07:44:14 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/10/16 10:45:24 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	set_pwd(char ***env);
static void	set_old_pwd(char ***env, char *old_pwd);

int	ft_cd(char **arg, char ***env)
{
	int		exit;
	char	old_pwd[1024];

	if (get_array_size(arg) != 1)
	{
		ft_printf("Error: cd takes one (and only one) argument\n");
		return (1);
	}
	getcwd(old_pwd, 1024);
	exit = chdir(arg[0]);
	if (!exit)
	{
		set_pwd(env);
		set_old_pwd(env, old_pwd);
		return (0);
	}
	else
	{
		ft_printf("Error: cd: %s not found\n", arg[0]);
		return (1);
	}
}

static void	set_pwd(char ***env)
{
	char	*arg[2];
	char	pwd[1024];

	getcwd(pwd, 1024);
	arg[0] = ft_strjoin("PWD=", pwd);
	if (!arg[0])
		memory_failure();
	arg[1] = NULL;
	ft_export(arg, env);
	free(arg[0]);
}

static void	set_old_pwd(char ***env, char *old_pwd)
{
	char	*arg[2];

	arg[0] = ft_strjoin("OLDPWD=", old_pwd);
	if (!arg[0])
		memory_failure();
	arg[1] = NULL;
	ft_export(arg, env);
	free(arg[0]);
}
