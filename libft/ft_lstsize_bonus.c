/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:15:15 by ykabili-          #+#    #+#             */
/*   Updated: 2024/11/10 16:29:04 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

// int main()
// {
// 	t_list *head = NULL;
// 	ft_lstadd_back(&head, ft_lstnew("1st node"));
// 	ft_lstadd_back(&head, ft_lstnew("2nd node"));
// 	ft_lstadd_back(&head, ft_lstnew("3rd node"));
// 	printf("%d",ft_lstsize(head));
// }