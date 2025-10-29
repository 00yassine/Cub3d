/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:59:51 by elkharti          #+#    #+#             */
/*   Updated: 2025/10/29 16:02:31 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_gc_node	*g_gc_head = NULL;

void	*gc_malloc(size_t size, int mode)
{
	void			*ptr;
	t_gc_node		*new_node;

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
