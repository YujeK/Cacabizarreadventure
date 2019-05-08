/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 20:54:26 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:47:02 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

void	draw_sector_altitude(t_wind wind, t_map map)
{
	t_coord start;
	t_coord end;

	if (map.selected_sector != -1)
	{
		start.x = 50;
		end.x = 70;
		start.y = SCREEN_HEIGHT - map.sector[map.selected_sector].ceil_height;
		end.y = SCREEN_HEIGHT - map.sector[map.selected_sector].floor_height;
		draw_rectangle(start, end, wind);
	}
}

void	draw_square(t_wind wind, t_coord vertex, int square_size, int color)
{
	int		i;
	int		j;
	t_coord	pixel;

	pixel.x = vertex.x - (square_size / 2);
	pixel.y = vertex.y - (square_size / 2);
	i = -1;
	while (++i < square_size)
	{
		j = -1;
		pixel.x = vertex.x - (square_size / 2);
		while (++j < square_size)
		{
			if (pixel.x >= 0 && pixel.y >= 0 && pixel.x < SCREEN_WIDTH
					&& pixel.x++ < SCREEN_HEIGHT)
				put_pixel32(wind.screen, pixel.x, pixel.y, color);
		}
		pixel.y++;
	}
}

void	draw_edges(t_map map, t_wind wind)
{
	int		i;
	t_line	line_draw;
	t_wall	line;

	line_draw.color = 0xffffff;
	i = -1;
	while (++i < map.edges_length)
	{
		line = get_line_coordinates(map, i);
		ft_draw_line(wind, line.start, line.end, line_draw);
	}
}

void	draw_sprites(t_map map, t_wind wind)
{
	int i;

	i = -1;
	while (++i < map.sprite_g_len)
		draw_square(wind, map.g_sprite[i].pos, 3, 0xffff00);
	i = -1;
	while (++i < map.sprite_r_len)
		draw_square(wind, map.r_sprite[i].pos, 3, 0x00ffff);
}

void	draw_window(t_map map, t_wind wind)
{
	int i;

	SDL_FillRect(wind.screen, NULL, 0x000000);
	i = -1;
	while (++i < map.vertex_length)
		draw_square(wind, map.vertex[i], 5, 0xffffff);
	draw_edges(map, wind);
	draw_sector_altitude(wind, map);
	draw_sprites(map, wind);
	draw_square(wind, map.player.pos, 7, 0x00ff00);
	SDL_UpdateWindowSurface(wind.window);
}
