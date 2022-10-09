/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_parser_norm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmerope <cmerope@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:44:21 by cmerope           #+#    #+#             */
/*   Updated: 2022/02/11 18:02:10 by cmerope          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_for_parser(t_tokens *tokens)
{
	int		i;
	int		cnt;
	char	*str;

	i = 0;
	cnt = 0;
	str = tokens->input;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			i = ft_count_cnt(i, &cnt, str, '"');
		else if (str[i] == '\'')
			i = ft_count_cnt(i, &cnt, str, '\'');
		else if (str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '"'))
			i++;
		i++;
	}
	if (cnt % 2)
		ft_print_error(tokens, -1);
}

void	ft_begin(t_tokens *tokens)
{
	int		i;
	char	*str;

	i = 0;
	str = tokens->input;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
		ft_print_error(tokens, -2);
	else if (str[i] == '\'' || str[i] == '"')
	{
		while (str[i] == '\'' || str[i] == '"')
			i++;
		if (str[i] == '|')
			tokens->flag_error = -1;
		else if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i++;
			if (str[i] == '|')
				ft_print_error(tokens, -1);
		}
	}
}

void	ft_end(t_tokens *tokens, int len)
{
	char	*str;

	str = tokens->input;
	while (str[len] == ' ')
		len++;
	if (str[len] == '|')
		ft_print_error(tokens, -2);
	else if (str[len] == '\'' || str[len] == '"')
	{
		while (str[len] == '\'' || str[len] == '"')
			len++;
		if (str[len] == '|')
			tokens->flag_error = -1;
		else if (str[len] == ' ')
		{
			while (str[len] == ' ')
				len++;
			if (str[len] == '|')
				ft_print_error(tokens, -1);
		}
	}
}

void	ft_for_pipe(t_tokens *tokens)
{
	int	len;

	len = ft_strlen(tokens->input) - 1;
	ft_begin(tokens);
	ft_end(tokens, len);
	if (tokens->flag_error == -1 || tokens->flag_error == -2)
		tokens->input = "\0";
}

int	ft_chek_pipes(t_tokens *tokens)
{
	int		pipe;
	char	**tmp3;
	int		i;
	int		start;

	pipe = 0;
	tmp3 = ft_split_modif(tokens->input, ' ', 0);
	start = 0;
	while (tmp3[start])
	{
		i = 0;
		while (tmp3[start][i] != '\0')
		{
			i = utils_chek_pipes(tmp3[start], i, &pipe, tokens);
			i++;
		}
		start++;
	}
	ft_free_str(&tmp3);
	return (pipe);
}
