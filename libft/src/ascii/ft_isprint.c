/* ************************************************************************** */
/**/
/*::::::::*/
/*   ft_isprint.c   :+::+:*/
/* +:+*/
/*   By: jboeve <jboeve@student.codam.nl> +#+ */
/*   +#+  */
/*   Created: 2022/10/05 09:02:31 by jboeve#+##+# */
/*   Updated: 2022/10/20 10:11:19 by joppe ########   odam.nl */
/**/
/* ************************************************************************** */

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
