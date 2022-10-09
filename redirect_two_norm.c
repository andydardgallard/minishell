/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_two_norm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:38:16 by dgallard          #+#    #+#             */
/*   Updated: 2022/02/11 14:00:51 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*ft_lft_red_helper(char **tmp, int cnt)
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

int	ft_lft_red(t_parser *tkn_strc, int i, t_tokens *tokens, int j)
{
	char	**tmp;
	int		cnt;
	int		k;
	char	*tmp2;

	tkn_strc[i].c_l_red++;
	tmp = ft_split(tkn_strc[i].tkn, ' ');
	cnt = -1;
	k = 0;
	while (tmp[k] != NULL)
	{
		if (ft_strncmp(tmp[k], "<", 1) != 0)
			cnt++;
		k++;
	}
	tmp2 = ft_lft_red_helper(tmp, cnt);
	while (*tmp2 == ' ')
		tmp2++;
	tokens->tokens_list[i] = ft_strdup(tmp2);
	j++;
	return (j);
}

int	ft_dbl_rght_red_help_one(t_parser *tkn_strc, t_tokens *tokens, int i, int j)
{
	if (tkn_strc[i].tkn[j + 2] == '>')
	{
		tokens->flag_error = -2;
		printf("minishel: syntax error near unexpected tkn `>'\n");
		tokens->input = "\0";
	}
	return (j);
}

char	*ft_dbl_rght_red_help_two(char **tmp, int cnt)
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
				cnt--;
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

int	ft_dbl_rght_red(t_parser *tkn_strc, int i, t_tokens *tokens, int j)
{
	char	**tmp;
	int		cnt;
	int		k;
	char	*tmp2;

	ft_dbl_rght_red_help_one(tkn_strc, tokens, i, j);
	tkn_strc[i].c_d_r_red++;
	tmp = ft_split(tkn_strc[i].tkn, ' ');
	cnt = -1;
	k = 0;
	while (tmp[k] != NULL)
	{
		if (ft_strncmp(tmp[k], ">>", 2) != 0)
			cnt++;
		k++;
	}
	tmp2 = ft_dbl_rght_red_help_two(tmp, cnt);
	while (*tmp2 == ' ')
		tmp2++;
	tokens->tokens_list[i] = ft_strdup(tmp2);
	j++;
	return (j);
}
