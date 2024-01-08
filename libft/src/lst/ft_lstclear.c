/* ************************************************************************** */
/**/
/*::::::::*/
/*   ft_lstclear.c  :+::+:*/
/* +:+*/
/*   By: joppe <jboeve@student.codam.nl>  +#+ */
/*   +#+  */
/*   Created: 2022/11/04 10:12:00 by joppe #+##+# */
/*   Updated: 2022/11/04 13:46:48 by jboeve########   odam.nl */
/**/
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*old;

	tmp = *lst;
	while (tmp)
	{
		old = tmp;
		del(tmp->content);
		tmp = tmp->next;
		free(old);
	}
	*lst = NULL;
}
