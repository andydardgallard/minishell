/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 20:42:55 by dgallard          #+#    #+#             */
/*   Updated: 2022/02/10 21:07:08 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_arrdup_utils(char **arr, char **tmp)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (arr[i] != NULL)
	{
		if (arr[i][0] != '\0')
		{
			tmp[cnt] = ft_strdup(arr[i]);
			cnt++;
		}
		arr[i] = 0;
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_arrdup(char **arr)
{
	int		i;
	int		cnt;
	char	**tmp;

	i = 0;
	cnt = 0;
	while (arr[i] != NULL)
	{
		if (arr[i][0] != '\0')
			cnt++;
		i++;
	}
	tmp = (char **)malloc(sizeof(char *) * (cnt + 1));
	tmp[cnt] = NULL;
	ft_arrdup_utils(arr, tmp);
	return (tmp);
}

void	ft_exp_list_to_arr_help(int cnt_tkn,
	t_tokens *tokens, t_export_list *alst)
{
	int	i;
	int	cnt_exp;

	i = 0;
	cnt_exp = 0;
	while (i < cnt_tkn - 1)
	{
		if (alst[i].v[0] != '\0')
		{
			tokens->mini_export_list[cnt_exp] = alst[i].v;
			if (alst[i].var != NULL)
			{
				tokens->mini_export_list[cnt_exp] = ft_strjoin(
						tokens->mini_export_list[cnt_exp], "=\"");
				tokens->mini_export_list[cnt_exp] = ft_strjoin(
						tokens->mini_export_list[cnt_exp], alst[i].var);
				tokens->mini_export_list[cnt_exp] = ft_strjoin(
						tokens->mini_export_list[cnt_exp], "\"");
			}
			cnt_exp++;
		}
		i++;
	}
}

void	ft_exp_list_to_arr(t_export_list *alst, t_tokens *tokens, char **tkn)
{
	int	i;
	int	cnt_exp;
	int	cnt_tkn;

	i = 0;
	cnt_exp = 0;
	cnt_tkn = 1;
	while (tkn[cnt_tkn] != NULL)
		cnt_tkn++;
	while (i < cnt_tkn - 1)
	{
		if (alst[i].v[0] != '\0')
			cnt_exp++;
		i++;
	}
	tokens->mini_export_list = (char **)malloc(sizeof(char *) * (cnt_exp +1));
	tokens->mini_export_list[cnt_exp] = NULL;
	ft_exp_list_to_arr_help(cnt_tkn, tokens, alst);
	tokens->export_flag = 1;
}

void	ft_crt_export_arr(t_tokens *tokens, char	**tkn)
{
	t_export_list	*alst;

	alst = 0;
	alst = ft_parse_export_tkn(alst, tkn);
	if (tokens->export_flag == 0)
		ft_exp_list_to_arr(alst, tokens, tkn);
	else
		ft_exp_list_to_arr_flag(alst, tokens, tkn);
	free(alst);
}
