/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arrs_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 20:34:12 by dgallard          #+#    #+#             */
/*   Updated: 2022/02/10 20:34:31 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_parse_export_tkn_util(int cnt_tkn, t_export_list	*alst)
{
	int	i;
	int	j;

	i = cnt_tkn - 2;
	while (i >= 0)
	{
		j = i - 1;
		while (j >= 0)
		{
			if (ft_strncmp(alst[i].v, alst[j].v, 4096.00) == 0)
			{
				if (alst[i].var == NULL && alst[j].var == NULL)
					ft_clear(&(alst[j].v), 0, ft_strlen(alst[j].v));
				else if (alst[i].var == NULL && alst[j].var != NULL)
					ft_clear(&(alst[i].v), 0, ft_strlen(alst[i].v));
				else if (alst[i].var != NULL && alst[j].var == NULL)
					ft_clear(&(alst[j].v), 0, ft_strlen(alst[j].v));
				else if (alst[i].var != NULL && alst[j].var != NULL)
					ft_clear(&(alst[j].v), 0, ft_strlen(alst[j].v));
			}
			j--;
		}
		i--;
	}
}

void	ft_parse_export_help(int i, char **tkn, t_export_list	*alst)
{
	int	j;

	j = 0;
	while (tkn[i][j] != '\0')
	{
		if ((tkn[i][j] < 48 && tkn[i][j] > 32)
			|| (tkn[i][j] < 65 && tkn[i][j] > 57)
			|| (tkn[i][j] < 97 && tkn[i][j] > 90)
			|| (tkn[i][j] < 127 && tkn[i][j] > 122))
		{
			printf("export: '%s': not a valid identifier\n", tkn[i]);
			ft_clear(&tkn[i], 0, ft_strlen(tkn[i]));
		}
		j++;
	}
	alst[i - 1].v = tkn[i];
	alst[i - 1].var = 0;
	alst[i - 1].cnt_tkn = i - 1;
}

void	ft_parse_export_print(int i, char **tkn)
{
	printf("export: '%s': not a valid identifier\n", tkn[i]);
	ft_clear(&tkn[i], 0, ft_strlen(tkn[i]));
}

void	ft_parse_export_helper(int i, char **tkn, t_export_list	*alst)
{
	int		j;
	char	*str;

	j = 0;
	str = 0;
	while (tkn[i][j] != '=')
		j++;
	alst[i - 1].v = ft_substr(tkn[i], 0, j);
	str = ft_strchr(tkn[i], '=');
	str++;
	alst[i - 1].var = str;
	alst[i - 1].cnt_tkn = i - 1;
}

t_export_list	*ft_parse_export_tkn(t_export_list	*alst, char **tkn)
{
	int	i;
	int	cnt_tkn;

	cnt_tkn = 1;
	while (tkn[cnt_tkn] != NULL)
		cnt_tkn++;
	alst = (t_export_list *)malloc(sizeof(t_export_list) * (cnt_tkn - 1));
	i = 1;
	while (i < cnt_tkn)
	{
		if ((tkn[i][0] < 65 || tkn[i][0] > 91)
			&& (tkn[i][0] < 96 || tkn[i][0] > 123))
			ft_parse_export_print(i, tkn);
		if (ft_strchr(tkn[i], '='))
			ft_parse_export_helper(i, tkn, alst);
		else
			ft_parse_export_help(i, tkn, alst);
		alst[i - 1].tkn = tkn[i];
		i++;
	}
	ft_parse_export_tkn_util(cnt_tkn, alst);
	return (alst);
}
