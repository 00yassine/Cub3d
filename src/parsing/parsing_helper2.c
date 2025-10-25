/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkharti <elkharti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:13:28 by ykabili-          #+#    #+#             */
/*   Updated: 2025/10/25 08:54:02 by elkharti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_atoi_skip(char *str, int *i)
{
	int	nb;

	nb = 0;
	skip_spaces(str, i);
	if (!(str[*i] >= '0' && str[*i] <= '9'))
		print_error("⚠️Error⚠️\n");
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		if (nb * 10 + (str[*i] - 48) > 255 || nb * 10 + (str[*i] - 48) < 0)
			return (-1);
		nb = nb * 10 + (str[*i] - 48);
		(*i)++;
	}
	skip_spaces(str, i);
	return (nb);
}
