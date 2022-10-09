/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:09:12 by dgallard          #+#    #+#             */
/*   Updated: 2022/02/11 01:09:14 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_export_utils(t_tokens *tokens, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < len - 1)
	{
		j = len - 1;
		while (j > i)
		{
			if (ft_strncmp(tokens->export_list[j - 1],
					tokens->export_list[j], 4096) >= 0)
			{
				tmp = tokens->export_list[j - 1];
				tokens->export_list[j - 1] = tokens->export_list[j];
				tokens->export_list[j] = tmp;
			}
			j--;
		}
		i++;
	}
}

void	ft_export_print(t_tokens *tokens)
{
	int	i;
	int	j;

	i = 0;
	while (tokens->export_list[i] != NULL)
	{
		write (1, "declare -x ", 12);
		j = 0;
		while (tokens->export_list[i][j] != '=')
		{
			write (1, &tokens->export_list[i][j], 1);
			j++;
		}
		if (tokens->export_list[i][j] == '=')
		{
			write (1, "=\"", 2);
			j++;
			write (1, &tokens->export_list[i][j],
				ft_strlen(&tokens->export_list[i][j]));
			write (1, "\"\n", 2);
		}
		else
			write (1, "\n", 1);
		i++;
	}
}

void	ft_export(t_tokens *tokens, int j, t_export_list ***alst)
{
	int		len;
	char	**tkn;
	int		cnt_tkn;

	(void) alst;
	(void) j;
	len = 0;
	cnt_tkn = 0;
	tkn = tokens->ep_lst;
	while (tkn[cnt_tkn] != NULL)
		cnt_tkn++;
	while (tokens->envp_list[len] != NULL)
		len++;
	ft_export_utils(tokens, len);
	if (cnt_tkn == 1)
		ft_export_print(tokens);
}

void	ft_mini_export_util(int len_m, t_tokens *tokens)
{
	int		i;
	int		j;
	char	*tmp_m;

	i = 0;
	while (i < len_m - 1)
	{
		j = len_m - 1;
		while (j > i)
		{
			if (ft_strncmp(tokens->mini_export_list[j - 1],
					tokens->mini_export_list[j], 4096) >= 0)
			{
				tmp_m = tokens->mini_export_list[j - 1];
				tokens->mini_export_list[j - 1] = tokens->mini_export_list[j];
				tokens->mini_export_list[j] = tmp_m;
			}
			j--;
		}
		i++;
	}
}

void	ft_mini_export(t_tokens *tokens, int j)
{
	int		i;
	int		len_m;
	char	**tkn;
	int		cnt_tkn;

	(void) j;
	len_m = 0;
	cnt_tkn = 0;
	tkn = tokens->ep_lst;
	while (tkn[cnt_tkn] != NULL)
		cnt_tkn++;
	while (tokens->mini_export_list[len_m] != NULL)
		len_m++;
	ft_mini_export_util(len_m, tokens);
	if (cnt_tkn == 1)
	{
		i = 0;
		while (tokens->mini_export_list[i] != NULL)
		{
			printf("declare -x ");
			printf("%s\n", tokens->mini_export_list[i]);
			i++;
		}
	}
}
