/* ************************************************************************** */
/**/
/*::::::::*/
/*   ft_lstlast.c  :+::+: */
/* +:+*/
/*   By: joppe <jboeve@student.codam.nl>  +#+ */
/*   +#+  */
/*   Created: 2022/11/03 18:09:12 by joppe #+##+# */
/*   Updated: 2023/08/12 00:38:22 by joppe ########   odam.nl */
/**/
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}
