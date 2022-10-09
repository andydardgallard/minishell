/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:02:28 by cmerope           #+#    #+#             */
/*   Updated: 2022/02/11 01:28:43 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_dollar(t_tokens *t, int str, int pos)
{
	int		start;
	char	*tmp2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp2 = NULL;
	start = pos;
	pos++;
	if (t->flag_q != 0 || t->ep_lst[str][pos] == '#')
		return (ft_flag_q(t, start, str, pos));
	else if (t->ep_lst[str][pos] == '_' || ft_isalpha(t->ep_lst[str][pos]) == 1)
	{
		while (ft_chek_simb(t->ep_lst[str][pos]) == 1)
		{
			pos++;
			i++;
		}
		tmp2 = ft_substr(t->ep_lst[str], start + 1, i);
		j = ft_chek_flag(t, tmp2);
		if (t->flag_q == 2)
			return (ft_full_ep(t, j, str, start));
	}
	return (ft_q_all(t, str, start, pos));
}

int	ft_quote(t_tokens *tokens, int str, int pos)
{
	int	start;

	start = pos;
	pos++;
	while (tokens->ep_lst[str][pos] != '\0')
	{
		if (tokens->ep_lst[str][pos] == '$'
			&& tokens->ep_lst[str][pos + 1] == '?' && str == 0)
			printf("minishell: $?: command not found\n");
		if (tokens->ep_lst[str][pos] == '\'')
			break ;
		pos++;
	}
	pos = ft_new_ep_lst(tokens, str, pos, start);
	return (pos);
}

int	ft_back_slesh(t_tokens *tokens, int str, int pos)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(tokens->ep_lst[str], 0, pos);
	tmp2 = ft_strdup(tokens->ep_lst[str] + pos + 1);
	tokens->ep_lst[str] = ft_strdup(tmp);
	tokens->ep_lst[str] = ft_strjoin(tokens->ep_lst[str], tmp2);
	free (tmp);
	free (tmp2);
	return (pos);
}

int	ft_double_quote(t_tokens *tokens, int str, int pos)
{
	int	start;

	start = pos;
	pos++;
	while (tokens->ep_lst[str][pos] != '\0')
	{
		if (ft_simb_pos(tokens, str, pos) == 1)
		{
			ft_back_slesh(tokens, str, pos);
			pos++;
		}
		else if (tokens->ep_lst[str][pos] == '$')
		{
			if (tokens->ep_lst[str][pos + 1] == '?')
				tokens->flag_q = 2;
			pos = ft_dollar(tokens, str, pos);
		}
		else if (tokens->ep_lst[str][pos] == '"')
			break ;
		pos++;
	}
	pos = ft_new_ep_lst(tokens, str, pos, start);
	return (pos);
}

void	ft_parser(t_tokens *tokens)
{
	int	i;
	int	j;

	i = -1;
	while (tokens->ep_lst[++i] != NULL)
	{
		j = -1;
		while (tokens->ep_lst[i][++j] != '\0')
		{
			tokens->flag_q = 0;
			if (tokens->ep_lst[i][j] == '"')
				j = ft_double_quote (tokens, i, j);
			else if (tokens->ep_lst[i][j] == '\'')
				j = ft_quote (tokens, i, j);
			else if (tokens->ep_lst[i][j] == '\\')
				j = ft_back_slesh (tokens, i, j);
			else if (tokens->ep_lst[i][j] == '$')
			{
				if (tokens->ep_lst[i][j + 1] == '?')
					tokens->flag_q = 1;
				j = ft_dollar (tokens, i, j);
			}
		}
	}
}
