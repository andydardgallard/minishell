/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:18:44 by dgallard          #+#    #+#             */
/*   Updated: 2022/02/11 18:18:46 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		s1_len;
	int		s2_len;
	char	*s_joined;

	i = 0;
	s2_len = 0;
	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s_joined = (char *)malloc(s1_len + ft_strlen(s2) + 1);
	if (!s_joined)
		return (NULL);
	while (i < (s1_len + ft_strlen(s2)) && i < s1_len)
	{
		s_joined[i] = s1[i];
		i++;
	}
	while (i < (s1_len + ft_strlen(s2)) || !s2)
		s_joined[i++] = s2[s2_len++];
	s_joined[i] = '\0';
	return (s_joined);
}
