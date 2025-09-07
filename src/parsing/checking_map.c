/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkharti <elkharti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:21:50 by ykabili-          #+#    #+#             */
/*   Updated: 2025/09/03 20:07:52 by elkharti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_map_is_last(char **map)
{
	int	i;
	int	map_started;

	i = 0;
	map_started = 0;
	while (map[i])
	{
		if (!map_started && is_map_line(map[i]))
			map_started = 1;
		if (map_started)
		{
			if (!is_map_line(map[i]) && map[i][0] != '\n')
				print_error("Error: Map is not the last element", 8);
		}
		i++;
	}
}

void	check_map_valid(char **map)
{
	char	c;
	int		i;
	int		j;
	int		player_count;

	i = 0;
	j = 0;
	player_count = 0;
	while (map[i])
	{
		if (is_map_line(map[i]))
		{
			j = 0;
			while (map[i][j])
			{
				c = map[i][j];
				if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
					player_count++;
				else if (c != '0' && c != '1' && c != ' '
					&& c != '\n' && c != '\t')
					print_error("Error: Invalid character in map", 9);
				j++;
			}
		}
		i++;
	}
	if (player_count != 1)
		print_error("Error: Map must contain exactly one player", 10);
}

void	validate_map(char **map)
{
	check_map_is_last(map);
	check_map_valid(map);
}
