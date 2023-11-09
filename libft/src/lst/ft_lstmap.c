/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 12:08:46 by joppe         #+#    #+#                 */
/*   Updated: 2022/11/04 13:58:52 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_head;
	t_list	*cur_node;

	if (!lst)
		return (NULL);
	new_head = ft_lstnew(NULL);
	if (!new_head)
		return (NULL);
	cur_node = new_head;
	cur_node->content = f(lst->content);
	lst = lst->next;
	while (lst)
	{
		new_node = ft_lstnew(NULL);
		if (!new_node)
			return (ft_lstclear(&new_head, del), NULL);
		new_node->content = f(lst->content);
		cur_node->next = new_node;
		cur_node = cur_node->next;
		lst = lst->next;
	}
	return (new_head);
}
