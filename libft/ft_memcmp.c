/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:44:03 by ykabili-          #+#    #+#             */
/*   Updated: 2024/10/27 17:50:11 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*sa;
	unsigned char	*sb;
	size_t			i;

	i = 0;
	sa = (unsigned char *)s1;
	sb = (unsigned char *)s2;
	while (i < n)
	{
		if (sa[i] > sb[i] || sa[i] < sb[i])
			return (sa[i] - sb[i]);
		i++;
	}
	return (0);
}
