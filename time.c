/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 01:45:21 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/23 19:21:17 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline void	time_diff(
	struct timespec *start,
	struct timespec *end,
	struct timespec *out
) {
	out->tv_nsec = end->tv_nsec - start->tv_nsec;
	out->tv_sec = end->tv_sec - start->tv_sec;
	if (out->tv_nsec < 0)
	{
		out->tv_nsec += 1000000000L;
		--out->tv_sec;
	}
}

void	update_timer(t_renderer *r)
{
	time_diff(&r->text_tick, &r->tick,
		&r->temp);
	if (r->temp.tv_sec >= 1)
	{
		time_diff(&r->last_tick, &r->tick,
			&r->temp);
		r->temp.tv_nsec += r->temp.tv_sec * 1000000000L;
		r->fps = 1000000000L / r->temp.tv_nsec ;
		r->text_tick = r->tick;
	}
	if (r->fps / 1000 == 0)
		r->fps_string[5] = ' ';
	else
		r->fps_string[5] = (r->fps / 1000) + '0';
	r->fps_string[6] = (r->fps / 100) % 10 + '0';
	r->fps_string[7] = (r->fps / 10) % 10 + '0';
	r->fps_string[8] = r->fps % 10 + '0';
	r->last_tick = r->tick;
}
