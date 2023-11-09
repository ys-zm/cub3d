/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   timer.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 22:45:21 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/08 22:50:50 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "timer.h"

t_timer	*timer_init(t_timer *t, double (*time_func)(void))
{
	t->time_func = time_func;
	return (t);
}

double	timer_start(t_timer *t)
{
	t->start = (*t->time_func)();
	return (t->start);
}

double	timer_stop(t_timer *t)
{
	t->end = (*t->time_func)();
	return (t->end);
}

double	timer_delta(t_timer *t)
{
	timer_stop(t);
	t->delta = t->end - t->start;
	return (t->delta);
}
