/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_intersections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 18:04:24 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:45:59 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

int	orientation(t_coord p, t_coord q, t_coord r)
{
	int	val;

	val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);
	if (val == 0)
		return (0);
	return (val > 0 ? 1 : 2);
}

int	line_intersects(t_coord p1, t_coord q1, t_coord p2, t_coord q2)
{
	int o1;
	int o2;
	int o3;
	int o4;

	o1 = orientation(p1, q1, p2);
	o2 = orientation(p1, q1, q2);
	o3 = orientation(p2, q2, p1);
	o4 = orientation(p2, q2, q1);
	if (o1 == 0 || o2 == 0 || o3 == 0 || o4 == 0)
		return (0);
	if (o1 != o2 && o3 != o4)
		return (1);
	return (0);
}

int	there_are_intersections(t_map map)
{
	int		i;
	int		j;
	t_wall	line1;
	t_wall	line2;

	i = -1;
	while (++i < map.edges_length - 1)
	{
		line1 = get_line_coordinates(map, i);
		j = i;
		while (++j < map.edges_length)
		{
			line2 = get_line_coordinates(map, j);
			if (line_intersects(line1.start, line1.end, line2.start, line2.end))
				return (1);
		}
	}
	return (0);
}
