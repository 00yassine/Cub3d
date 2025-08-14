/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:41:40 by ykabili-          #+#    #+#             */
/*   Updated: 2024/11/10 16:52:12 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

	// int main()
	// {
	// t_list *head = NULL;
	// ft_lstadd_back(&head, ft_lstnew("1st node"));
	// ft_lstadd_back(&head, ft_lstnew("2nd node"));
	// ft_lstadd_back(&head, ft_lstnew("3rd node"));
	// t_list *tmp = ft_lstlast(head);
	// printf("%s",tmp->content);
	// }