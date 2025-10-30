/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 19:56:10 by ykabili-          #+#    #+#             */
/*   Updated: 2025/10/30 10:35:13 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		lens1;
	int		lens2;

	lens1 = 0;
	lens2 = 0;
	if (s1)
		lens1 = ft_strlen(s1);
	if (s2)
		lens2 = ft_strlen(s2);
	result = (char *)gc_malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!result)
		return (NULL);
	lens1 = 0;
	lens2 = 0;
	while (s1 && s1[lens1] != '\0')
	{
		result[lens1] = s1[lens1];
		lens1++;
	}
	while (s2 && s2[lens2] != '\0')
		result[lens1++] = s2[lens2++];
	result[lens1] = '\0';
	return (result);
}
