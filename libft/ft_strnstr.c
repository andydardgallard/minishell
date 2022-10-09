/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:24:40 by tblink            #+#    #+#             */
/*   Updated: 2022/02/11 18:19:04 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, int len)
{
	int	i;
	int	k;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[0])
		{
			k = 1;
			while (needle[k] && haystack[i + k] == needle[k] && (i + k) < len)
				k++;
			if (!needle[k])
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}
