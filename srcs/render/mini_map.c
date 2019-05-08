/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 19:59:28 by smerelo           #+#    #+#             */
/*   Updated: 2019/05/08 11:27:13 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ui_draw_vector(t_wind wind,
			t_coord vtx, float angle)
{
	float	step_x;
	float	step_y;
	t_coord	vtx_a;
	t_coord	vtx_b;
	t_line	line;

	step_x = cos(angle) * 0;
	step_y = sin(angle);
	vtx_a.x = vtx.x + step_x;
	vtx_a.y = vtx.y + step_y;
	step_x = cos(angle) * 30;
	step_y = sin(angle) * 30;
	vtx_b.x = vtx.x + step_x;
	vtx_b.y = vtx.y + step_y;
	line.color = RED;
	ft_draw_line3(wind, vtx_a, vtx_b, line);
}

void	draw_player(t_plyr player, t_wind wind)
{
	int		x;
	int		y;
	t_coord	coord;

	coord = (t_coord){
		player.where.x * 5 + 200,
		player.where.y * 5 + 10};
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (player.where.x + x * 5 + 749 < 0
				|| player.where.x + x * 5 + 749 > SCREEN_WIDTH
				|| player.where.y + y * 5 + 10 < 0
				|| player.where.y + y * 5 + 10 > SH)
				break ;
			put_pixel32(wind.screen, player.where.x * 5 + 200 + x - 2.5,
			player.where.y * 5 + 10 + y - 2.5, RED);
			x++;
		}
		y++;
	}
	ui_draw_vector(wind, coord, player.angle);
}

void	draw_sprites(t_data *data, t_wind wind, t_b *b)
{
	int i;

	i = -1;
	while (++i < data->sprite_nbr)
	{
		if (data->sprite[i].status != 2)
		{
			b->y = -1;
			while (++b->y < 5)
			{
				b->x = -1;
				while (++b->x < 5)
				{
					if (data->sprite[i].where.x + b->x * 5 + 749 < 0
					|| data->sprite[i].where.x + b->x * 5 + 749 > SCREEN_WIDTH
					|| data->sprite[i].where.y + b->y * 5 + 10 < 0
					|| data->sprite[i].where.y + b->y * 5 + 10 > SH)
						break ;
					put_pixel32(wind.screen,
						data->sprite[i].where.x * 5 + 200 + b->x - 2.5,
						data->sprite[i].where.y * 5 + 10 + b->y - 2.5, GREEN);
				}
			}
		}
	}
}

void	fillrect(SDL_Rect rect, t_wind wind)
{
	int x;
	int y;

	y = 0;
	while (y < rect.h)
	{
		x = 0;
		while (x < rect.w)
		{
			if (rect.x + x < 0 || rect.x + x > SH
			|| rect.y + y < 0 || rect.y + y > SCREEN_WIDTH)
				break ;
			put_pixel32(wind.screen,
				rect.x + x, rect.y + y, RED + 0xA0000000);
			x++;
		}
		y++;
	}
}

void	draw_map(t_b *b, t_data *data)
{
	b->line.color = 0;
	b->i = 0;
	while (b->i < (int)b->numsectors)
	{
		b->j = 0;
		while (b->j < (int)b->sectors[b->i].npoints)
		{
			if (b->sectors[b->i].neighbors[b->j] == -1)
			{
				b->point.x = b->sectors[b->i].vertex[b->j].x * 5 + 200;
				b->point.y = b->sectors[b->i].vertex[b->j].y * 5;
				b->next_point.x = b->sectors[b->i].vertex[b->j + 1].x * 5 + 200;
				b->next_point.y = b->sectors[b->i].vertex[b->j + 1].y * 5;
				ft_draw_line3(data->wind, b->point, b->next_point, b->line);
			}
			b->j++;
		}
		b->i++;
	}
	draw_player(b->player, data->wind);
	draw_sprites(data, data->wind, b);
}
