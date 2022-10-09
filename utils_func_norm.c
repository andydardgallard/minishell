/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func_norm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:08:32 by dgallard          #+#    #+#             */
/*   Updated: 2022/02/11 18:08:34 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_cd_utils(t_tokens *tokens, char *pnew)
{
	int	j;
	int	i;

	j = 0;
	while (tokens->envp_list[j] != NULL)
	{
		i = 0;
		while (tokens->envp_list[j][i] != '\0')
		{
			if (tokens->envp_list[j][0] == 'P'
				&& tokens->envp_list[j][1] == 'W'
				&& tokens->envp_list[j][2] == 'D'
				&& tokens->envp_list[j][3] == '=')
				tokens->envp_list[j] = pnew;
			i++;
		}
		j++;
	}
}

void	ft_cd(t_tokens *tokens, int iter)
{
	char	**tkn;
	char	*pold;
	char	*pnew;
	char	new_dir[4096];

	(void) iter;
	tkn = tokens->ep_lst;
	if (!(ft_strncmp(tkn[1], "..", 3)))
	{
		pold = ft_pwd_for_cd();
		chdir(pold);
	}
	else
		chdir(tkn[1]);
	getcwd(new_dir, sizeof(new_dir));
	pnew = new_dir;
	pnew = ft_strjoin("PWD=", pnew);
	ft_cd_utils(tokens, pnew);
}

void	ft_clear(char **str, int start, int end)
{
	while (start < end)
	{
		str[0][start] = '\0';
		start++;
	}
}

int	ft_what_function(t_tokens *tokens, int i, t_export_list ***alst)
{
	if (ft_same(tokens, "echo", 0, i) == 2)
	{
		ft_echo(tokens, i);
		return (2);
	}
	else if (ft_same(tokens, "pwd", 0, i) == 2)
	{
		printf("%s\n", ft_pwd());
		return (2);
	}
	else if (ft_same(tokens, "env", 0, i) == 2)
	{
		ft_env(tokens);
		return (2);
	}
	else if (ft_same(tokens, "export", 0, i) == 2)
	{
		ft_export(tokens, i, alst);
		if (tokens->export_flag == 1)
			ft_mini_export(tokens, i);
		return (2);
	}
	return (0);
}
