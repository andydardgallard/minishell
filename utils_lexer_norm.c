/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:25:39 by dgallard          #+#    #+#             */
/*   Updated: 2022/02/11 15:25:41 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_parser	*ft_init_token_struct(t_tokens *tokens)
{
	int			i;
	t_parser	*tkn_strc;

	i = -1;
	tkn_strc = 0;
	tkn_strc = (t_parser *)malloc(sizeof(t_parser) * (tokens->h_lev + 1));
	tkn_strc[tokens->h_lev].iter = NULL;
	if (tokens->tokens_list)
	{
		while (++i < tokens->h_lev)
		{
			tkn_strc[i].tkn = tokens->tokens_list[i];
			tkn_strc[i].iter = "dgallard";
			tkn_strc[i].i = i;
			tkn_strc[i].c_d_l_red = 0;
			tkn_strc[i].d_l_red = 0;
			tkn_strc[i].c_d_r_red = 0;
			tkn_strc[i].d_r_red = 0;
			tkn_strc[i].c_l_red = 0;
			tkn_strc[i].l_red = 0;
			tkn_strc[i].c_r_red = 0;
			tkn_strc[i].r_red = 0;
		}
	}
	return (tkn_strc);
}

void	ft_c_d_l_red(t_parser *tkn_strc, int i)
{
	int		j;
	char	*tmp;
	char	**tmp2;

	tkn_strc[i].d_l_red = (char **)malloc(sizeof(char *)
			* (tkn_strc[i].c_d_l_red + 1));
	tkn_strc[i].d_l_red[tkn_strc->c_d_l_red] = NULL;
	tmp = ft_strnstr(tkn_strc[i].tkn, "<<", ft_strlen(tkn_strc[i].tkn));
	j = 0;
	tmp2 = 0;
	while (tkn_strc[i].c_d_l_red > j)
	{
		tmp = ft_strnstr(tmp, "<<", ft_strlen(tmp));
		tmp += 2;
		tmp2 = ft_split(tmp, ' ');
		tkn_strc[i].d_l_red[j] = ft_strdup(tmp2[0]);
		j++;
	}
}

void	ft_red_helper_two(t_parser *tkn_strc)
{
	int	i;

	i = 0;
	while (tkn_strc[i].iter != NULL)
	{
		if (tkn_strc[i].c_d_l_red > 0)
			ft_c_d_l_red(tkn_strc, i);
		if (tkn_strc[i].c_l_red > 0)
			ft_c_l_red(tkn_strc, i);
		if (tkn_strc[i].c_d_r_red > 0)
			ft_d_r_red(tkn_strc, i);
		if (tkn_strc[i].c_r_red > 0)
			ft_r_red(tkn_strc, i);
		i++;
	}
}

t_parser	*ft_lexer(t_tokens *tokens)
{
	int			i;
	char		*str;
	t_parser	*tkn_strc;

	i = 0;
	str = 0;
	tkn_strc = 0;
	tokens->h_lev = 1;
	if (tokens->input != NULL)
	{
		str = tokens->input;
		if (*str == '\0')
		{
			tokens->input = str;
			return (NULL);
		}
		if (ft_strchr(str, '|'))
			tokens->h_lev = tokens->h_lev + ft_chek_pipes(tokens);
		tokens->tokens_list = ft_split_modif(str, '|', tokens->h_lev);
		tkn_strc = ft_init_token_struct(tokens);
		ft_red_helper_one(tkn_strc, tokens);
		ft_red_helper_two(tkn_strc);
	}
	return (tkn_strc);
}
