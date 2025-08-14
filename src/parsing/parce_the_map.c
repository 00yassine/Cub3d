#include "../../includes/cub3d.h"

void skip_new_lines(char **map, char **p_map)
{
	int i = 0;
	int j = 0;

	while (map[i])
	{
		if (map[i][0] != '\n') // skip empty lines
		{
			p_map[j] = strdup(map[i]); // deep copy
			if (!p_map[j])
			{
				// handle allocation failure
				while (j-- > 0)
					free(p_map[j]);
				return;
			}
			j++;
		}
		i++;
	}
	p_map[j] = NULL; // terminate the array
}

void	parce(char **map, int len)
{
	char	**p_map;
	int		i;

	i = 0;
	p_map = malloc(sizeof(char *) * len);
	skip_new_lines(map, p_map);
	print_twodarr(p_map);
}
