/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:14:32 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/15 10:53:43 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* STRING EXPANSION ($)
- if no $ or token is heredoc dlm or single quote -> we return */

char		*expand_string(char *value, t_shell *shell);
static int	exp_alloc(t_expand **expansion, int max_exp);
static int	fill_up_exp(char *tokvalue, t_shell *sh, t_expand *exp, int dollar);
static char	*apply_expansions(char *tokvalue, t_expand *exp, int n_exp);
static int	find_exp(char *val, t_shell *sh, t_expand **exp, int *cnt);

char	*expand_string(char *value, t_shell *shell)
{
	t_expand	*exp;
	int			n_exp;
	char		*new_value;
	int			max_exp;

	exp = NULL;
	n_exp = 0;
	max_exp = 20;
	if (exp_alloc(&exp, max_exp) || find_exp(value, shell, &exp, &n_exp))
	{
		free_expansion(&exp, n_exp);
		return (NULL);
	}
	if (n_exp == 0)
	{
		free_expansion(&exp, n_exp);
		return (value);
	}
	new_value = apply_expansions(value, exp, n_exp);
	free_expansion(&exp, n_exp);
	if (!new_value)
		return (NULL);
	free(value);
	return (new_value);
}

static int	exp_alloc(t_expand **expansion, int max_exp)
{
	*expansion = malloc(sizeof(t_expand) * max_exp);
	if (!*expansion)
		return (MEMORY_ALLOCATION_ERROR);
	return (NO_ERROR);
}

/* WE FILL UP THE EXPANSION STRUCT (envname + envvalue)*/
static int	find_exp(char *val, t_shell *sh, t_expand **exp, int *cnt)
{
	int		i;
	char	*dollar_pos;
	int		dollar_int;
	int		max_exp;

	max_exp = 10;
	i = 0;
	while (val[i])
	{
		dollar_pos = ft_strchr(val + i, '$');
		if (!dollar_pos)
			return (NO_ERROR);
		dollar_int = dollar_pos - val;
		if (ft_is_valid_exp(val, dollar_int + 1, 1))
		{
			if (*cnt == (max_exp - 1) && inc_exp_capacity(exp, &max_exp) != 0)
				return (MEMORY_ALLOCATION_ERROR);
			if (fill_up_exp(val, sh, &(*exp)[*cnt], dollar_int) != NO_ERROR)
				return (MEMORY_ALLOCATION_ERROR);
			i = (*exp)[*cnt].end;
			(*cnt)++;
		}
		i = dollar_int + 1;
	}
	return (NO_ERROR);
}

static int	fill_up_exp(char *tokvalue, t_shell *sh, t_expand *exp, int dollar)
{
	exp->start = dollar;
	exp->envar_name = get_env_name(tokvalue, dollar);
	if (!exp->envar_name)
		return (MEMORY_ALLOCATION_ERROR);
	exp->end = dollar + ft_strlen(exp->envar_name) + 1;
	exp->env_val = get_env_value(exp->envar_name, sh);
	if (!exp->env_val)
	{
		free(exp->envar_name);
		return (MEMORY_ALLOCATION_ERROR);
	}
	return (NO_ERROR);
}

static char	*apply_expansions(char *tokvalue, t_expand *exp, int n_exp)
{
	int		j;
	char	*new;
	int		current;

	new = alloc_newvalue(tokvalue, exp, n_exp);
	if (!new)
		return (NULL);
	ft_memcpy(new, tokvalue, exp[0].start);
	current = exp[0].start;
	j = 0;
	while (j < n_exp)
	{
		ft_memcpy(new + current, exp[j].env_val, ft_strlen(exp[j].env_val));
		current += ft_strlen(exp[j].env_val);
		if (j < n_exp - 1)
		{
			ft_memcpy(new + current, tokvalue + exp[j].end, 
				exp[j + 1].start - exp[j].end);
			current += exp[j + 1].start - exp[j].end;
		}
		j++;
	}
	ft_strlcpy(new + current, tokvalue + exp[n_exp - 1].end, 
		ft_strlen(tokvalue + exp[n_exp - 1].end) + 1);
	return (new);
}
