/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extention_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:35:49 by ykabili-          #+#    #+#             */
/*   Updated: 2025/10/24 15:42:53 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_map_name(char *str)
{
	int (i) = 0;
	while (str[i])
		i++;
	if (str[i - 1] == 'b' && str[i - 2] == 'u'
		&& str[i - 3] == 'c' && str[i - 4] == '.')
		return (1);
	return (0);
}

void	ft_ex_checker(char *str)
{
	if (!check_map_name(str))
	{
		printf("Error\n:⚠️​invalid map file, please try another file⚠️.\n");
		exit(1);
	}
}
