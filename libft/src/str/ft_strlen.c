/* ************************************************************************** */
/**/
/*::::::::*/
/*   ft_strlen.c:+::+:*/
/* +:+*/
/*   By: jboeve <jboeve@student.codam.nl> +#+ */
/*   +#+  */
/*   Created: 2022/10/05 09:10:16 by jboeve#+##+# */
/*   Updated: 2022/11/01 19:20:47 by joppe ########   odam.nl */
/**/
/* ************************************************************************** */

#include "libft.h"

 //added a check to see if s exists before dereferencing it
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}
