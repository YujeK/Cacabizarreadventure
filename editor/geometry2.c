/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 09:46:15 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:48:03 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

int	min(int a, int b)
{
	return (a > b ? b : a);
}

int	max(int a, int b)
{
	return (a > b ? a : b);
}

int	get_line_distance(t_map map, t_coord world_pos, int edge_index)
{
	t_wall	line;
	int		distance;

	line = get_line_coordinates(map, edge_index);
	distance = (abs((line.end.y - line.start.y) * (world_pos.x) -
	(line.end.x - line.start.x) * (world_pos.y) + (line.end.x * line.start.y)
	- (line.end.y * line.start.x)) / (sqrt(pow(line.end.y - line.start.y, 2) +
	pow(line.end.x - line.start.x, 2))));
	return (distance);
}

int	line_is_close(t_map map, t_coord world_pos, int i)
{
	int distance;
	int min_distance;
	int closest_edge;

	min_distance = 25;
	while (++i < map.edges_length)
	{
		distance = get_line_distance(map, world_pos, i);
		if (distance < min_distance)
		{
			min_distance = distance;
			closest_edge = i;
			if (min_distance <= 10)
				return (i);
		}
	}
	return (min_distance <= 10 ? closest_edge : -1);
}
