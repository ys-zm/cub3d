/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:26:06 by yzaim             #+#    #+#             */
/*   Updated: 2024/01/08 15:26:10 by yzaim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timer.h"
#include "MLX42/MLX42.h"

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
