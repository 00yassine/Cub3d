#include "../includes/cub3d.h"
int count_lines(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	line = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return -1;
	while ((line = get_next_line(fd)) != NULL)
	{
		free(line);
		count++;
	}
	close(fd);
	return (count);
}

void print_error(char *error, int exitcode)
{
	printf("\033[31m%s",error);
	exit(exitcode);
}
int	main(int ac, char **av)
{
	int		fd;
	char	**map;
	int		i;
	int		len;

	i = 0;
	len = count_lines(av[1]);
	map = malloc(sizeof(char *) * len);
	if (ac != 2)
		print_error("Error: the number of arguments is not valid", 6);
	fd = open(av[1],O_RDONLY);
	if (fd < 0)
		print_error("Error: cannot open file", 5);
	while((map[i] = get_next_line(fd)) != NULL)
		i++;
	parce(map);
	return (0);
}
