/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkharti <elkharti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:35:46 by elkharti          #+#    #+#             */
/*   Updated: 2025/10/25 09:29:31 by elkharti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int count_lines(char *filename)
{
	int fd;
	int count;
	char *line;

	count = 0;
	line = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

void print_error(char *error)
{
	printf("\033[31m%s", error);
	exit(1);
}

char **load_map_from_file(char *filename)
{
	int fd;
	char **map;
	int len;
	char *line;

	len = count_lines(filename);
	if (len < 0)
		print_error("Error: cannot open file");
	map = malloc(sizeof(char *) * (len + 1));
	if (!map)
		print_error("Error: memory allocation failed");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		(free(map), print_error("Error: cannot open file"));
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

char **load_map_from_file(char *filename)
{
	char **map;
	t_map *parsed_map;

	if (ac != 2)
		print_error("Error: the number of arguments is not valid");
	map = load_map_from_file(av[1]);
	parsed_map = parce(map);
	start(parsed_map);
	cleanup_map(parsed_map);
	free_2d_array(map);
	return (0);
}
