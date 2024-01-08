/* ************************************************************************** */
/**/
/*::::::::*/
/*   ft_putchar_fd.c:+::+:*/
/* +:+*/
/*   By: joppe <jboeve@student.codam.nl>  +#+ */
/*   +#+  */
/*   Created: 2022/10/16 22:50:05 by joppe #+##+# */
/*   Updated: 2022/11/03 15:36:34 by jboeve########   odam.nl */
/**/
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
