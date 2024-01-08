/* ************************************************************************** */
/**/
/*::::::::*/
/*   ft_lstadd_front.c  :+::+:*/
/* +:+*/
/*   By: joppe <jboeve@student.codam.nl>  +#+ */
/*   +#+  */
/*   Created: 2022/11/03 17:29:50 by joppe #+##+# */
/*   Updated: 2022/11/04 13:46:20 by jboeve########   odam.nl */
/**/
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
