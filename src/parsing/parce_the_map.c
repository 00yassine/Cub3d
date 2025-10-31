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

static void	check_is_valid_element(char *line)
{
	if (!line || !*line || line[0] == '\n')
		return ;
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "NO\t", 3) == 0)
		return ;
	else if (ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "SO\t", 3) == 0)
		return ;
	else if (ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "WE\t", 3) == 0)
		return ;
	else if (ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "EA\t", 3) == 0)
		return ;
	else if (ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "F\t", 2) == 0)
		return ;
	else if (ft_strncmp(line, "C ", 2) == 0
		|| ft_strncmp(line, "C\t", 2) == 0)
		return ;
	else if (line[0] == '1' || line[0] == '0' || line[0] == '\0')
		return ;
	else
		print_error("⚠️   Error   ⚠️\n");
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
		check_is_valid_element(map[i] + j);
		update_element_count(map_stu, map[i] + j);
		i++;
	}
	return (map_stu->ele.no * map_stu->ele.so
		* map_stu->ele.we * map_stu->ele.ea
		* map_stu->ele.f * map_stu->ele.c);
}

static void	parse_player_line(t_map *map_list, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "NO\t", 3) == 0)
		map_list->no_player = ft_str_take(line, 3);
	else if (ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "SO\t", 3) == 0)
		map_list->so_player = ft_str_take(line, 3);
	else if (ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "WE\t", 3) == 0)
		map_list->we_player = ft_str_take(line, 3);
	else if (ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "EA\t", 3) == 0)
		map_list->ea_player = ft_str_take(line, 3);
	else if (ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "F\t", 2) == 0)
		map_list->floor = ft_nb_take(line, 2);
	else if (ft_strncmp(line, "C ", 2) == 0
		|| ft_strncmp(line, "C\t", 2) == 0)
		map_list->ceiling = ft_nb_take(line, 2);
}

void	fill_player_str(t_map *map_list)
{
	char	**map;
	int		i;
	int		j;

	map = map_list->all_content;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && (map[i][j] == ' '
				|| (map[i][j] >= 9 && map[i][j] <= 13)))
			j++;
		parse_player_line(map_list, map[i] + j);
		i++;
	}
}
