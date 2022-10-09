/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_crt_path_arr_norm.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:13:19 by dgallard          #+#    #+#             */
/*   Updated: 2022/02/11 18:17:13 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_struct_init(t_tokens *tokens)
{
	tokens->input = 0;
	tokens->path_list = 0;
	tokens->tokens_list = 0;
	tokens->flag_error = 0;
	tokens->right_red = 0;
	tokens->dbl_right_red = 0;
	tokens->r_r_f = 0;
	tokens->cnt_tokens = 1;
	tokens->h_lev = 1;
	tokens->envp_list = 0;
	tokens->export_list = 0;
	tokens->mini_export_list = 0;
	tokens->export_flag = 0;
	tokens->ep_lst = 0;
	tokens->path_cnt = 0;
	tokens->flag = 0;
	tokens->flag_q = 0;
	tokens->flag_j_cnt = 0;
}

int	ft_count_smbls(char *str, char smbl)
{
	int	cnt;

	cnt = 0;
	while (*str != '\0')
	{
		if (*str == smbl)
			cnt++;
		str++;
	}
	return (cnt);
}

void	ft_crt_path_utils(t_tokens *tokens, int word, int i, char *str_path)
{
	int	j;

	tokens->path_list[i] = (char *)malloc(word + 1);
	j = 0;
	while (j < word)
	{
		tokens->path_list[i][j] = str_path[j];
		j++;
	}
	tokens->path_list[i][word] = '\0';
}

void	ft_crt_path_arr(t_tokens *tokens, char *str_path)
{
	int		i;
	int		word;
	char	*start;

	tokens->path_cnt = ft_count_smbls(str_path, ':') + 1;
	tokens->path_list = (char **)malloc(sizeof(char *) * tokens->path_cnt);
	i = 0;
	while (i < tokens->path_cnt)
	{
		start = str_path;
		word = 0;
		while (*start != ':' && *start != '\0')
		{
			word++;
			start++;
		}
		ft_crt_path_utils(tokens, word, i, str_path);
		start++;
		str_path = start;
		i++;
	}
}

void	ft_parse_vpath(t_tokens *tokens, char **envp)
{
	char	*str_path;
	int		j;
	int		i;

	j = 0;
	while (envp[j] != NULL)
	{
		i = 0;
		while (envp[j][i] != '\0')
		{
			if (envp[j][0] == 'P' && envp[j][1] == 'A'
				&& envp[j][2] == 'T' && envp[j][3] == 'H'
				&& envp[j][4] == '=')
				str_path = envp[j];
			i++;
		}
		j++;
	}
	str_path = ft_strchr(str_path, '/');
	if (str_path)
		ft_crt_path_arr(tokens, str_path);
	else
		write(1, "command not found:\n", 18);
}
