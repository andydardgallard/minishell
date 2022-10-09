/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:18:57 by dgallard          #+#    #+#             */
/*   Updated: 2022/02/11 18:18:59 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, int n)
{
	int				i;
	unsigned char	*pstr1;
	unsigned char	*pstr2;

	i = 0;
	pstr1 = (unsigned char *)str1;
	pstr2 = (unsigned char *)str2;
	while (i != n && (pstr1[i] != '\0' || pstr2[i] != '\0'))
	{
		if (pstr1[i] != pstr2[i])
			return (pstr1[i] - pstr2[i]);
		i++;
	}
	return (0);
}
