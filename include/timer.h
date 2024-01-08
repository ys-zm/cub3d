/* ************************************************************************** */
/**/
/*   :::::::: */
/*   timer.h   :+::+: */
/*+:+ */
/*   By: joppe <jboeve@student.codam.nl> +#+  */
/*  +#+   */
/*   Created: 2023/11/08 22:44:16 by joppe #+##+# */
/*   Updated: 2023/11/08 22:50:57 by joppe ########   odam.nl */
/**/
/* ************************************************************************** */


#ifndef TIMER_H
# define TIMER_H

typedef struct s_timer
{
	double	start;
	double	end;
	double	delta;
	double	(*time_func)(void);
}	t_timer;

t_timer	*timer_init(t_timer *t, double (*time_func)(void));
double	timer_start(t_timer *t);
double	timer_stop(t_timer *t);
double	timer_delta(t_timer *t);

#endif
