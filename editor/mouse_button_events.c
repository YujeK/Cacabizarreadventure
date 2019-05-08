/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_button_events.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 00:29:48 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:48:49 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

int		check_right_mouse_press(t_map map, t_coord mouse_pos)
{
	return (select_edge_to_extrude(map, mouse_pos));
}

int		check_left_mouse_press(t_map map, t_coord mouse_pos)
{
	int vertex_index;

	vertex_index = select_vertex_to_move(map, mouse_pos);
	return (vertex_index);
}

t_map	check_left_mouse_release(t_map map,
		t_coord mouse_pos, int vertex_index)
{
	if (vertex_index != -1)
		map = translate_vertex(map, vertex_index, mouse_pos);
	return (map);
}

t_map	check_mouse_events(t_wind wind, t_map map, t_coord mouse_pos)
{
	static int		edge_index;
	static int		vertex_index;
	static t_coord	start_mouse_pos;

	if (wind.event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (wind.event.button.button == SDL_BUTTON_LEFT)
			vertex_index = check_left_mouse_press(map, mouse_pos);
		else
			edge_index = check_right_mouse_press(map, mouse_pos);
		start_mouse_pos = mouse_pos;
	}
	if (wind.event.type == SDL_MOUSEBUTTONUP)
	{
		if (wind.event.button.button == SDL_BUTTON_LEFT)
			map = check_left_mouse_release(map, mouse_pos, vertex_index);
		else
		{
			if (edge_index != -1)
				map = extrude_sector(map, edge_index,
						start_mouse_pos, mouse_pos);
		}
	}
	return (map);
}
