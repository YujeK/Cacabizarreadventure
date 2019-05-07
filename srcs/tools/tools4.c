/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 03:29:08 by smerelo           #+#    #+#             */
/*   Updated: 2019/05/07 05:35:05 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	orientation(t_vector p, t_vector q, t_vector r)
{
	int	val;

	val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);
	if (val == 0)
		return (0);
	return (val > 0 ? 1 : 2);
}

int	line_intersects(t_vector p1, t_vector q1, t_vector p2, t_vector q2)
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

int		in_sector_full(t_sector *sectors, t_vector point, unsigned int NumSectors)
{
	t_vector	infinite;
	t_wall	sector_edge;
	int		i;
	int		j;
	int		intersection_count;

	infinite.y = point.y;
	infinite.x = 200000;
	i = -1;
	while (++i < NumSectors)
	{
		j = -1;
		intersection_count = 0;
		while (++j < sectors[i].npoints)
		{
			sector_edge.start = sectors[i].vertex[j];
			if(j == sectors[i].npoints)
				sector_edge.end = sectors[i].vertex[0];
			else
				sector_edge.end = sectors[i].vertex[j + 1];
			if (line_intersects(point, infinite,
						sector_edge.start, sector_edge.end))
				intersection_count++;
		}
		if (intersection_count == 1)
			return (i);
	}
	return (-1);
}
