/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_initializer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkharti <elkharti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:12:47 by ykabili-          #+#    #+#             */
/*   Updated: 2025/09/12 08:42:35 by elkharti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	struct_initializer(t_map *map)
{
	map->ele.no = 0;
	map->ele.so = 0;
	map->ele.we = 0;
	map->ele.ea = 0;
	map->ele.f = 0;
	map->ele.c = 0;
}
