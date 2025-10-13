/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:13:28 by ykabili-          #+#    #+#             */
/*   Updated: 2025/10/13 19:14:39 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_atoi_skip(char *str, int *i)
{
	int	nb;

	nb = 0;
	skip_spaces(str, i);
	if (!(str[*i] >= '0' && str[*i] <= '9'))
		print_error("Error: Invalid color number\n", 1);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		nb = nb * 10 + (str[*i] - 48);
		(*i)++;
	}
	skip_spaces(str, i);
	return (nb);
}
