/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arrs_helper_one_norm.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:20:31 by dgallard          #+#    #+#             */
/*   Updated: 2022/02/10 22:53:42 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_exp_list_to_arr_flag_srt(int cnt, int cnt_exp, t_export_list *ex_lst)
{
	int	i;
	int	j;

	i = cnt_exp + cnt - 1;
	while (i >= 0)
	{
		j = i - 1;
		while (j >= 0)
		{
			if (ft_strncmp(ex_lst[i].v, ex_lst[j].v, 4096.00) == 0)
			{
				if (ex_lst[i].var == NULL && ex_lst[j].var == NULL)
					ft_clear(&(ex_lst[j].v), 0, ft_strlen(ex_lst[j].v));
				else if (ex_lst[i].var == NULL && ex_lst[j].var != NULL)
					ft_clear(&(ex_lst[i].v), 0, ft_strlen(ex_lst[i].v));
				else if (ex_lst[i].var != NULL && ex_lst[j].var == NULL)
					ft_clear(&(ex_lst[j].v), 0, ft_strlen(ex_lst[j].v));
				else if (ex_lst[i].var != NULL && ex_lst[j].var != NULL)
					ft_clear(&(ex_lst[j].v), 0, ft_strlen(ex_lst[j].v));
			}
			j--;
		}
		i--;
	}
}

int	ft_exp_list_to_arr_flag_cnt(int cnt_exp,
	t_export_list *lst, t_export_list *ex_lst)
{
	int	i;

	i = 0;
	while (i < cnt_exp)
	{
		ex_lst[i].v = ft_strdup(lst[i].v);
		ex_lst[i].var = ft_strdup(lst[i].var);
		ex_lst[i].cnt_tkn = lst[i].cnt_tkn;
		i++;
	}
	return (i);
}

int	ft_helper(char **tkn, t_export_list *alst, t_tokens *tokens, int *cnt_exp)
{
	int	i;
	int	cnt_tkn;
	int	cnt;
	int	j;

	i = 0;
	j = 0;
	cnt = 0;
	cnt_tkn = 1;
	while (tokens->mini_export_list[j] != NULL)
		j++;
	j = *cnt_exp;
	while (tkn[cnt_tkn] != NULL)
		cnt_tkn++;
	while (i < cnt_tkn - 1)
	{
		if (alst[i].v[0] != '\0')
			cnt++;
		i++;
	}
	return (cnt);
}

void	ft_utils(t_export_list *alst, int j, t_export_list *ex_lst, int i)
{
	int	cnt_tkn;

	cnt_tkn = 0;
	while (i < j)
	{
		if (alst[cnt_tkn].v[0] != '\0')
		{
			ex_lst[i].v = ft_strdup(alst[cnt_tkn].v);
			ex_lst[i].var = ft_strdup(alst[cnt_tkn].var);
			ex_lst[i].cnt_tkn = i;
			i++;
		}
		cnt_tkn++;
	}
}

void	ft_exp_list_to_arr_flag(t_export_list *alst,
	t_tokens *tokens, char **tkn)
{
	int				i;
	int				cnt;
	int				cnt_exp;
	t_export_list	*lst;
	t_export_list	*ex_lst;

	i = 0;
	lst = 0;
	cnt = 0;
	cnt_exp = 0;
	lst = ft_parse_export_tkn_flag(lst, tokens->mini_export_list);
	cnt = ft_helper(tkn, alst, tokens, &cnt_exp);
	ex_lst = (t_export_list *)malloc(sizeof(t_export_list) * (cnt_exp + cnt));
	i = ft_exp_list_to_arr_flag_cnt(cnt_exp, lst, ex_lst);
	ft_utils(alst, cnt_exp + cnt, ex_lst, i);
	ft_exp_list_to_arr_flag_srt(cnt, cnt_exp, ex_lst);
	ft_exp_list_to_arr_flag_lst(tokens, cnt, cnt_exp, ex_lst);
	free(lst);
}
