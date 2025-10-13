/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:21:50 by ykabili-          #+#    #+#             */
/*   Updated: 2025/10/13 19:11:24 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_position(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'W'
		&& c != 'E' && c != 'S' && c != ' ')
	{
		return (1);
	}
	return (0);
}

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
			if (!is_map_line(map[i]) && map[i][0] && map[i][0] != '\n')
				print_error("Error: Map is not the last element", 8);
		}
		i++;
	}
}

void	check_map_valid_char(char **map)
{
	char	c;

	int (i), (j), (player_count);
	i = 0;
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

void	check_map_flood_fill(char **map)
{
	int (i), (j);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' ||
				map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (i == 0 || !map[i + 1] || j == 0 || !map[i][j + 1] ||
					check_position(map[i - 1][j]) ||
					check_position(map[i + 1][j]) ||
					check_position(map[i][j - 1]) ||
					check_position(map[i][j + 1]))
				{
					print_error("Error: Map is not closed by walls", 98);
				}
			}
			j++;
		}
		i++;
	}
}

void	validate_map(t_map *map_struct)
{
	int		i;
	char	**map;

	map = map_struct->all_content;
	check_map_is_last(map);
	i = 0;
	while (map[i] && map[i][0] != '1' && map[i][0] != '0' && map[i][0] != ' ')
		i++;
	if (!map[i])
		print_error("Error: Map not found", 11);
	check_map_valid_char(&map[i]);
	check_map_flood_fill(&map[i]);
	map_struct->all_content = &map[i];
}
