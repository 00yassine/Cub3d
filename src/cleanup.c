/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkharti <elkharti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:01:52 by elkharti          #+#    #+#             */
/*   Updated: 2025/10/29 17:58:59 by elkharti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_gc_node	*g_gc_head = NULL;

void	cleanup_data(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->mlx_ptr)
	{
		i = 0;
		while (i < 4)
		{
			if (data->tex[i].img)
				mlx_destroy_image(data->mlx_ptr, data->tex[i].img);
			i++;
		}
		if (data->img)
			mlx_destroy_image(data->mlx_ptr, data->img);
		if (data->win_ptr)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	gc_malloc(0, 0);
}

void	*gc_malloc(size_t size, int mode)
{
	void		*ptr;
	t_gc_node	*new_node;

	if (mode == 0)
	{
		gc_free_all();
		return (NULL);
	}
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = (t_gc_node *)malloc(sizeof(t_gc_node));
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}
	new_node->ptr = ptr;
	new_node->next = g_gc_head;
	g_gc_head = new_node;
	return (ptr);
}

void	gc_free(void *ptr)
{
	t_gc_node	*current;
	t_gc_node	*prev;

	current = g_gc_head;
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				g_gc_head = current->next;
			free(current->ptr);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	gc_free_all(void)
{
	t_gc_node	*current;
	t_gc_node	*next;

	current = g_gc_head;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	g_gc_head = NULL;
}
