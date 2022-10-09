/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arrs_helper_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:20:31 by dgallard          #+#    #+#             */
/*   Updated: 2022/02/10 22:35:46 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_exp_list_to_arr_flag_lst_h(t_tokens *tokens, int cnt,
	int cnt_exp, t_export_list *ex_lst)
{
	int	j;
	int	i;

	j = 0;
	i = cnt_exp + cnt - 1;
	while (i >= 0)
	{
		if (ex_lst[i].v[0] != '\0')
		{
			tokens->mini_export_list[j] = ft_strdup(ex_lst[i].v);
			if (ex_lst[i].var != NULL)
			{
				tokens->mini_export_list[j] = ft_strjoin(
						tokens->mini_export_list[j], "=\"");
				tokens->mini_export_list[j] = ft_strjoin(
						tokens->mini_export_list[j], ex_lst[i].var);
				tokens->mini_export_list[j] = ft_strjoin(
						tokens->mini_export_list[j], "\"");
			}
			j++;
		}
		i--;
	}
}

void	ft_exp_list_to_arr_flag_lst(t_tokens *tokens, int cnt,
	int cnt_exp, t_export_list *ex_lst)
{
	int	i;
	int	cnt_tkn;

	i = 0;
	while (tokens->mini_export_list[i] != NULL)
	{
		tokens->mini_export_list[i] = 0;
		free(tokens->mini_export_list[i]);
		i++;
	}
	tokens->mini_export_list = 0;
	free(tokens->mini_export_list);
	i = 0;
	cnt_tkn = 0;
	while (i < cnt + cnt_exp)
	{
		if (ex_lst[i].v[0] != '\0')
			cnt_tkn++;
		i++;
	}
	tokens->mini_export_list = (char **)malloc(sizeof(char *) * (cnt_tkn + 1));
	tokens->mini_export_list[cnt_tkn] = NULL;
	ft_exp_list_to_arr_flag_lst_h(tokens, cnt, cnt_exp, ex_lst);
}
