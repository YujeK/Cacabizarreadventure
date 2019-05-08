/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_in_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 02:38:31 by smerelo           #+#    #+#             */
/*   Updated: 2019/05/08 23:12:40 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	scale_coords(t_bas *bas)
{
	bas->xscale1 = HFOV / bas->tz1;
	bas->yscale1 = VFOV / bas->tz1;
	bas->x1 = SCREEN_WIDTH / 2 - (int)(bas->tx1 * bas->xscale1);
	bas->xscale2 = HFOV / bas->tz2;
	bas->yscale2 = VFOV / bas->tz2;
	bas->x2 = SCREEN_WIDTH / 2 - (int)(bas->tx2 * bas->xscale2);
}

void	clamp_coords(t_bas *bas, t_data *data)
{
	data->x_draw = bas->x;
	bas->z = ((bas->x - bas->x1) *
	(bas->tz2 - bas->tz1) / (bas->x2 - bas->x1) + bas->tz1) * 8;
	bas->ya = (bas->x - bas->x1) *
	(bas->y2a - bas->y1a) / (bas->x2 - bas->x1) + bas->y1a;
	bas->cya = clamp(bas->ya, bas->ytop[bas->x], bas->ybottom[bas->x]);
	bas->yb = (bas->x - bas->x1) *
	(bas->y2b - bas->y1b) / (bas->x2 - bas->x1) + bas->y1b;
	bas->cyb = clamp(bas->yb, bas->ytop[bas->x], bas->ybottom[bas->x]);
	bas->i = -1;
}

void	draw_edges(t_bas *bas, t_data *data, t_b *b)
{
	t_rv rv;

	while (++bas->x <= bas->endx)
	{
		clamp_coords(bas, data);
		while (++bas->i < data->sprite_nbr)
		{
			if (data->sectqueue[data->sprite[bas->i].sectorno]
			<= data->sectqueue[data->now_sect]
			&& data->sprite[bas->i].status != 2
			&& data->sectqueue[data->sprite[bas->i].sectorno] != -1)
				data->sprite[bas->i] = get_sprite_coords(data,
			&data->sprite[bas->i], b, bas);
		}
		recycle_vline3(bas, &rv);
		vline(data, &rv);
		recycle_vline4(bas, &rv);
		vline(data, &rv);
		draw_neighbor(data, bas, &rv);
	}
}

void	while_edges(t_bas *bas, t_data *data, t_b *b)
{
	while (++bas->s < (int)bas->sect.npoints)
	{
		transform_vertex(b, bas);
		if (bas->tz1 <= 0 && bas->tz2 <= 0)
			continue;
		init_intersect_vars2(bas);
		scale_coords(bas);
		if (bas->x1 >= bas->x2
		|| bas->x2 < bas->now.sx1 || bas->x1 > bas->now.sx2)
			continue;
		into_screen(b, bas);
		draw_edges(bas, data, b);
		if (bas->neighbor >= 0 && bas->endx >= bas->beginx
		&& (bas->head + 32 + 1 - bas->tail) % 32)
		{
			*bas->head = (t_item){bas->neighbor, bas->beginx, bas->endx};
			if (++bas->head == bas->queue + 32)
				bas->head = bas->queue;
		}
	}
}
