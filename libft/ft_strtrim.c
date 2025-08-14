/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:04:11 by ykabili-          #+#    #+#             */
/*   Updated: 2024/10/28 20:17:02 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	is_in_set(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		z;
	char	*result;

	z = 0;
	j = ft_strlen(s1);
	i = 0;
	while (s1[i] && is_in_set(set, s1[i]))
		i++;
	j--;
	while (j >= i && is_in_set(set, s1[j]))
		j--;
	result = (char *)malloc(sizeof(char) * (j - i + 2));
	if (!result)
		return (NULL);
	while (i <= j)
		result[z++] = s1[i++];
	result[z] = '\0';
	return (result);
}
