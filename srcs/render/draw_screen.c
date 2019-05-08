/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <smerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 00:15:17 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/08 11:21:27 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	transform_vertex(t_b *b, t_bas *bas)
{
	bas->vx1 = bas->sect.vertex[bas->s + 0].x - b->player.where.x;
	bas->vy1 = bas->sect.vertex[bas->s + 0].y - b->player.where.y;
	bas->vx2 = bas->sect.vertex[bas->s + 1].x - b->player.where.x;
	bas->vy2 = bas->sect.vertex[bas->s + 1].y - b->player.where.y;
	bas->pcos = b->player.anglecos;
	bas->psin = b->player.anglesin;
	bas->tx1 = bas->vx1 * bas->psin - bas->vy1 * bas->pcos;
	bas->tz1 = bas->vx1 * bas->pcos + bas->vy1 * bas->psin;
	bas->tx2 = bas->vx2 * bas->psin - bas->vy2 * bas->pcos;
	bas->tz2 = bas->vx2 * bas->pcos + bas->vy2 * bas->psin;
	bas->ttx1 = bas->tx1;
	bas->ttx2 = bas->tx2;
	bas->ttz1 = bas->tz1;
	bas->ttz2 = bas->tz2;
}

void	into_screen(t_b *b, t_bas *bas)
{
	float p;

	p = b->player.yaw;
	bas->yceil = bas->sect.ceil - b->player.where.z;
	bas->yfloor = bas->sect.floor - b->player.where.z;
	bas->neighbor = bas->sect.neighbors[bas->s];
	bas->nyceil = 0;
	bas->nyfloor = 0;
	if (bas->neighbor >= 0)
	{
		bas->nyceil = b->sectors[bas->neighbor].ceil - b->player.where.z;
		bas->nyfloor = b->sectors[bas->neighbor].floor - b->player.where.z;
	}
	bas->y1a = SH / 2 - (int)(yaw(bas->yceil, bas->tz1, p) * bas->yscale1);
	bas->y1b = SH / 2 - (int)(yaw(bas->yfloor, bas->tz1, p) * bas->yscale1);
	bas->y2a = SH / 2 - (int)(yaw(bas->yceil, bas->tz2, p) * bas->yscale2);
	bas->y2b = SH / 2 - (int)(yaw(bas->yfloor, bas->tz2, p) * bas->yscale2);
	bas->ny1a = SH / 2 - (int)(yaw(bas->nyceil, bas->tz1, p) * bas->yscale1);
	bas->ny1b = SH / 2 - (int)(yaw(bas->nyfloor, bas->tz1, p) * bas->yscale1);
	bas->ny2a = SH / 2 - (int)(yaw(bas->nyceil, bas->tz2, p) * bas->yscale2);
	bas->ny2b = SH / 2 - (int)(yaw(bas->nyfloor, bas->tz2, p) * bas->yscale2);
	bas->beginx = max(bas->x1, bas->now.sx1);
	bas->endx = min(bas->x2, bas->now.sx2);
	bas->x = bas->beginx;
}

void	draw_neighbor(t_data *data, t_bas *bas, t_rv *rv)
{
	if (bas->neighbor >= 0)
	{
		bas->nya = (bas->x - bas->x1)
		* (bas->ny2a - bas->ny1a) / (bas->x2 - bas->x1) + bas->ny1a;
		bas->cnya = clamp(bas->nya, bas->ytop[bas->x], bas->ybottom[bas->x]);
		bas->nyb = (bas->x - bas->x1)
		* (bas->ny2b - bas->ny1b) / (bas->x2 - bas->x1) + bas->ny1b;
		bas->cnyb = clamp(bas->nyb, bas->ytop[bas->x], bas->ybottom[bas->x]);
		bas->r1 = luminosity(bas->r1, bas->z, data->luminosity);
		bas->r2 = bas->r1;
		recycle_vline(bas, rv);
		vline(data, rv);
		bas->ytop[bas->x] = clamp(max(bas->cya, bas->cnya)
		, bas->ytop[bas->x], SH - 1);
		recycle_vline2(bas, rv);
		vline(data, rv);
		bas->ybottom[bas->x] = clamp(min(bas->cyb
		, bas->cnyb), 0, bas->ybottom[bas->x]);
	}
	else
	{
		recycle_vline21(bas, rv);
		vline2(data, bas, rv);
	}
}

int		init_draw_queue(t_data *data, t_bas *bas)
{
	bas->i = 0;
	bas->now = *bas->tail;
	data->now_sect = bas->now.sectorno;
	if (++bas->tail == bas->queue + 32)
		bas->tail = bas->queue;
	if (bas->i < data->numsectors)
	{
		data->sectqueue[bas->now.sectorno] = bas->i;
		bas->i++;
	}
	return (0);
}

void	draw_screen(t_data *data, t_b *b)
{
	t_bas bas;

	bas = init_draw_vars(data, b, &bas);
	while (bas.head != bas.tail)
	{
		bas.i = -1;
		init_draw_queue(data, &bas);
		if (bas.renderedsectors[bas.now.sectorno] & 0x21)
			continue;
		++bas.renderedsectors[bas.now.sectorno];
		bas.sect = b->sectors[bas.now.sectorno];
		bas.s = -1;
		while (++bas.i < data->sprite_nbr)
			data->sprite[bas.i].x_count = 0;
		while_edges(&bas, data, b);
		++bas.renderedsectors[bas.now.sectorno];
	}
}
