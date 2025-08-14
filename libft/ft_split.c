/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:12:05 by ykabili-          #+#    #+#             */
/*   Updated: 2024/11/01 22:51:33 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_count_words(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static int	ft_start_index(const char *s, char c, int i)
{
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

static int	ft_end_index(const char *s, char c, int i)
{
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_free(char **str, int i)
{
	while (i-- > 0)
		free (str[i]);
	free (str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	t_split	zo;

	if (!s)
		return (NULL);
	zo.word_i = 0;
	zo.i = 0;
	zo.word_c = ft_count_words((char *)s, c);
	zo.result = (char **)malloc(sizeof (char *) * (zo.word_c + 1));
	if (!zo.result)
		return (NULL);
	while (zo.word_i < zo.word_c)
	{
		zo.start = ft_start_index(s, c, zo.i);
		zo.end = ft_end_index(s, c, zo.start);
		zo.result[zo.word_i] = ft_substr(s, zo.start, zo.end - zo.start);
		if (!zo.result[zo.word_i])
			return (ft_free(zo.result, zo.word_i));
		zo.word_i++;
		zo.i = zo.end;
	}
	zo.result[zo.word_c] = NULL;
	return (zo.result);
}
