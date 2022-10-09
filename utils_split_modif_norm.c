/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split_modif_norm.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmerope <cmerope@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:44:21 by cmerope           #+#    #+#             */
/*   Updated: 2022/02/10 20:12:47 by cmerope          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_next_step(int i, char const *s)
{
	if (s[i] == '"')
	{
		i++;
		while (s[i] && (s[i] != '"'))
			i++;
	}
	if (s[i] == '\'')
	{
		i++;
		while (s[i] && (s[i] != '\''))
			i++;
	}
	return (i);
}

int	ft_skip_quote(int i, unsigned int *next_str_len, char **next_str)
{
	if ((*next_str)[i] == '"' || (*next_str)[i] == '\'')
	{
		(*next_str_len)++;
		i++;
		if ((*next_str)[i - 1] == '"')
		{
			while ((*next_str)[i] && ((*next_str)[i] != '"' ))
			{
				(*next_str_len)++;
				i++;
			}
		}
		else if ((*next_str)[i - 1] == '\'')
		{
			while ((*next_str)[i] && ((*next_str)[i] != '\'' ))
			{
				(*next_str_len)++;
				i++;
			}
		}
	}
	return (i);
}
