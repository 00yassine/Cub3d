/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:47:36 by ykabili-          #+#    #+#             */
/*   Updated: 2025/10/24 15:49:21 by ykabili-         ###   ########.fr       */
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
	while ((line = get_next_line(fd)) != NULL)
	{
		free(line);
		count++;
	}
	close(fd);
	return (count);
}

void	print_error(char *error, int exitcode)
{
	printf("\033[31m%s", error);
	exit(exitcode);
}

int	main(int ac, char **av)
{
	int		fd;
	char	**map;
	t_map	*parsed_map;
	int		i;
	int		len;

	if (ac != 2)
		print_error("Error: the number of arguments is not valid", 6);
	ft_ex_checker(av[1]);
	len = count_lines(av[1]);
	if (len < 0)
		print_error("Error: cannot open file", 5);
	map = malloc(sizeof(char *) * (len + 1));
	if (!map)
		print_error("Error: memory allocation failed", 7);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		free(map);
		print_error("Error: cannot open file", 5);
	}
	i = 0;
	while ((map[i] = get_next_line(fd)) != NULL)
		i++;
	map[i] = NULL;
	close(fd);
	parsed_map = parce(map);
	start(parsed_map);
	cleanup_map(parsed_map);
	free_2d_array(map);
	return (0);
}
