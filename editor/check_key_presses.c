/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key_presses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:23:21 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:45:36 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

t_map	check_sprite_key(t_wind wind, t_map map, t_coord mouse_pos, int s)
{
	if (wind.event.key.keysym.sym == SDLK_g)
	{
		if ((s = in_sector_full(map, mouse_pos)) != -1)
		{
			map.g_sprite[map.sprite_g_len].pos = mouse_pos;
			map.g_sprite[map.sprite_g_len].sector_num = s;
			map.sprite_g_len++;
		}
	}
	return (map);
}

t_map	check_altitude_press(t_wind wind, t_map map)
{
	if (wind.event.key.keysym.sym == SDLK_UP)
		map.sector[map.selected_sector].ceil_height += 1;
	if (wind.event.key.keysym.sym == SDLK_DOWN)
	{
		map.sector[map.selected_sector].ceil_height -= 1;
		if (map.sector[map.selected_sector].ceil_height <=
				map.sector[map.selected_sector].floor_height)
			map.sector[map.selected_sector].ceil_height += 1;
	}
	if (wind.event.key.keysym.sym == SDLK_RIGHT)
	{
		map.sector[map.selected_sector].floor_height += 1;
		if (map.sector[map.selected_sector].ceil_height <=
				map.sector[map.selected_sector].floor_height)
			map.sector[map.selected_sector].floor_height -= 1;
	}
	if (wind.event.key.keysym.sym == SDLK_LEFT)
		map.sector[map.selected_sector].floor_height -= 1;
	return (map);
}

t_map	check_key_up(t_wind wind, t_map map, t_coord mouse_pos)
{
	int sector_num;

	sector_num = -1;
	if (wind.event.key.keysym.sym == SDLK_ESCAPE)
	{
		write_fd(map);
		clean_and_exit(wind);
	}
	else if (wind.event.key.keysym.sym == SDLK_v)
		map = create_mid_line_vertex(map, mouse_pos);
	else if (wind.event.key.keysym.sym == SDLK_s)
		map.selected_sector = in_sector_full(map, mouse_pos);
	else if (wind.event.key.keysym.sym == SDLK_c)
	{
		if ((sector_num = in_sector_full(map, mouse_pos)) != -1)
		{
			map.player.sector_num = sector_num;
			map.player.pos = mouse_pos;
		}
	}
	map = check_sprite_key(wind, map, mouse_pos, sector_num);
	map = check_altitude_press(wind, map);
	return (map);
}

t_map	check_key_press(t_wind wind, t_map map, t_coord mouse_pos)
{
	if (wind.event.type == SDL_KEYUP)
		map = check_key_up(wind, map, mouse_pos);
	return (map);
}
