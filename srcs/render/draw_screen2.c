/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 00:15:17 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/07 08:24:01 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void draw_screen(t_data *data, t_plyr *player, t_sector *sectors, unsigned int NumSectors, t_b *b)
{
	int ytop[SCREEN_WIDTH] = {0};
	t_bas bas;
	bas.head = bas.queue;
	bas.tail = bas.queue;
	bas.x = 0;
	data->sprite = sprite_size(data->sprite, *player, *data, b);
	bas.i = 0;
	while(bas.i < 32)
	{
		data->sectqueue[bas.i] = -1;
		bas.i++;
	}
	bas.i = 0;
	while (bas.x < SH)
	{
		bas.ybottom[bas.x] = SH - 1;
		bas.x++;
	}
	bas.x = 0;
	while (bas.x < NumSectors)
	{
		bas.renderedsectors[bas.x] = 0;
		bas.x++;
	}
	bas.head->sectorno = player->sector;
	bas.head->sx1 = 0;
	bas.head->sx2 = SCREEN_WIDTH - 1;
	if (++bas.head == bas.queue + 32)
		bas.head = bas.queue;
	while (bas.head != bas.tail)
	{
		bas.i = 0;
		bas.now = *bas.tail;
		data->now_sect = bas.now.sectorno;
		if (++bas.tail == bas.queue + 32)
			bas.tail = bas.queue;
		if(bas.i < NumSectors)
		{
			data->sectqueue[bas.now.sectorno] = bas.i;
			bas.i++;
		}
		if (bas.renderedsectors[bas.now.sectorno] & 0x21)
			continue;
		++bas.renderedsectors[bas.now.sectorno];
		bas.sect = sectors[bas.now.sectorno];
		bas.s = -1;
		bas.i = -1;
		while(++bas.i < data->sprite_nbr)
			data->sprite[bas.i].x_count = 0;
		while (++bas.s < bas.sect.npoints)
		{
			bas.vx1 = bas.sect.vertex[bas.s + 0].x - player->where.x;
			bas.vy1 = bas.sect.vertex[bas.s + 0].y - player->where.y;
			bas.vx2 = bas.sect.vertex[bas.s + 1].x - player->where.x;
			bas.vy2 = bas.sect.vertex[bas.s + 1].y - player->where.y;
			//dist = sqrt(pow(bas.vx1 - player.where.x, 2) + pow(bas.vy1 - player.where.y, 2));
			bas.pcos = player->anglecos, bas.psin = player->anglesin;
			bas.tx1 = bas.vx1 * bas.psin - bas.vy1 * bas.pcos;
			bas.tz1 = bas.vx1 * bas.pcos + bas.vy1 * bas.psin;
			bas.tx2 = bas.vx2 * bas.psin - bas.vy2 * bas.pcos;
			bas.tz2 = bas.vx2 * bas.pcos + bas.vy2 * bas.psin;
			bas.ttx1 = bas.tx1;
			bas.ttx2 = bas.tx2;
			bas.ttz1 = bas.tz1;
			bas.ttz2 = bas.tz2;
			if (bas.tz1 <= 0 && bas.tz2 <= 0)
				continue;
			if (bas.tz1 <= 0 || bas.tz2 <= 0)
			{
				bas.nearz = 1e-4f;
				bas.farz = 5;
				bas.nearside = 1e-5f;
				bas.farside = 20.f;
				bas.i1 = Intersect(bas.tx1, bas.tz1, bas.tx2, bas.tz2, -bas.nearside, bas.nearz, -bas.farside, bas.farz);
				bas.i2 = Intersect(bas.tx1, bas.tz1, bas.tx2, bas.tz2, bas.nearside, bas.nearz, bas.farside, bas.farz);
				if (bas.tz1 < bas.nearz)
				{
					if (bas.i1.y > 0)
					{
						bas.tx1 = bas.i1.x;
						bas.tz1 = bas.i1.y;
					}
					else
					{
						bas.tx1 = bas.i2.x;
						bas.tz1 = bas.i2.y;
					}
				}
				if (bas.tz2 < bas.nearz)
				{
					if (bas.i1.y > 0)
					{
						bas.tx2 = bas.i1.x;
						bas.tz2 = bas.i1.y;
					}
					else
					{
						bas.tx2 = bas.i2.x;
						bas.tz2 = bas.i2.y;
					}
				}
			}
			bas.xscale1 = hfov / bas.tz1;
			bas.yscale1 = vfov / bas.tz1;
			bas.x1 = SCREEN_WIDTH / 2 - (int)(bas.tx1 * bas.xscale1);
			bas.xscale2 = hfov / bas.tz2;
			bas.yscale2 = vfov / bas.tz2;
			bas.x2 = SCREEN_WIDTH / 2 - (int)(bas.tx2 * bas.xscale2);
			if (bas.x1 >= bas.x2 || bas.x2 < bas.now.sx1 || bas.x1 > bas.now.sx2)
				continue;
			bas.yceil = bas.sect.ceil - player->where.z;
			bas.yfloor = bas.sect.floor - player->where.z;
			bas.neighbor = bas.sect.neighbors[bas.s];
			bas.nyceil = 0;
			bas.nyfloor = 0;
			if (bas.neighbor >= 0)
			{
				bas.nyceil = sectors[bas.neighbor].ceil - player->where.z;
				bas.nyfloor = sectors[bas.neighbor].floor - player->where.z;
			}
			bas.y1a = SH / 2 - (int)(yaw(bas.yceil, bas.tz1, player->yaw) * bas.yscale1);
			bas.y1b = SH / 2 - (int)(yaw(bas.yfloor, bas.tz1, player->yaw) * bas.yscale1);
			bas.y2a = SH / 2 - (int)(yaw(bas.yceil, bas.tz2, player->yaw) * bas.yscale2);
			bas.y2b = SH / 2 - (int)(yaw(bas.yfloor, bas.tz2, player->yaw) * bas.yscale2);
			bas.ny1a = SH / 2 - (int)(yaw(bas.nyceil, bas.tz1, player->yaw) * bas.yscale1);
			bas.ny1b = SH / 2 - (int)(yaw(bas.nyfloor, bas.tz1, player->yaw) * bas.yscale1);
			bas.ny2a = SH / 2 - (int)(yaw(bas.nyceil, bas.tz2, player->yaw) * bas.yscale2);
			bas.ny2b = SH / 2 - (int)(yaw(bas.nyfloor, bas.tz2, player->yaw) * bas.yscale2);
			bas.beginx = max(bas.x1, bas.now.sx1), bas.endx = min(bas.x2, bas.now.sx2);
			bas.x = bas.beginx;
			while( ++bas.x <= bas.endx)
			{
				data->x_draw = bas.x;
				bas.z = ((bas.x - bas.x1) * (bas.tz2 - bas.tz1) / (bas.x2 - bas.x1) + bas.tz1) * 8;
				bas.ya = (bas.x - bas.x1) * (bas.y2a - bas.y1a) / (bas.x2 - bas.x1) + bas.y1a;
				bas.cya = clamp(bas.ya, ytop[bas.x], bas.ybottom[bas.x]);
				bas.yb = (bas.x - bas.x1) * (bas.y2b - bas.y1b) / (bas.x2 - bas.x1) + bas.y1b;
				bas.cyb = clamp(bas.yb, ytop[bas.x], bas.ybottom[bas.x]);
				bas.i = -1;
				while(++bas.i < data->sprite_nbr)
				{
					if(data->sectqueue[data->sprite[bas.i].sectorno] <= data->sectqueue[data->now_sect] && data->sprite[bas.i].status != 2 && data->sectqueue[data->sprite[bas.i].sectorno] != -1)
							data->sprite[bas.i] = get_sprite_coords(data, &data->sprite[bas.i], player, sectors, ytop[bas.x], bas.ybottom[bas.x]);
				}
				vline(data, bas.x, ytop[bas.x], bas.cya - 1, 0x111111, 0x3f3f3f, 0x111111, data->wind.screen, bas.res_img, -1);
				vline(data, bas.x, bas.cyb + 1, bas.ybottom[bas.x], 0x992c42, 0x6b3636, 0x992c42, data->wind.screen, bas.res_img, -1);
				if (bas.neighbor >= 0)
				{
					bas.nya = (bas.x - bas.x1) * (bas.ny2a - bas.ny1a) / (bas.x2 - bas.x1) + bas.ny1a;
					bas.cnya = clamp(bas.nya, ytop[bas.x], bas.ybottom[bas.x]);
					bas.nyb = (bas.x - bas.x1) * (bas.ny2b - bas.ny1b) / (bas.x2 - bas.x1) + bas.ny1b;
					bas.cnyb = clamp(bas.nyb, ytop[bas.x], bas.ybottom[bas.x]);
					bas.r1 = luminosity(bas.r1, bas.z, data->luminosity);
					bas.r2 = bas.r1;
					vline(data, bas.x, bas.cya, bas.cnya - 1, 0, bas.x == bas.x1 || bas.x == bas.x2 ? 0 : bas.r1, 0, data->wind.screen, bas.res_img, -1);
					ytop[bas.x] = clamp(max(bas.cya, bas.cnya), ytop[bas.x], SH - 1);
					vline(data, bas.x, bas.cnyb + 1, bas.cyb, 0, bas.x == bas.x1 || bas.x == bas.x2 ? 0 : bas.r2, 0, data->wind.screen, bas.res_img, -1);
					//vline2(500, bas.x, bas.cnyb + 1, bas.cyb, 0, bas.x == bas.x1 || bas.x == bas.x2 ? 0 : bas.r2, 0, data->wind.screen, data->pepo.img, bas.ya, bas.yb);
					bas.ybottom[bas.x] = clamp(min(bas.cyb, bas.cnyb), 0, bas.ybottom[bas.x]);/*
					if(data->sectqueue[data->sprite[0].sectorno] <= data->sectqueue[data->now_sect])
						data->sprite = get_sprite_coords(data, player, sectors, ytop[bas.x], bas.ybottom[bas.x]); */
				}
				else
				{
					//bas.r = luminosity(bas.r, bas.z, data->luminosity);
					//bas.point_in_image = bas.ratio * 600;
					vline2(500, bas.x, bas.cya, bas.cyb, 0, bas.x == bas.x1 || bas.x == bas.x2 ? 0 : bas.r, 0, data->wind.screen, data->pepo.img, bas.ya, bas.yb);
					//vline(data, bas.x, bas.cya, bas.cyb, 0, bas.x == bas.x1 || bas.x == bas.x2 ? 0 : bas.r, 0, data->wind.screen, bas.res_img, bas.now.sectorno);
				}
			}
			if (bas.neighbor >= 0 && bas.endx >= bas.beginx && (bas.head + 32 + 1 - bas.tail) % 32)
			{
				*bas.head = (t_item){bas.neighbor, bas.beginx, bas.endx};
				if (++bas.head == bas.queue + 32)
					bas.head = bas.queue;
			}
		}
		++bas.renderedsectors[bas.now.sectorno];
	}
}
