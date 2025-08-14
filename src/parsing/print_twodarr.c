#include "../../includes/cub3d.h"

void	print_twodarr(char **map)
{
	int	i = 0;

	while (map[i])
	{
		printf("%s",map[i]);
		i++;
	}
}
