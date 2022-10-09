/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:37:15 by cmerope           #+#    #+#             */
/*   Updated: 2022/02/11 17:55:42 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_cp_path_arr_help(t_tokens *tokens, char **path)
{
	int	i;
	int	j;

	i = 0;
	while (i < tokens->path_cnt)
	{
		path[i] = (char *)malloc(ft_strlen(tokens->path_list[i]) + 1);
		if (!(path[i]))
		{
			tokens->flag_error = 1;
			return ;
		}
		j = 0;
		while (j < ft_strlen(tokens->path_list[i]))
		{
			path[i][j] = tokens->path_list[i][j];
			path[i][ft_strlen(tokens->path_list[i])] = '\0';
			j++;
		}
		i++;
	}
}

char	**ft_cp_path_arr(t_tokens *tokens)
{
	char	**path;

	path = (char **)malloc(sizeof(char *) * tokens->path_cnt);
	if (!(path))
	{
		tokens->flag_error = 1;
		return (NULL);
	}
	ft_cp_path_arr_help(tokens, path);
	return (path);
}

char	*ft_clean_redirect(char **tkn, int cnt_redir)
{
	char	*tmp;
	int		i;

	i = 1;
	tmp = 0;
	tmp = tkn[0];
	while (tkn[i] != NULL)
	{
		if (i != cnt_redir && i != cnt_redir + 1)
		{
			tmp = ft_strjoin(tmp, " ");
			tmp = ft_strjoin(tmp, tkn[i]);
		}
		i++;
	}
	return (tmp);
}

void	ft_c_d_l_red_util(t_parser *tokens_struct, int i, t_tokens *tokens)
{
	int		l;
	char	*str;

	str = "minishell: syntax error near unexpected token `newline'";
	if (tokens_struct[i].c_d_l_red)
	{
		tokens->red_input = 0;
		l = 0;
		while (l < tokens_struct[i].c_d_l_red)
		{
			while (1)
			{
				if (tokens_struct[i].d_l_red[l] == NULL)
				{
					printf("%s\n", str);
					break ;
				}
				tokens->red_input = readline("> ");
				if (ft_strncmp(tokens->red_input,
						tokens_struct[i].d_l_red[l], 4096) == 0)
					break ;
			}
			l++;
		}
	}
}

int	ft_c_l_red_utils(t_parser *tokens_struct, int i, t_tokens *tokens)
{
	if (tokens_struct[i].c_l_red)
	{
		if (tokens_struct[i].l_red[0] == NULL)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (0);
		}
		else
		{
			tokens->tokens_list[i] = ft_strjoin(tokens->tokens_list[i], " ");
			tokens->tokens_list[i] = ft_strjoin(tokens->tokens_list[i],
					tokens_struct[i].l_red[0]);
			ft_split_for_parser(tokens, tokens->tokens_list[i]);
			ft_parser(tokens);
		}
	}
	return (1);
}
