/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:23:30 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:47:56 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

int		dot_product(t_coord a, t_coord b)
{
	return (a.x * b.x + a.y * b.y);
}

int		vector_cross_product(t_wall a, t_wall b)
{
	t_coord a_to_middle;
	t_coord middle_to_b;

	a_to_middle.x = a.end.x - a.start.x;
	a_to_middle.y = a.end.y - a.start.y;
	middle_to_b.x = b.end.x - b.start.x;
	middle_to_b.y = b.end.y - b.start.y;
	return (a_to_middle.x * middle_to_b.y - middle_to_b.x * a_to_middle.y);
}

int		get_point_distance(t_coord a, t_coord b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}

int		point_in_segment(t_map map, t_coord point_in_line, int edge_index)
{
	double distance_to_start;
	double distance_to_end;
	double segment_distance;

	distance_to_start = get_point_distance(point_in_line,
			map.vertex[map.edges[edge_index].x]);
	distance_to_end = get_point_distance(point_in_line,
			map.vertex[map.edges[edge_index].y]);
	segment_distance = get_point_distance(map.vertex[map.edges[edge_index].x],
			map.vertex[map.edges[edge_index].y]);
	if (distance_to_start < segment_distance
			&& distance_to_end < segment_distance)
		return (1);
	return (0);
}

t_coord	get_closest_point_on_line(t_map map, t_coord world_pos, int edge_index)
{
	t_wall	line;
	t_coord start_to_point;
	t_coord	line_vector;
	t_coord result;
	t_misc	t;

	line = get_line_coordinates(map, edge_index);
	start_to_point.x = world_pos.x - line.start.x;
	start_to_point.y = world_pos.y - line.start.y;
	line_vector.x = line.end.x - line.start.x;
	line_vector.y = line.end.y - line.start.y;
	t.squared_line_distance = pow(line_vector.x, 2) + pow(line_vector.y, 2);
	t.stp_dot_ste = start_to_point.x *
		line_vector.x + start_to_point.y * line_vector.y;
	t.t = t.stp_dot_ste / t.squared_line_distance;
	result.x = (int)(line.start.x + line_vector.x * t.t);
	result.y = (int)(line.start.y + line_vector.y * t.t);
	return (result);
}
