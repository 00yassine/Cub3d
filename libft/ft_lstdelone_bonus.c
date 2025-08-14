/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:19:20 by ykabili-          #+#    #+#             */
/*   Updated: 2024/11/11 17:19:22 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst)
	{
		if (del)
		{
			del(lst->content);
		}
		free (lst);
	}
}

// void del(void *content) {
//     free(content);
// }
// int main() {
//     t_list *node = ft_lstnew(ft_strdup("Hello, World!"));

//     if (node) {
//         printf("%s\n", (char *)node->content);
//         ft_lstdelone(node, del);
//         printf("%s\n", (char *)node->content);
//     }
//     return 0;
// }