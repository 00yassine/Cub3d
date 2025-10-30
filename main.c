/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:35:46 by elkharti          #+#    #+#             */
/*   Updated: 2025/10/30 10:26:49 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	count_lines(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	line = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

void	print_error(char *error)
{
	printf("\033[31m%s", error);
	gc_free_all();
	exit(1);
}

char	**load_map_from_file(char *filename)
{
	int		fd;
	char	**map;
	int		len;
	char	*line;

	len = count_lines(filename);
	if (len < 0)
		print_error("Error: cannot open file");
	map = gc_malloc(sizeof(char *) * (len + 1));
	if (!map)
		print_error("Error: memory allocation failed");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error("Error: cannot open file");
	len = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		map[len++] = line;
		line = get_next_line(fd);
	}
	map[len] = NULL;
	close(fd);
	return (map);
}

int	main(int ac, char **av)
{
	char	**map;
	t_map	*parsed_map;

	if (ac != 2)
		print_error("Error: the number of arguments is not valid");
	map = load_map_from_file(av[1]);
	parsed_map = parce(map);
	raycasting_entry(parsed_map);
	gc_free_all();
	return (0);
}
