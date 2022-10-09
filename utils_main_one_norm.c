/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main_one_norm.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:37:15 by cmerope           #+#    #+#             */
/*   Updated: 2022/02/11 18:44:15 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_cnt_d_quotes(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			cnt++;
		i++;
	}
	return (cnt);
}

int	ft_cnt_quotes(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && str[i - 1] != '\\')
			cnt++;
		i++;
	}
	return (cnt);
}

void	ft_cnt_tkn_d(int *flag_join_d, char *s, int *cnt_tkn)
{
	int	cnt;

	cnt = 0;
	if (*flag_join_d == 0)
	{
		cnt = ft_cnt_d_quotes(s);
		if (!(cnt % 2))
			(*cnt_tkn)++;
		else
			*flag_join_d = 1;
	}
	if (*flag_join_d == 1)
	{
		if (ft_strchr(s, '"'))
		{
			cnt = ft_cnt_d_quotes(s + 1);
			if (cnt % 2)
			{
				(*cnt_tkn)++;
				*flag_join_d = 0;
			}
		}
	}
}

void	ft_cnt_tkn(int *flag_join, char *s, int *cnt_tkn)
{
	int	cnt;

	cnt = 0;
	if (*flag_join == 0)
	{
		cnt = ft_cnt_quotes(s);
		if (!(cnt % 2))
			(*cnt_tkn)++;
		else
			*flag_join = 1;
	}
	else if (*flag_join == 1)
	{
		if (ft_strchr(s, '\''))
		{
			cnt = ft_cnt_quotes(s);
			if (cnt % 2)
			{
				(*cnt_tkn)++;
				*flag_join = 0;
			}
		}
	}
}

void	ft_split_for_parser(t_tokens *tokens, char *str)
{
	char	**tmp3;
	int		flag_join_d;
	int		flag_join;
	int		cnt_tkn;

	tokens->flag_error = 0;
	tmp3 = NULL;
	cnt_tkn = 0;
	flag_join_d = 0;
	flag_join = 0;
	tmp3 = ft_split_modif(str, ' ', 0);
	tokens->flag_j_cnt = ft_cnt_j_all(tmp3, &flag_join_d, &flag_join, &cnt_tkn);
	tokens->ep_lst = (char **)malloc(sizeof(char *) * (cnt_tkn + 1));
	tokens->ep_lst[cnt_tkn] = NULL;
	ft_full_all(tokens, tmp3, &flag_join, &flag_join_d);
	ft_free_str(&tmp3);
}
