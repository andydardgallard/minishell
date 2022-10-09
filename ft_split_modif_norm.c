/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_modif.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmerope <cmerope@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:44:21 by cmerope           #+#    #+#             */
/*   Updated: 2022/02/10 19:08:49 by cmerope          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static char	**ft_malloc_error(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static unsigned int	ft_get_nb_strs(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nb_strs;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_strs++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		if (s[i] == '"' || s[i] == '\'')
			i = ft_next_step(i, s);
		i++;
	}
	if (s[i - 1] != c)
		nb_strs++;
	return (nb_strs);
}

static void	ft_get_next_str(char **next_str, unsigned int *next_str_len,
					char c)
{
	unsigned int	i;

	*next_str += *next_str_len;
	*next_str_len = 0;
	i = 0;
	while (**next_str && **next_str == c)
		(*next_str)++;
	while ((*next_str)[i])
	{
		i = ft_skip_quote(i, next_str_len, next_str);
		if ((*next_str)[i] == c)
			return ;
		(*next_str_len)++;
		i++;
	}
}

int	ft_get_nb(int nb, char *s, char c)
{
	int	nb_strs;

	nb_strs = 0;
	if (nb == 0)
		nb_strs = ft_get_nb_strs(s, c);
	else
		nb_strs = (unsigned int)nb;
	return (nb_strs);
}

char	**ft_split_modif(char *s, char c, int nb)
{
	char			**tab;
	unsigned int	next_str_len;
	unsigned int	nb_strs;
	unsigned int	i;

	if (!s)
		return (NULL);
	nb_strs = ft_get_nb(nb, s, c);
	tab = (char **)malloc(sizeof(char *) * (nb_strs + 1));
	if (!tab)
		return (NULL);
	i = -1;
	next_str_len = 0;
	while (++i < nb_strs)
	{
		ft_get_next_str(&s, &next_str_len, c);
		tab[i] = (char *)malloc(sizeof(char) * (next_str_len + 1));
		if (!tab[i])
			return (ft_malloc_error(tab));
		ft_strlcpy(tab[i], s, next_str_len + 1);
	}
	tab[i] = NULL;
	return (tab);
}
