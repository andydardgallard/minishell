/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions_norm.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:10:50 by dgallard          #+#    #+#             */
/*   Updated: 2022/02/11 01:10:52 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_same(t_tokens *tokens, char *str, int j, int i)
{
	char	**tkn;

	tkn = tokens->ep_lst;
	while (tkn[j][i] == str[i])
	{
		i++;
		if (str[i - 1] == '\0')
			return (2);
	}
	return (1);
}

char	*ft_pwd(void)
{
	char	*str_pwd;
	char	dir[4096];

	getcwd(dir, sizeof(dir));
	str_pwd = dir;
	return (str_pwd);
}

void	ft_echo(t_tokens *tokens, int j)
{
	int		flag;
	int		i;
	char	**tkn;

	(void) j;
	flag = 0;
	i = 1;
	tkn = tokens->ep_lst;
	if (ft_same(tokens, "-n", 1, 0) == 2)
		flag = 1;
	while (tkn[i] != NULL)
	{
		if (flag == 1)
			i++;
		write(1, tkn[i], ft_strlen(tkn[i]));
		write(1, " ", 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
}

char	*ft_pwd_for_cd(void)
{
	int		i;
	int		j;
	int		c;
	char	*str;
	char	*s;

	i = 0;
	j = 0;
	c = 0;
	str = ft_pwd();
	i = ft_count_smbls(str, '/');
	while (str[c] != '\0')
	{
		if (str[c] == '/')
		{
			j++;
			if (i == j)
				break ;
		}
		c++;
	}
	s = ft_substr(str, 0, c);
	return (s);
}

void	ft_env(t_tokens *tokens)
{
	int	i;

	i = 0;
	while (tokens->envp_list[i] != NULL)
	{
		printf("%s\n", tokens->envp_list[i]);
		i++;
	}
}
