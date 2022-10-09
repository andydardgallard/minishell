/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:09:36 by dgallard          #+#    #+#             */
/*   Updated: 2022/02/11 01:09:39 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_printf_unset_error(char **tkn, int i)
{
	printf("unset: '%s': not a valid identifier\n", tkn[i]);
	ft_clear(&tkn[i], 0, ft_strlen(tkn[i]));
}

char	**ft_unset_util(char **tkn)
{
	int	i;
	int	j;

	i = 1;
	while (tkn[i] != NULL)
	{
		if ((tkn[i][0] < 65 || tkn[i][0] > 91)
			&& (tkn[i][0] < 96 || tkn[i][0] > 123))
			ft_printf_unset_error(tkn, i);
		else
		{
			j = 0;
			while (tkn[i][j] != '\0')
			{
				if ((tkn[i][j] < 48 && tkn[i][j] > 32)
					|| (tkn[i][j] < 65 && tkn[i][j] > 57)
					|| (tkn[i][j] < 97 && tkn[i][j] > 90)
					|| (tkn[i][j] < 127 && tkn[i][j] > 122))
					ft_printf_unset_error(tkn, i);
				j++;
			}
		}
		i++;
	}
	return (tkn);
}

void	ft_unset_utils(t_tokens *tokens, int j, char *tkn)
{
	char	*tmp;
	int		cnt_tkn;

	cnt_tkn = 0;
	if (ft_strchr(tokens->mini_export_list[j], '='))
	{
		while (tokens->mini_export_list[j][cnt_tkn] != '\0')
		{
			if (tokens->mini_export_list[j][cnt_tkn] == '=')
				break ;
			cnt_tkn++;
		}
		tmp = ft_substr(tokens->mini_export_list[j], 0, cnt_tkn);
	}
	else
		tmp = tokens->mini_export_list[j];
	if (ft_strncmp(tkn, tmp, 4096) == 0)
		ft_clear(&tokens->mini_export_list[j], 0,
			ft_strlen(tokens->mini_export_list[j]));
}

void	ft_unset(t_tokens *tokens, char **tkn_q)
{
	char	**tkn;
	int		i;
	int		j;
	int		cnt_tkn;

	i = 1;
	cnt_tkn = 0;
	tkn = ft_unset_util(tkn_q);
	if (tokens->export_flag == 1)
	{
		while (tkn[i] != NULL)
		{
			if (tkn[i][0] != '\0')
			{
				j = 0;
				while (tokens->mini_export_list[j] != NULL)
				{
					ft_unset_utils(tokens, j, tkn[i]);
					j++;
				}
			}
			i++;
		}
	}
	tokens->mini_export_list = ft_arrdup(tokens->mini_export_list);
}
