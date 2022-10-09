/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmerope <cmerope@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:02:28 by cmerope           #+#    #+#             */
/*   Updated: 2022/02/11 01:04:59 by cmerope          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_full_ep(t_tokens *tokens, int j, int str, int start)
{
	int		i;
	int		pos;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	pos = 0;
	tmp = NULL;
	tmp2 = NULL;
	i = 0;
	tmp = ft_substr(tokens->ep_lst[str], 0, start);
	while (tokens->envp_list[j][i] != '=')
		i++;
	tmp2 = ft_substr(tokens->envp_list[j], i + 1,
			ft_strlen(tokens->envp_list[j]) - i);
	tmp3 = ft_substr(tokens->ep_lst[str], start + i + 1,
			ft_strlen(tokens->ep_lst[str]) - start - i);
	pos = start + ft_strlen(tmp2) - 1;
	tokens->ep_lst[str] = ft_strdup(tmp);
	tokens->ep_lst[str] = ft_strjoin(tokens->ep_lst[str], tmp2);
	tokens->ep_lst[str] = ft_strjoin(tokens->ep_lst[str], tmp3);
	free (tmp);
	free (tmp2);
	free (tmp3);
	return (pos);
}

int	ft_q_all(t_tokens *tokens, int str, int start, int pos)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 1;
	tmp = NULL;
	tmp2 = NULL;
	tmp = ft_substr(tokens->ep_lst[str], 0, start);
	tmp2 = ft_substr(tokens->ep_lst[str], start,
			ft_strlen(tokens->ep_lst[str]) - start);
	tokens->ep_lst[str] = ft_strdup(tmp);
	pos = start;
	free (tmp);
	free (tmp2);
	return (pos);
}

int	ft_simb_pos(t_tokens *tokens, int str, int pos)
{
	if (tokens->ep_lst[str][pos] == '\\'
		&& (tokens->ep_lst[str][pos + 1] == '"'
		|| tokens->ep_lst[str][pos + 1] == '\\'
		|| tokens->ep_lst[str][pos + 1] == '$'))
		return (1);
	return (0);
}
