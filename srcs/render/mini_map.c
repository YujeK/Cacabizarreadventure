/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 19:59:28 by smerelo           #+#    #+#             */
/*   Updated: 2019/05/07 05:27:29 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ui_draw_vector(t_wind wind,
			t_coord vtx, float angle, float start, float size)
{
	float	step_x;
	float	step_y;
	t_coord	vtx_a;
	t_coord	vtx_b;
	t_line	line;

	step_x = cos(angle) * start;
	step_y = sin(angle) * start;
	vtx_a.x = vtx.x + step_x;
	vtx_a.y = vtx.y + step_y;
	step_x = cos(angle) * size;
	step_y = sin(angle) * size;
	vtx_b.x = vtx.x + step_x;
	vtx_b.y = vtx.y + step_y;
	line.color = 0x700000;
	ft_draw_line3(wind, vtx_a, vtx_b, line);
}

void	draw_player(t_plyr player, t_wind wind)
{
	int		x;
	int		y;
	t_coord coord = (t_coord){
		player.where.x * 5 + 200,
		player.where.y * 5 + 10};

	y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 5)
		{
			if (player.where.x + x * 5 + 749 < 0 || player.where.x + x * 5 + 749 > SCREEN_WIDTH
			|| player.where.y + y  * 5 + 10 < 0 || player.where.y + y  * 5 + 10 > SCREEN_HEIGHT)
				break ;
			put_pixel32(wind.screen, player.where.x * 5 + 200 + x - 2.5,
			player.where.y * 5 + 10 + y - 2.5, 0x700000);
			x++;
		}
		y++;
	}

	ui_draw_vector(wind, coord, player.angle, 0, 50);
}

void	draw_sprites(t_data *data, t_wind wind)
{
	int x;
	int y;
	int i;

	i = -1;
	y = 0;
	while (++i < data->sprite_nbr)
	{
		if (data->sprite[i].status != 2)
		{
			y = 0;
			while (y < 5)
			{
				x = 0;
				while (x < 5)
				{
					if (data->sprite[i].where.x + x * 5 + 749 < 0 || data->sprite[i].where.x + x * 5 + 749 > SCREEN_WIDTH || data->sprite[i].where.y + y * 5 + 10 < 0 || data->sprite[i].where.y + y * 5 + 10 > SCREEN_HEIGHT)
						break;
					put_pixel32(wind.screen, data->sprite[i].where.x * 5 + 200 + x - 2.5,
								data->sprite[i].where.y * 5 + 10 + y - 2.5, BLUE);
					x++;
				}
				y++;
			}
		}
	}
}

void	fillrect(SDL_Rect rect, int color, t_wind wind)
{
	int x;
	int y;
	y = 0;
	while (y < rect.h)
	{
		x = 0;
		while (x < rect.w)
		{
			if (rect.x + x < 0 || rect.x + x > SCREEN_HEIGHT
			|| rect.y + y < 0 || rect.y + y > SCREEN_WIDTH)
				break ;
			put_pixel32(wind.screen, rect.x + x, rect.y + y, color + 0xA0000000);
			x++;
		}
		y++;
	}
}

void	draw_map(t_b *b, t_data *data)
{
	unsigned int	i;
	unsigned int	j;
	t_coord			point;
	t_coord			next_point;
	t_line			line;
	SDL_Rect		rect;

	line.color = 0x285091;
	i = 0;
	rect.h = 248;
	rect.w = 247;
	rect.x = 749;
	rect.y = 0;
	fillrect(rect, 0x2a303a, data->wind);
	while (i < b->NumSectors)
	{
		j = 0;
		while (j < b->sectors[i].npoints)
		{
			if (b->sectors[i].neighbors[j] == -1)
			{
				point.x = b->sectors[i].vertex[j].x * 5 + 200;
				point.y = b->sectors[i].vertex[j].y * 5;
				next_point.x = b->sectors[i].vertex[j + 1].x * 5 + 200;
				next_point.y = b->sectors[i].vertex[j + 1].y * 5;
				ft_draw_line3(data->wind, point, next_point, line);
			}
			j++;
		}
		i++;
	}
	draw_player(b->player, data->wind);
	draw_sprites(data, data->wind);
}
