/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmerope <cmerope@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:02:28 by cmerope           #+#    #+#             */
/*   Updated: 2022/02/11 01:03:48 by cmerope          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	get_status(t_tokens *tokens)
{
	if (WIFEXITED(tokens->flag))
		g_exit = WEXITSTATUS(tokens->flag);
	if (WIFSIGNALED(tokens->flag))
		g_exit = 128 + WTERMSIG(tokens->flag);
}

int	ft_new_ep_lst(t_tokens *tokens, int str, int pos, int start)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	tmp = ft_substr(tokens->ep_lst[str], 0, start);
	tmp2 = ft_substr(tokens->ep_lst[str], start + 1, pos - start - 1);
	tmp3 = ft_strdup(tokens->ep_lst[str] + pos + 1);
	tokens->ep_lst[str] = ft_strdup(tmp);
	tokens->ep_lst[str] = ft_strjoin(tokens->ep_lst[str], tmp2);
	pos = start + ft_strlen(tmp2);
	free (tmp);
	free (tmp2);
	tokens->ep_lst[str] = ft_strjoin(tokens->ep_lst[str], tmp3);
	free (tmp3);
	return (pos);
}

int	ft_chek_simb(char c)
{
	if (c == ' ' || c == '\0' || c == '\\'
		|| c == '"' || c == '$' || c == '\'')
		return (0);
	return (1);
}

int	ft_flag_q(t_tokens *tokens, int start, int str, int pos)
{
	char	*tmp;

	tmp = NULL;
	if (tokens->ep_lst[str][pos] == '?' && str == 0
		&& !(ft_strchr(tokens->input, '|')))
	{
		if (tokens->flag_q == 2)
			g_exit = 127;
		printf("minishell: %d: command not found\n", g_exit);
	}
	else if (tokens->flag_q == 1 || tokens->flag_q == 2)
	{
		get_status(tokens);
		if (tokens->flag_q == 2 && str == 0 && !(ft_strchr(tokens->input, '|')))
			g_exit = 127;
		tmp = ft_strdup(ft_itoa(g_exit));
	}
	else if (tokens->ep_lst[str][pos] == '#')
		tmp = ft_strdup ("0");
	tokens->ep_lst[str] = ft_strdup(tmp);
	pos = start + ft_strlen(tmp) - 1;
	free (tmp);
	tokens->flag_q = 0;
	return (pos);
}

int	ft_chek_flag(t_tokens *tokens, char *tmp2)
{
	int	j;

	j = 0;
	tokens->flag_q = 0;
	while (tokens->envp_list[j])
	{
		if (ft_strnstr(tokens->envp_list[j], tmp2, ft_strlen(tmp2)) == 0)
		{
			tokens->flag_q = 1;
			j++;
		}
		else
		{
			tokens->flag_q = 2;
			break ;
		}
	}
	return (j);
}
