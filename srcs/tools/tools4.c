/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 03:29:08 by smerelo           #+#    #+#             */
/*   Updated: 2019/05/08 11:32:34 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		overlap(float a1, float a2, float b1, float b2)
{
	if (min(a1, a2) <= max(b1, b2) && min(b1, b2) <= max(a1, a2))
		return (1);
	else
		return (0);
}

int		orientation(t_vector p, t_vector q, t_vector r)
{
	int	val;

	val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);
	if (val == 0)
		return (0);
	return (val > 0 ? 1 : 2);
}

int		line_intersects(t_vector p1, t_vector q1, t_vector p2, t_vector q2)
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

int		in_sector_full(t_sector *sectors,
			t_vector point, unsigned int numsectors)
{
	t_vector	i;
	t_wall		se;
	int			t[3];

	i.y = point.y;
	i.x = 200000;
	t[0] = -1;
	while (++t[0] < (int)numsectors)
	{
		t[1] = -1;
		t[2] = 0;
		while (++t[1] < (int)sectors[t[0]].npoints)
		{
			se.start = sectors[t[0]].vertex[t[1]];
			if (t[1] == (int)sectors[t[0]].npoints)
				se.end = sectors[t[0]].vertex[0];
			else
				se.end = sectors[t[0]].vertex[t[1] + 1];
			if (line_intersects(point, i, se.start, se.end))
				t[2]++;
		}
		if (t[2] == 1)
			return (t[0]);
	}
	return (-1);
}
