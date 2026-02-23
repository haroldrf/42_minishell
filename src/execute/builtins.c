/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:17:23 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/10/15 13:16:56 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(t_xnode *node)
{
	if (!node->argv[0])
		return (1);
	if (!ft_strcmp(node->argv[0], "cd"))
		return (1);
	if (!ft_strcmp(node->argv[0], "exit"))
		return (1);
	if (!ft_strcmp(node->argv[0], "echo"))
		return (1);
	if (!ft_strcmp(node->argv[0], "env"))
		return (1);
	if (!ft_strcmp(node->argv[0], "export"))
		return (1);
	if (!ft_strcmp(node->argv[0], "pwd"))
		return (1);
	if (!ft_strcmp(node->argv[0], "unset"))
		return (1);
	return (0);
}

int	exec_builtin(t_xnode *node, t_shell *ms)
{
	if (!node->argv[0])
		return (0);
	if (!ft_strcmp(node->argv[0], "cd"))
		return (ft_cd(node->argv + 1, &ms->env));
	if (!ft_strcmp(node->argv[0], "exit"))
		return (ft_exit(ms, node));
	if (!ft_strcmp(node->argv[0], "echo"))
		return (ft_echo(node->argv + 1));
	if (!ft_strcmp(node->argv[0], "env"))
		return (ft_env(ms->env));
	if (!ft_strcmp(node->argv[0], "export"))
		return (ft_export(node->argv + 1, &ms->env));
	if (!ft_strcmp(node->argv[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(node->argv[0], "unset"))
		return (ft_unset(node->argv + 1, &ms->env));
	return (0);
}
