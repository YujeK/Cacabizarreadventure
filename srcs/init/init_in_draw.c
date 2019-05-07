/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_in_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 02:38:31 by smerelo           #+#    #+#             */
/*   Updated: 2019/05/07 12:42:41 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void scale_coords(t_bas *bas)
{
    bas->xscale1 = hfov / bas->tz1;
    bas->yscale1 = vfov / bas->tz1;
    bas->x1 = SCREEN_WIDTH / 2 - (int)(bas->tx1 * bas->xscale1);
    bas->xscale2 = hfov / bas->tz2;
    bas->yscale2 = vfov / bas->tz2;
    bas->x2 = SCREEN_WIDTH / 2 - (int)(bas->tx2 * bas->xscale2);
}

void clamp_coords(t_bas *bas, t_data *data)
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

void	recycle_vline3(t_bas *bas, t_rv *rv)
{
	rv->x = bas->x;
	rv->y1 = bas->ytop[bas->x];
	rv->y2 = bas->cya - 1;
	rv->top = 0x111111;
	rv->middle = 0x3f3f3f;
	rv->bottom = 0x111111;
}

void	recycle_vline4(t_bas *bas, t_rv *rv)
{
	rv->x = bas->x;
	rv->y1 =  bas->cyb + 1;
	rv->y2 = bas->ybottom[bas->x];
	rv->top = 0x992c42;
	rv->middle = 0x6b3636;
	rv->bottom = 0x992c42;
}

void draw_edges(t_bas *bas, t_data *data, t_b *b)
{
	t_rv rv;
    while (++bas->x <= bas->endx)
    {
        clamp_coords(bas, data);
        while (++bas->i < data->sprite_nbr)
        {
            if (data->sectqueue[data->sprite[bas->i].sectorno]
            <= data->sectqueue[data->now_sect] &&
            data->sprite[bas->i].status != 2 &&
            data->sectqueue[data->sprite[bas->i].sectorno] != -1)
            data->sprite[bas->i] = get_sprite_coords(data, &data->sprite[bas->i], &b->player, b->sectors, bas->ytop[bas->x], bas->ybottom[bas->x]);
        }
		recycle_vline3(bas, &rv);
        vline(data, bas, &rv);
		recycle_vline4(bas, &rv);
        vline(data, bas, &rv);
        draw_neighbor(data, b, bas);
    }
}

void while_edges(t_bas *bas, t_data *data, t_b *b)
{
    while (++bas->s < bas->sect.npoints)
    {
        transform_vertex(data, b, bas);
        if (bas->tz1 <= 0 && bas->tz2 <= 0)
            continue;
        init_intersect_vars2(data, b, bas);
        scale_coords(bas);
        if (bas->x1 >= bas->x2 || bas->x2 < bas->now.sx1 || bas->x1 > bas->now.sx2)
            continue;
        into_screen(data, b, bas);
        draw_edges(bas, data, b);
        if (bas->neighbor >= 0 && bas->endx >= bas->beginx && (bas->head + 32 + 1 - bas->tail) % 32)
        {
            *bas->head = (t_item){bas->neighbor, bas->beginx, bas->endx};
            if (++bas->head == bas->queue + 32)
                bas->head = bas->queue;
        }
    }
}
