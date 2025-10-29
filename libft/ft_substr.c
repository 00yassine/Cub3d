/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkharti <elkharti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:59:39 by ykabili-          #+#    #+#             */
/*   Updated: 2025/10/29 08:41:55 by elkharti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	char *sub;
	size_t i;
	unsigned int n;

	i = 0;
	if (!s)
		return (NULL);
	n = ft_strlen(s);
	if (n <= start)
		return (ft_strdup(""));
	if (n - start < len)
		len = n - start;
	sub = (char *)gc_malloc((len + 1) * sizeof(char), 1);
	if (!sub)
		return (NULL);
	while (s[start] != '\0' && i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
