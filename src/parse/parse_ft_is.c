/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ft_is.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 22:33:12 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/10 13:59:59 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	ft_isspace(char c);
bool	ft_isops(char c);
bool	ft_isquotes(char c);
bool	ft_is_comb(t_token *token);
bool	ft_is_valid_exp(char *value, int i, bool start);

// space, form-feed ('\f'), newline ('\n'), carriage return ('\r'), horizontal
// tab ('\t'),  and vertical tab ('\v').
bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || (c == 32));
}

bool	ft_isops(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

bool	ft_isquotes(char c)
{
	return (c == '"' || c == '\'');
}

bool	ft_is_comb(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == TOKEN_DOUBLE_Q || token->type == TOKEN_SINGLE_Q
		|| token->type == TOKEN_WORD)
		return (true);
	return (false);
}

bool	ft_is_valid_exp(char *value, int i, bool start)
{
	if (start == true)
		return (ft_isalpha(value[i]) || value[i] == '_' || value[i] == '?'); 
	else
		return (ft_isalnum(value[i]) || value[i] == '_'); 
}
