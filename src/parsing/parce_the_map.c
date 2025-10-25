/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parce_the_map.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ykabili- <ykabili-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/08/15 17:11:51 by ykabili-		  #+#	#+#			 */
/*   Updated: 2025/08/16 13:28:05 by ykabili-		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	update_element_count(t_map *map_stu, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "NO\t", 3) == 0)
		map_stu->ele.no += 1;
	else if (ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "SO\t", 3) == 0)
		map_stu->ele.so += 1;
	else if (ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "WE\t", 3) == 0)
		map_stu->ele.we += 1;
	else if (ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "EA\t", 3) == 0)
		map_stu->ele.ea += 1;
	else if (ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "F\t", 2) == 0)
		map_stu->ele.f += 1;
	else if (ft_strncmp(line, "C ", 2) == 0
		|| ft_strncmp(line, "C\t", 2) == 0)
		map_stu->ele.c += 1;
}

int	check_map_structer(t_map *map_stu, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && (map[i][j] == ' '
			|| (map[i][j] >= 9 && map[i][j] <= 13)))
			j++;
		update_element_count(map_stu, map[i] + j);
		i++;
	}
	return (map_stu->ele.no * map_stu->ele.so * map_stu->ele.we
		* map_stu->ele.ea * map_stu->ele.f * map_stu->ele.c);
}

void	fill_player_str(t_map *map_list)
{
	char	**map;

	int (i), (j);
	i = 0;
	map = map_list->all_content;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && (map[i][j] == ' '
			|| (map[i][j] >= 9 && map[i][j] <= 13)))
			j++;
		if (ft_strncmp(map[i] + j, "NO ", 3) == 0)
			map_list->no_player = ft_str_take(map[i] + j, 3);
		else if (ft_strncmp(map[i] + j, "SO ", 3) == 0)
			map_list->so_player = ft_str_take(map[i] + j, 3);
		else if (ft_strncmp(map[i] + j, "WE ", 3) == 0)
			map_list->we_player = ft_str_take(map[i] + j, 3);
		else if (ft_strncmp(map[i] + j, "EA ", 3) == 0)
			map_list->ea_player = ft_str_take(map[i] + j, 3);
		else if (ft_strncmp(map[i] + j, "F ", 2) == 0)
			map_list->floor = ft_nb_take(map[i] + j, 2);
		else if (ft_strncmp(map[i] + j, "C ", 2) == 0)
			map_list->ceiling = ft_nb_take(map[i] + j, 2);
		i++;
	}
}

t_map	*parce(char **map)
{
	t_map	*map_list;

	map_list = malloc(sizeof(t_map));
	struct_initializer(map_list);
	map_list->all_content = map;
	if (check_map_structer(map_list, map_list->all_content) != 1)
		print_error("⚠️Error⚠️\n");
	fill_player_str(map_list);
	validate_map(map_list);
	return (map_list);
}
