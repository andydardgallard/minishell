/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmerope <cmerope@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:44:21 by cmerope           #+#    #+#             */
/*   Updated: 2022/02/10 20:21:27 by cmerope          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_print_error(t_tokens *tokens, int f)
{
	tokens->flag_error = f;
	if (tokens->flag_error == -2)
		printf("minishel: syntax error near unexpected token `|'\n");
	if (tokens->flag_error == -1)
		printf("minishel: command not found\n");
}

int	ft_count_cnt(int i, int *cnt, char *str, char c)
{
	(*cnt)++;
	i++;
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] == c)
		(*cnt)++;
	return (i);
}

void	ft_free_str(char ***str)
{
	int	i;

	i = 0;
	while ((*str)[i] != NULL)
	{
		free((*str)[i]);
		i++;
	}
	free(*str);
}

int	utils_chek_pipes(char *tmp3, int i, int *pipe, t_tokens *tokens)
{
	if (tmp3[i] == '|' && tmp3[i + 1] == '|')
	{
		ft_print_error(tokens, -2);
		tokens->input = "\0";
		return (0);
	}
	if (tmp3[i] == '"' || tmp3[i] == '\'')
	{
		i = ft_next_step(i, tmp3);
		i++;
	}
	if (tmp3[i] == '|')
		(*pipe)++;
	return (i);
}
