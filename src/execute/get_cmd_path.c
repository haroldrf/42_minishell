/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:17:44 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/10/11 13:20:07 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// protect if no PATH ?!...
char	*get_cmd_path(t_xnode *node)
{
	char	*cmd_path;
	char	*tmp;
	char	**path_table;
	int		i;

	if (node->argv[0][0] == '.' || node->argv[0][0] == '/')
		return (node->argv[0]);
	path_table = ft_split(getenv("PATH"), ':');
	i = -1;
	while (path_table[++i])
	{
		tmp = ft_strjoin(path_table[i], "/");
		cmd_path = ft_strjoin(tmp, node->argv[0]);
		free(tmp);
		if (!access(cmd_path, F_OK))
		{
			free_array(path_table);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free_array(path_table);
	return (NULL);
}
