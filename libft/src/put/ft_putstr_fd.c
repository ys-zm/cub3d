/* ************************************************************************** */
/**/
/*::::::::*/
/*   ft_putstr_fd.c :+::+:*/
/* +:+*/
/*   By: joppe <jboeve@student.codam.nl>  +#+ */
/*   +#+  */
/*   Created: 2022/10/13 20:42:52 by joppe #+##+# */
/*   Updated: 2022/10/20 10:20:20 by joppe ########   odam.nl */
/**/
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = ft_strlen(s);
	write(fd, s, len);
}
