#include "../../includes/cub3d.h"

int	check_map_structer(t_map *map_stu)
{
	int	i;
	char **map;

	map = map_stu->all_content;
	i = 0;
	while (map[i])
	{
		if (ft_strncmp(map[i],"NO ", 3) == 0)
			map_stu->ele.no = 1;
		if (ft_strncmp(map[i],"SO ", 3) == 0)
			map_stu->ele.so = 1;
		if (ft_strncmp(map[i],"WE ", 3) == 0)
			map_stu->ele.we = 1;
		if (ft_strncmp(map[i],"EA ", 3) == 0)
			map_stu->ele.ea = 1;
		if (ft_strncmp(map[i],"F ", 2) == 0)
			map_stu->ele.f = 1;
		if (ft_strncmp(map[i],"C ", 2) == 0)
			map_stu->ele.c = 1;
		i++;
	}
	return ((map_stu->ele.no && map_stu->ele.so &&
			map_stu->ele.we && map_stu->ele.ea &&
			map_stu->ele.f && map_stu->ele.c) * i);
}
void	parce(char **map)
{
	t_map	*map_list;
	int		i;

	i = 0;
	map_list = malloc(sizeof(t_map));
	map_list->all_content = map;
	if (check_map_structer(map_list) == 0)
		print_error("Error: some of the info are not there.", 15);
}
