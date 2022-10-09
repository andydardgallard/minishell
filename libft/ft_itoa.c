/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 14:38:37 by mstyr             #+#    #+#             */
/*   Updated: 2022/02/11 18:17:56 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_putnbr_i(unsigned int len)
{
	size_t	i;

	i = 0;
	while (len >= 10)
	{
		len /= 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	char			*s;
	unsigned int	n2;
	unsigned int	i;

	n2 = n;
	i = ft_putnbr_i(n2) + 0;
	s = (char *)malloc(sizeof(char) * i + 1);
	if (!s)
		return (NULL);
	if (n == 0)
	{
		s[0] = '0';
		s[1] = '\0';
	}
	s[i] = '\0';
	i--;
	while (n2 > 0)
	{
		s[i] = (n2 % 10) + 48;
		n2 /= 10;
		i--;
	}
	if (n < 0)
		s[0] = '-';
	return (s);
}
