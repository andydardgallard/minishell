/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arrs_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 23:11:26 by dgallard          #+#    #+#             */
/*   Updated: 2022/02/10 23:11:28 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_crt_envp_list_helper(t_tokens *tokens, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	tokens->envp_list = (char **)malloc(sizeof(char *) * (i + 1));
	tokens->export_list = (char **)malloc(sizeof(char *) * (i + 1));
	tokens->envp_list[i] = NULL;
	tokens->export_list[i] = NULL;
}

void	ft_crt_envp_list(t_tokens *tokens, char **envp)
{
	int	i;
	int	j;

	i = 0;
	ft_crt_envp_list_helper(tokens, envp);
	while (envp[i] != NULL)
	{
		j = 0;
		while (envp[i][j] != '\0')
			j++;
		tokens->envp_list[i] = (char *)malloc(j + 1);
		tokens->envp_list[i][j] = '\0';
		tokens->export_list[i] = (char *)malloc(j + 1);
		tokens->export_list[i][j] = '\0';
		j = 0;
		while (envp[i][j] != '\0')
		{
			tokens->envp_list[i][j] = envp[i][j];
			tokens->export_list[i][j] = envp[i][j];
			j++;
		}
		i++;
	}
}

t_export_list	*ft_init_export_strct(t_export_list *alst, int cnt_tkn)
{
	int	i;

	i = 1;
	while (i < cnt_tkn)
	{
		alst[i].tkn = 0;
		alst[i].v = 0;
		alst[i].var = 0;
		alst[i].cnt_tkn = 0;
		i++;
	}
	return (alst);
}

void	ft_helper_one(int i, int cnt_tkn, char **tkn, t_export_list *alst)
{
	int		j;
	char	*str;

	while (i < cnt_tkn)
	{
		if (ft_strchr(tkn[i], '='))
		{
			j = 0;
			str = 0;
			while (tkn[i][j] != '=')
				j++;
			alst[i].v = ft_substr(tkn[i], 0, j);
			str = ft_strchr(tkn[i], '=');
			str = str + 2;
			alst[i].var = ft_substr(str, 0, ft_strlen(str) - 1);
			alst[i].cnt_tkn = i;
		}
		else
		{
			alst[i].v = tkn[i];
			alst[i].var = 0;
			alst[i].cnt_tkn = i;
		}
		i++;
	}
}

t_export_list	*ft_parse_export_tkn_flag(t_export_list *alst, char **tkn)
{
	int	i;
	int	cnt_tkn;

	cnt_tkn = 0;
	while (tkn[cnt_tkn] != NULL)
		cnt_tkn++;
	alst = (t_export_list *)malloc(sizeof(t_export_list) * (cnt_tkn));
	i = 0;
	ft_helper_one(i, cnt_tkn, tkn, alst);
	return (alst);
}
