/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:12:30 by ykabili-          #+#    #+#             */
/*   Updated: 2025/10/29 16:00:35 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_color	ft_nb_take(char *str, int i)
{
	t_color	color;

	color.r = ft_atoi_skip(str, &i);
	if (str[i] != ',')
		print_error("⚠️Error⚠️\n");
	i++;
	color.g = ft_atoi_skip(str, &i);
	if (str[i] != ',')
		print_error("⚠️Error⚠️\n");
	i++;
	color.b = ft_atoi_skip(str, &i);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			print_error("⚠️Error⚠️\n");
		i++;
	}
	if (color.r < 0 || color.r > 255 || color.g < 0
		|| color.g > 255 || color.b < 0 || color.b > 255)
		print_error("⚠️Error⚠️\n");
	return (color);
}

void	get_path_bounds(char *line, int i, int *start, int *end)
{
	int	last;

	while (line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
		i++;
	if (!line[i])
		print_error("⚠️Error⚠️\n");
	*start = i;
	last = *start;
	while (line[last] && line[last] != '\n')
		last++;
	last--;
	while (line[last] == ' ' || (line[last] >= 9 && line[last] <= 13))
		last--;
	*end = last + 1;
	i = *start;
	while (i < *end)
	{
		if (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
			print_error("⚠️Error⚠️\n");
		i++;
	}
}

char	*ft_str_take(char *line, int i)
{
	int		start;
	int		end;
	char	*path;

	get_path_bounds(line, i, &start, &end);
	path = ft_substr(line, start, end - start);
	if (access(path, F_OK) != 0)
	{
		print_error("⚠️Error⚠️\n");
	}
	return (path);
}

void	skip_spaces(char *str, int *i)
{
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (line[i] == '1' || line[i] == '0');
}
