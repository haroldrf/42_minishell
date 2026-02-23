/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_clean2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:30:05 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/14 21:19:40 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cleanup_cmd_tree(t_xnode **node);
void	cleanup_node(t_xnode *node);
void	free_redir(t_redir *redir);

void	cleanup_cmd_tree(t_xnode **node)
{
	t_xnode	*current;
	t_xnode	*next;

	if (!node || !*node)
		return ;
	current = *node;
	while (current)
	{
		next = current->next;
		cleanup_node(current);
		current = next;
	}
	*node = NULL;
}

void	cleanup_node(t_xnode *node)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (node)
	{
		if (node->argv)
		{
			while (node->argv[i])
				free(node->argv[i++]);
			free(node->argv);
		}
		if (node->redir)
		{
			while (node->redir[j])
				free_redir(node->redir[j++]);
			free(node->redir);
		}
		free(node);
	}
}

void	free_redir(t_redir *redir)
{
	if (redir)
	{
		if (redir->file)
			free(redir->file);
		if (redir->heredoc_dlm)
			free(redir->heredoc_dlm);
		free(redir);
	}
}
