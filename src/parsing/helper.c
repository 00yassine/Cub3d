/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:50:59 by ykabili-          #+#    #+#             */
/*   Updated: 2025/10/31 10:51:21 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_map	*parce(char **map)
{
	t_map	*map_list;

	map_list = gc_malloc(sizeof(t_map));
	struct_initializer(map_list);
	map_list->all_content = map;
	if (check_map_structer(map_list, map_list->all_content) != 1)
		print_error("⚠️   Error   ⚠️\n");
	fill_player_str(map_list);
	validate_map(map_list);
	return (map_list);
}
