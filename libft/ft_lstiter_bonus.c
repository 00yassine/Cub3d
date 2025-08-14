/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:42:52 by ykabili-          #+#    #+#             */
/*   Updated: 2024/11/11 18:42:54 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f || !lst)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
// void fti_toupper(void *c)
// {
//     char *str =(char *)c;
//     int i;
//     i = 0;
//     while(str[i])
//     {
//         str[i] = (char)ft_toupper((unsigned char)str[i]);
//         i++;
//     }
// }
// int main()
// {
//     t_list *node;
//     char *str = ft_strdup("abcd");
//     node = ft_lstnew(str);
//     printf("%s\n",(char *)node->content);
//     ft_lstiter(node, fti_toupper);
//     printf("%s",(char *)node->content);
// }