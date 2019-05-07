/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_comps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 02:59:19 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/07 08:24:01 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

SDL_Color	ft_hex_to_rgb(int hexa)
{
	SDL_Color color;

	color.r = hexa >> 24;
	color.g = hexa >> 16;
	color.b = hexa >> 8;
	color.a = hexa;
	return (color);
}

void		cap_framerate(t_data *data)
{
	if ((1000 / FPS) > SDL_GetTicks() - data->starting_tick)
		SDL_Delay(1000 / FPS - (SDL_GetTicks() - data->starting_tick));
	if (data->is_cd == 1)
	{
		data->weap_cd++;
		if (data->weap_cd == 7)
		{
			data->weap_cd = 0;
			data->is_cd = 0;
		}
	}
}

void		wpn_bobbing(t_data *data)
{
	if (data->wpn_x == 15 || data->wpn_x == -15
	|| data->wpn_y == -15 || data->wpn_y == 15)
		data->wpn_repos = 1;
	if (data->wpn_x == 0 && data->wpn_y == 0)
		data->wpn_repos = 0;
	if ((data->wpn_y > 0) && data->wpn_repos == 1)
		data->wpn_y--;
	if ((data->wpn_y < 0) && data->wpn_repos == 1)
		data->wpn_y++;
	if ((data->wpn_x < 0) && data->wpn_repos == 1)
		data->wpn_x++;
	if ((data->wpn_x > 0) && data->wpn_repos == 1)
		data->wpn_x--;
}

void		ft_crosshair(t_data *data)
{
	t_coord		pt1;
	t_coord		pt2;
	t_line		line;

	pt1.x = SCREEN_WIDTH / 2 - 1;
	pt1.y = SH / 2 - 12;
	pt2.x = SCREEN_WIDTH / 2 - 1;
	pt2.y = SH / 2 + 12;
	line.color = 0xFF1493;
	ft_draw_line3(data->wind, pt1, pt2, line);
	pt1.x = SCREEN_WIDTH / 2 - 12;
	pt1.y = SH / 2;
	pt2.x = SCREEN_WIDTH / 2 + 12;
	pt2.y = SH / 2;
	ft_draw_line3(data->wind, pt1, pt2, line);
}
