/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_three.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:50:06 by dgallard          #+#    #+#             */
/*   Updated: 2022/02/11 14:37:24 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*ft_rght_red_helper(char **tmp, int cnt)
{
	int		k;
	char	*tmp2;

	k = 0;
	tmp2 = "";
	while (tmp[k] != NULL && cnt > 0)
	{
		if (ft_redirect_if_one(tmp, k))
		{
			if (k == 0)
			{
				tmp2 = ft_strjoin(tmp2, " ");
				tmp2 = ft_strjoin(tmp2, tmp[k]);
			}
			else if (ft_redirect_if_two(tmp, k))
			{
				tmp2 = ft_strjoin(tmp2, " ");
				tmp2 = ft_strjoin(tmp2, tmp[k]);
				cnt--;
			}
		}
		k++;
	}
	return (tmp2);
}

int	ft_rght_red(t_parser *tkn_strc, int i, t_tokens *tokens, int j)
{
	char	**tmp;
	int		cnt;
	int		k;
	char	*tmp2;

	tkn_strc[i].c_r_red++;
	tmp = ft_split(tkn_strc[i].tkn, ' ');
	cnt = -1;
	k = 0;
	while (tmp[k] != NULL)
	{
		if (ft_strncmp(tmp[k], ">", 1) != 0)
			cnt++;
		k++;
	}
	tmp2 = ft_rght_red_helper(tmp, cnt);
	while (*tmp2 == ' ')
		tmp2++;
	tokens->tokens_list[i] = ft_strdup(tmp2);
	return (j);
}

int	ft_redirect_if_three(t_parser *tkn_strc, int i, int j)
{
	if ((j > 0 && tkn_strc[i].tkn[j] == '<'
			&& tkn_strc[i].tkn[j + 1] != '<'
			&& tkn_strc[i].tkn[j - 1] != '<')
		|| (j == 0 && tkn_strc[i].tkn[j] == '<'
			&& tkn_strc[i].tkn[j + 1] != '<'))
		return (1);
	else
		return (0);
}

int	ft_redirect_if_four(t_parser *tkn_strc, int i, int j)
{
	if ((j > 0 && tkn_strc[i].tkn[j] == '>'
			&& tkn_strc[i].tkn[j + 1] != '>'
			&& tkn_strc[i].tkn[j - 1] != '>')
		|| (j == 0 && tkn_strc[i].tkn[j] == '>'
			&& tkn_strc[i].tkn[j + 1] != '>'))
		return (1);
	else
		return (0);
}

void	ft_red_helper_one(t_parser *tkn_strc, t_tokens *tokens)
{
	int	i;
	int	j;

	i = 0;
	while (tkn_strc[i].iter != NULL)
	{
		j = 0;
		while (tkn_strc[i].tkn[j] != '\0')
		{	
			if (tkn_strc[i].tkn[j] == '<' && tkn_strc[i].tkn[j + 1] == '<')
				j = ft_dbl_lft_red(tkn_strc, tokens, i, j);
			if (ft_redirect_if_three(tkn_strc, i, j))
				j = ft_lft_red(tkn_strc, i, tokens, j);
			if (tkn_strc[i].tkn[j] == '>' && tkn_strc[i].tkn[j + 1] == '>')
				ft_dbl_rght_red(tkn_strc, i, tokens, j);
			if (ft_redirect_if_four(tkn_strc, i, j))
				j = ft_rght_red(tkn_strc, i, tokens, j);
			j++;
		}
		i++;
	}
}
