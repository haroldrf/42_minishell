/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retoken_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:27:15 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/15 10:45:06 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		count_elts(char *s);
void	free_split(char **split, int i);
int		assign_values(t_retoken *tok_d, int k);

int	count_elts(char *s)
{
	int		count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] != ' ' && s[i])
			count++;
		while (s[i] != ' ' && s[i])
			i++;
	}
	return (count);
}

int	assign_values(t_retoken *tok_d, int k)
{
	tok_d->new_tok[*tok_d->j]->value = ft_strdup(tok_d->split[k]);
	if (!tok_d->new_tok[*tok_d->j]->value)
		return (MEMORY_ALLOCATION_ERROR);
	tok_d->new_tok[*tok_d->j]->length 
		= ft_strlen(tok_d->new_tok[*tok_d->j]->value);
	tok_d->new_tok[*tok_d->j]->type = tok_d->old_tok->type;
	if (k == 0)
		tok_d->new_tok[*tok_d->j]->start = tok_d->old_tok->start;
	else 
		tok_d->new_tok[*tok_d->j]->start 
			= tok_d->new_tok[*tok_d->j - 1]->end + 1;
	tok_d->new_tok[*tok_d->j]->end = tok_d->new_tok[*tok_d->j]->start 
		+ tok_d->new_tok[*tok_d->j]->length;
	tok_d->new_tok[*tok_d->j]->expandable = false;
	tok_d->new_tok[*tok_d->j]->comb_prev = false;
	tok_d->new_tok[*tok_d->j]->retoken = false;
	return (NO_ERROR);
}

void	free_split(char **split, int i)
{
	while (i > 0)
		free(split[--i]);
	free(split);
}
