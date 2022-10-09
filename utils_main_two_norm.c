/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmerope <cmerope@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:37:15 by cmerope           #+#    #+#             */
/*   Updated: 2022/02/11 17:33:25 by cmerope          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_cnt_j(char *s, int *flag_join_d, int *flag_join)
{
	int	j;

	j = 0;
	if (*flag_join_d == 0 && *flag_join == 0)
	{
		while (s[j] != '"' && s[j] != '\'' && s[j] != '\0')
			j++;
	}
	else if (*flag_join_d == 1)
	{
		while (s[j] != '"' && s[j] != '\0')
			j++;
	}
	else
	{
		while (s[j] != '\'' && s[j] != '\0')
			j++;
	}
	return (j);
}

char	*ft_full_d_two(t_tokens *t, char *s, int *flag_join_d, int *cnt_tkn)
{
	int		cnt;
	char	*tmp2;

	cnt = 0;
	tmp2 = NULL;
	if (ft_strchr(s, '"'))
	{
		cnt = ft_cnt_d_quotes(s);
		if (cnt % 2)
		{
			*flag_join_d = 0;
			tmp2 = ft_strjoin(tmp2, " ");
			t->ep_lst[*cnt_tkn] = ft_strjoin(tmp2, s);
			(*cnt_tkn)++;
		}
	}
	else
	{
		tmp2 = ft_strjoin(tmp2, " ");
		tmp2 = ft_strjoin(tmp2, s);
	}
	return (tmp2);
}

char	*ft_full_d_one(t_tokens *t, char *s, int *flag_join_d, int *cnt_tkn)
{
	int		cnt;
	char	*tmp2;

	cnt = 0;
	tmp2 = NULL;
	if (*flag_join_d == 0)
	{
		cnt = ft_cnt_d_quotes(s);
		if (!(cnt % 2))
		{
			t->ep_lst[*cnt_tkn] = ft_strdup(s);
			(*cnt_tkn)++;
		}
		else
		{
			*flag_join_d = 1;
			tmp2 = ft_strdup(s);
		}
	}
	else if (*flag_join_d == 1)
		tmp2 = ft_full_d_two(t, s, flag_join_d, cnt_tkn);
	return (tmp2);
}

char	*ft_full_two(t_tokens *tokens, char *s, int *flag_join, int *cnt_tkn)
{
	int		cnt;
	char	*tmp2;

	cnt = 0;
	tmp2 = NULL;
	if (ft_strchr(s, '\''))
	{
		cnt = ft_cnt_quotes(s);
		if (cnt % 2)
		{
			*flag_join = 0;
			tmp2 = ft_strjoin(tmp2, " ");
			tokens->ep_lst[*cnt_tkn] = ft_strjoin(tmp2, s);
			(*cnt_tkn)++;
		}
	}
	else
	{
		tmp2 = ft_strjoin(tmp2, " ");
		tmp2 = ft_strjoin(tmp2, s);
	}
	return (tmp2);
}

char	*ft_full_one(t_tokens *tokens, char *s, int *flag_join, int *cnt_tkn)
{
	int		cnt;
	char	*tmp2;

	cnt = 0;
	tmp2 = NULL;
	if (*flag_join == 0)
	{
		cnt = ft_cnt_quotes(s);
		if (!(cnt % 2))
		{
			tokens->ep_lst[*cnt_tkn] = ft_strdup(s);
			(*cnt_tkn)++;
		}
		else
		{
			*flag_join = 1;
			tmp2 = ft_strdup(s);
		}
	}
	else if (*flag_join == 1)
		tmp2 = ft_full_two(tokens, s, flag_join, cnt_tkn);
	return (tmp2);
}
