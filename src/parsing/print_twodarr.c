/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   print_twodarr.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ykabili- <ykabili-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/08/15 17:12:25 by ykabili-		  #+#	#+#			 */
/*   Updated: 2025/08/16 14:25:48 by ykabili-		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_twodarr(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
}
void print_info(t_map *map)
{
    int i = 0;
    printf("Map content:\n");
    if (map->all_content)
    {
        while (map->all_content[i])
        {
            if (map->all_content[i][0] != '\n')
                printf("%s\n", map->all_content[i]);
            i++;
        }
    }

    printf("Textures:\n");
    printf("NO: %s\n", map->no_player ? map->no_player : "NULL");
    printf("SO: %s\n", map->so_player ? map->so_player : "NULL");
    printf("WE: %s\n", map->we_player ? map->we_player : "NULL");
    printf("EA: %s\n", map->ea_player ? map->ea_player : "NULL");

    printf("Floor color: R=%d, G=%d, B=%d\n",
        map->floor.r, map->floor.g, map->floor.b);
    printf("Ceiling color: R=%d, G=%d, B=%d\n",
        map->ceiling.r, map->ceiling.g, map->ceiling.b);
}
