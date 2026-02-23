/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:39:08 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/13 17:01:37 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_name(char *value, int dollar_int);
char	*get_env_value(char *env_val, t_shell *shell);
char	*alloc_newvalue(char *value, t_expand *expansion, int n_exp);
void	free_expansion(t_expand **expansion, int n_exp);
int		inc_exp_capacity(t_expand **exp, int *max_exp);

char	*get_env_name(char *value, int dollar_int)
{
	int		len;
	char	*envar_name;

	dollar_int++;
	if (value[dollar_int] == '?')
		len = 1;
	else 
	{
		len = 0;
		while (value[dollar_int + len] 
			&& ft_is_valid_exp(value, dollar_int + len, false))
			len++;
	}
	envar_name = malloc(sizeof(char) * (len + 1));
	if (!envar_name)
		return (NULL);
	ft_strlcpy(envar_name, value + dollar_int, len + 1);
	return (envar_name);
}

char	*get_env_value(char *envar_name, t_shell *shell)
{
	int		i;
	char	*env_val;
	int		envarnamelen;

	i = 0;
	if (envar_name && ft_strcmp(envar_name, "?") == 0)
		return (ft_itoa(shell->last_exit_code));
	envarnamelen = ft_strlen(envar_name);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], envar_name, envarnamelen) == 0 
			&& shell->env[i][envarnamelen] == '=')
		{
			env_val = ft_strdup(shell->env[i] + envarnamelen + 1);
			if (!env_val)
				return (NULL);
			return (env_val);
		}
		i++;
	}
	return (ft_strdup(""));
}

char	*alloc_newvalue(char *value, t_expand *exp, int n_exp)
{
	int		length;
	char	*new_value;
	int		j;

	length = exp[0].start + ft_strlen(exp[0].env_val);
	j = 1;
	while (j < n_exp)
	{
		length += exp[j].start - exp[j - 1].end + ft_strlen(exp[j].env_val);
		j++;
	}
	length += ft_strlen(value + exp[n_exp - 1].end);
	new_value = malloc(sizeof(char) * (length + 1));
	if (!new_value)
		return (NULL);
	return (new_value);
}

void	free_expansion(t_expand **expansion, int n_exp)
{
	int	i;

	i = 0;
	if (expansion && *expansion)
	{
		while (i < n_exp)
		{
			if ((*expansion)[i].envar_name)
			{
				free((*expansion)[i].envar_name);
				(*expansion)[i].envar_name = NULL;
			}
			if ((*expansion)[i].env_val)
			{
				free((*expansion)[i].env_val);
				(*expansion)[i].env_val = NULL;
			}
			i++;
		}
		free((*expansion));
		*expansion = NULL;
	}
}

int	inc_exp_capacity(t_expand **exp, int *max_exp)
{
	t_expand	*new_exp;
	int			new_max;
	int			i;

	new_max = *max_exp * 2;
	new_exp = malloc(sizeof(t_expand) * new_max);
	if (!new_exp)
		return (MEMORY_ALLOCATION_ERROR);
	i = 0;
	while (i < *max_exp)
	{
		new_exp[i] = (*exp)[i];
		i++;
	}
	free(*exp);
	*exp = new_exp;
	*max_exp = new_max;
	return (NO_ERROR);
}
