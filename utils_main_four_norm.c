/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main_four_norm.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmerope <cmerope@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:37:15 by cmerope           #+#    #+#             */
/*   Updated: 2022/02/11 17:40:07 by cmerope          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_cnt_j_all(char **tmp3, int *flag_join_d, int *flag_join, int *cnt_tkn)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tmp3[i] != NULL)
	{
		if ((!(ft_strchr(tmp3[i], '"')) && *flag_join_d == 0)
			&& (!(ft_strchr(tmp3[i], '\'')) && *flag_join == 0))
			(*cnt_tkn)++;
		j = ft_cnt_j(tmp3[i], flag_join_d, flag_join);
		if (tmp3[i][j] == '"')
			ft_cnt_tkn_d(flag_join_d, tmp3[i], cnt_tkn);
		else if (tmp3[i][j] == '\'')
			ft_cnt_tkn(flag_join, tmp3[i], cnt_tkn);
		i++;
	}
	return (j);
}

void	ft_full_all(t_tokens *t, char **tmp3, int *flag_join, int *flag_join_d)
{
	int		i;
	int		j;
	int		cnt_tkn;
	char	*tmp2;

	i = 0;
	cnt_tkn = 0;
	j = t->flag_j_cnt;
	while (tmp3[i] != NULL)
	{
		if ((!(ft_strchr(tmp3[i], '"')) && *flag_join_d == 0)
			&& (!(ft_strchr(tmp3[i], '\'')) && *flag_join == 0))
		{
			t->ep_lst[cnt_tkn] = ft_strdup(tmp3[i]);
			cnt_tkn++;
		}
		j = ft_cnt_j(tmp3[i], flag_join_d, flag_join);
		if (tmp3[i][j] == '"')
			tmp2 = ft_full_one(t, tmp3[i], flag_join_d, &cnt_tkn);
		else if (tmp3[i][j] == '\'')
			tmp2 = ft_full_one(t, tmp3[i], flag_join, &cnt_tkn);
		i++;
	}
}
