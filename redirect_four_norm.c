/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_four.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:38:16 by dgallard          #+#    #+#             */
/*   Updated: 2022/02/11 15:20:50 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_r_red_help(t_parser *tkn_strc, int i, int k)
{
	int		j;
	char	*tmp;
	char	**tmp2;

	j = 0;
	tmp2 = 0;
	while (tkn_strc[i].tkn[j] != '\0')
	{
		if ((j > 0 && tkn_strc[i].tkn[j] == '>'
				&& tkn_strc[i].tkn[j + 1] != '>'
				&& tkn_strc[i].tkn[j - 1] != '>')
			|| (j == 0 && tkn_strc[i].tkn[j] == '>'
				&& tkn_strc[i].tkn[j + 1] != '>'))
		{
			tmp = tkn_strc[i].tkn + j + 1;
			tmp2 = ft_split(tmp, ' ');
			tkn_strc[i].r_red[k] = ft_strdup(tmp2[0]);
			k--;
		}
		j++;
	}
}

void	ft_r_red(t_parser *tkn_strc, int i)
{
	int	j;
	int	k;

	tkn_strc[i].r_red = (char **)malloc(sizeof(char *)
			* (tkn_strc[i].c_r_red + 1));
	tkn_strc[i].r_red[tkn_strc->c_r_red] = NULL;
	k = tkn_strc[i].c_r_red - 1;
	ft_r_red_help(tkn_strc, i, k);
	j = 0;
	while (j < tkn_strc[i].c_r_red)
	{
		if (tkn_strc[i].r_red[j] == NULL)
			printf("minishell: syntax error near unexpected tkn `newline'\n");
		j++;
	}
}

void	ft_d_r_red(t_parser *tkn_strc, int i)
{
	int		j;
	char	*tmp;
	char	**tmp2;

	tkn_strc[i].d_r_red = (char **)malloc(sizeof(char *)
			* (tkn_strc[i].c_d_r_red + 1));
	tkn_strc[i].d_r_red[tkn_strc->c_d_r_red] = NULL;
	tmp = ft_strnstr(tkn_strc[i].tkn, ">>", ft_strlen(tkn_strc[i].tkn));
	j = 0;
	tmp2 = 0;
	while (tkn_strc[i].c_d_r_red > j)
	{
		tmp = ft_strnstr(tmp, ">>", ft_strlen(tmp));
		tmp += 2;
		tmp2 = ft_split(tmp, ' ');
		tkn_strc[i].d_r_red[j] = ft_strdup(tmp2[0]);
		if (tkn_strc[i].d_r_red[j] == NULL)
			printf("minishell: syntax error near unexpected tkn `newline'\n");
		j++;
	}
}

void	ft_c_l_red_help(t_parser *tkn_strc, int i, int k)
{
	int		j;
	char	*tmp;
	char	**tmp2;

	j = 0;
	tmp2 = 0;
	while (tkn_strc[i].tkn[j] != '\0')
	{
		if ((j > 0 && tkn_strc[i].tkn[j] == '<'
				&& tkn_strc[i].tkn[j + 1] != '<'
				&& tkn_strc[i].tkn[j - 1] != '<')
			|| (j == 0 && tkn_strc[i].tkn[j] == '<'
				&& tkn_strc[i].tkn[j + 1] != '<'))
		{
			tmp = tkn_strc[i].tkn + j + 1;
			tmp2 = ft_split(tmp, ' ');
			tkn_strc[i].l_red[k] = ft_strdup(tmp2[0]);
			k--;
		}
		j++;
	}
}

void	ft_c_l_red(t_parser *tkn_strc, int i)
{
	int	k;

	tkn_strc[i].l_red = (char **)malloc(sizeof(char *)
			* (tkn_strc[i].c_l_red + 1));
	tkn_strc[i].l_red[tkn_strc->c_l_red] = NULL;
	k = tkn_strc[i].c_l_red - 1;
	ft_c_l_red_help(tkn_strc, i, k);
}
