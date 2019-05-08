/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:24:51 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:49:58 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

t_coord	*place_vertex(t_coord new_vertex_pos,
		t_coord *vertex, int vertex_length)
{
	vertex[vertex_length] = new_vertex_pos;
	return (vertex);
}

t_wall	get_line_coordinates(t_map map, int i)
{
	t_wall line;

	line.start.x = map.vertex[map.edges[i].x].x;
	line.start.y = map.vertex[map.edges[i].x].y;
	line.end.x = map.vertex[map.edges[i].y].x;
	line.end.y = map.vertex[map.edges[i].y].y;
	return (line);
}

t_map	create_mid_vertex(t_map map, t_coord point_on_line)
{
	map.vertex = place_vertex(point_on_line, map.vertex, map.vertex_length);
	map.vertex_length += 1;
	return (map);
}

t_map	create_mid_line_vertex(t_map map, t_coord world_pos)
{
	int		edge_index;
	t_coord	point_on_line;

	edge_index = -1;
	while ((edge_index) < map.edges_length)
	{
		edge_index = line_is_close(map, world_pos, edge_index);
		if (edge_index == -1)
			return (map);
		point_on_line = get_closest_point_on_line(map, world_pos, edge_index);
		if (point_in_segment(map, point_on_line, edge_index))
		{
			map = create_mid_vertex(map, point_on_line);
			map = divide_line(map, edge_index);
			map = add_edge_to_sector(map, edge_index);
			break ;
		}
	}
	return (map);
}
