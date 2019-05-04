/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 00:15:17 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/04 12:37:29 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void draw_screen(t_data *data, t_plyr *player, t_sector *sectors, unsigned int NumSectors)
{
	t_item queue[32];
	t_item *head;
	t_item *tail;
	t_item now;
	head = queue;
	tail = queue;
	int	sectqueue[33];
	int ytop[SCREEN_WIDTH] = {0};
	int ybottom[SCREEN_WIDTH];
	int renderedsectors[25];
	int i;
	t_sector sect;
	int x;
	int pixel;
	int s;
	int y1a;
	int y2a;
	int ny1a;
	int ny2a;
	int beginx;
	int y1b;
	int y2b;
	int ny1b;
	int ny2b;
	int endx;
	int x1;
	int x2;
	int z;
	int ya;
	int yb;
	int cya;
	int nya;
	int nyb;
	int cyb;
	int cnya;
	int cnyb;
	float vx1;
	float vy1;
	float vx2;
	float vy2;
	float pcos;
	float psin;
	float tx1;
	float tx2;
	float tz1;
	float tz2;
	float ttx1;
	float ttx2;
	float ttz1;
	float ttz2;
	float nearz;
	float farz;
	float nearside;
	float farside;
	float xscale1;
	float xscale2;
	float yscale1;
	float yscale2;
	float yceil;
	float yfloor;
	float nyceil;
	float nyfloor;
	float ratio;
	float width;
	float float_x;
	float to_intersection;
	float to_end;
	float point_in_image;
	t_vector intersection;
	int neighbor;
	unsigned int r;
	unsigned int r1;
	unsigned int r2;
	t_vector i1;
	t_vector i2;
	unsigned int *img;
	unsigned int *res_img;
	t_tga specs;
	float dist;

	pixel = 0;
	x = 0;
	data->sprite = sprite_size(data->sprite, *player, *data);
	i = 0;
	while(i < 32)
	{
		data->sectqueue[i] = 100;
		i++;
	}
	i = 0;
	while (x < SCREEN_HEIGHT)
	{
		ybottom[x] = SCREEN_HEIGHT - 1;
		x++;
	}
	x = 0;
	while (x < NumSectors)
	{
		renderedsectors[x] = 0;
		x++;
	}
	head->sectorno = player->sector;
	head->sx1 = 0;
	head->sx2 = SCREEN_WIDTH - 1;
	if (++head == queue + 32)
		head = queue;
	while (head != tail)
	{
		now = *tail;
		data->now_sect = now.sectorno;
		if (++tail == queue + 32)
			tail = queue;
		if(i < NumSectors /* && data->sectqueue[now.sectorno] == 100 */)
		{
			data->sectqueue[now.sectorno] = i;
			i++;
		}
		if (renderedsectors[now.sectorno] & 0x21)
			continue;
		++renderedsectors[now.sectorno];
		sect = sectors[now.sectorno];
		s = -1;
		i = -1;
		while(++i < data->sprite_nbr)
			data->sprite[i].x_count = 0;
		while (++s < sect.npoints)
		{
			vx1 = sect.vertex[s + 0].x - player->where.x;
			vy1 = sect.vertex[s + 0].y - player->where.y;
			vx2 = sect.vertex[s + 1].x - player->where.x;
			vy2 = sect.vertex[s + 1].y - player->where.y;
			//dist = sqrt(pow(vx1 - player.where.x, 2) + pow(vy1 - player.where.y, 2));
			pcos = player->anglecos, psin = player->anglesin;
			tx1 = vx1 * psin - vy1 * pcos;
			tz1 = vx1 * pcos + vy1 * psin;
			tx2 = vx2 * psin - vy2 * pcos;
			tz2 = vx2 * pcos + vy2 * psin;
			ttx1 = tx1;
			ttx2 = tx2;
			ttz1 = tz1;
			ttz2 = tz2;
			if (tz1 <= 0 && tz2 <= 0)
				continue;
			if (tz1 <= 0 || tz2 <= 0)
			{
				nearz = 1e-4f;
				farz = 5;
				nearside = 1e-5f;
				farside = 20.f;
				i1 = Intersect(tx1, tz1, tx2, tz2, -nearside, nearz, -farside, farz);
				i2 = Intersect(tx1, tz1, tx2, tz2, nearside, nearz, farside, farz);
				if (tz1 < nearz)
				{
					if (i1.y > 0)
					{
						tx1 = i1.x;
						tz1 = i1.y;
					}
					else
					{
						tx1 = i2.x;
						tz1 = i2.y;
					}
				}
				if (tz2 < nearz)
				{
					if (i1.y > 0)
					{
						tx2 = i1.x;
						tz2 = i1.y;
					}
					else
					{
						tx2 = i2.x;
						tz2 = i2.y;
					}
				}
			}
			xscale1 = hfov / tz1;
			yscale1 = vfov / tz1;
			x1 = SCREEN_WIDTH / 2 - (int)(tx1 * xscale1);
			xscale2 = hfov / tz2;
			yscale2 = vfov / tz2;
			x2 = SCREEN_WIDTH / 2 - (int)(tx2 * xscale2);
			if (x1 >= x2 || x2 < now.sx1 || x1 > now.sx2)
				continue;
			yceil = sect.ceil - player->where.z;
			yfloor = sect.floor - player->where.z;
			neighbor = sect.neighbors[s];
			nyceil = 0;
			nyfloor = 0;
			if (neighbor >= 0)
			{
				nyceil = sectors[neighbor].ceil - player->where.z;
				nyfloor = sectors[neighbor].floor - player->where.z;
			}
			y1a = SCREEN_HEIGHT / 2 - (int)(yaw(yceil, tz1, player->yaw) * yscale1);
			y1b = SCREEN_HEIGHT / 2 - (int)(yaw(yfloor, tz1, player->yaw) * yscale1);
			y2a = SCREEN_HEIGHT / 2 - (int)(yaw(yceil, tz2, player->yaw) * yscale2);
			y2b = SCREEN_HEIGHT / 2 - (int)(yaw(yfloor, tz2, player->yaw) * yscale2);
			ny1a = SCREEN_HEIGHT / 2 - (int)(yaw(nyceil, tz1, player->yaw) * yscale1);
			ny1b = SCREEN_HEIGHT / 2 - (int)(yaw(nyfloor, tz1, player->yaw) * yscale1);
			ny2a = SCREEN_HEIGHT / 2 - (int)(yaw(nyceil, tz2, player->yaw) * yscale2);
			ny2b = SCREEN_HEIGHT / 2 - (int)(yaw(nyfloor, tz2, player->yaw) * yscale2);
			beginx = max(x1, now.sx1), endx = min(x2, now.sx2);
			x = beginx;
			while( ++x <= endx)
			{
				data->x_draw = x;
				z = ((x - x1) * (tz2 - tz1) / (x2 - x1) + tz1) * 8;
				ya = (x - x1) * (y2a - y1a) / (x2 - x1) + y1a;
				cya = clamp(ya, ytop[x], ybottom[x]);
				yb = (x - x1) * (y2b - y1b) / (x2 - x1) + y1b;
				cyb = clamp(yb, ytop[x], ybottom[x]);
				i = -1;
				while(++i < data->sprite_nbr)
				{
					if(data->sectqueue[data->sprite[i].sectorno] <= data->sectqueue[data->now_sect] && data->sprite[i].status != 2)
						data->sprite[i] = get_sprite_coords(data, &data->sprite[i], player, sectors, ytop[x], ybottom[x]);
				}
				vline(data, x, ytop[x], cya - 1, 0x111111, 0x3f3f3f, 0x111111, data->wind.screen, res_img);
				vline(data, x, cyb + 1, ybottom[x], 0x992c42, 0x6b3636, 0x992c42, data->wind.screen, res_img);
				if (neighbor >= 0)
				{
					nya = (x - x1) * (ny2a - ny1a) / (x2 - x1) + ny1a;
					cnya = clamp(nya, ytop[x], ybottom[x]);
					nyb = (x - x1) * (ny2b - ny1b) / (x2 - x1) + ny1b;
					cnyb = clamp(nyb, ytop[x], ybottom[x]);
					r1 = luminosity(r1, z, data->luminosity);
					r2 = r1;
					vline(data, x, cya, cnya - 1, 0, x == x1 || x == x2 ? 0 : r1, 0, data->wind.screen, res_img);
					ytop[x] = clamp(max(cya, cnya), ytop[x], SCREEN_HEIGHT - 1);
					vline(data, x, cnyb + 1, cyb, 0, x == x1 || x == x2 ? 0 : r2, 0, data->wind.screen, res_img);
					ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]);/*
					if(data->sectqueue[data->sprite[0].sectorno] <= data->sectqueue[data->now_sect])
						data->sprite = get_sprite_coords(data, player, sectors, ytop[x], ybottom[x]); */
				}
				else
				{
					r = luminosity(r, z, data->luminosity);
					point_in_image = ratio * 600;
					//vline2(point_in_image, x, cya, cyb, 0, x == x1 || x == x2 ? 0 : r, 0, data->wind.screen, res_img, ya, yb);
					vline(data, x, cya, cyb, 0, x == x1 || x == x2 ? 0 : r, 0, data->wind.screen, res_img);
				}
			}
			if (neighbor >= 0 && endx >= beginx && (head + 32 + 1 - tail) % 32)
			{
				*head = (t_item){neighbor, beginx, endx};
				if (++head == queue + 32)
					head = queue;
			}
		}
		++renderedsectors[now.sectorno];
	}
}
