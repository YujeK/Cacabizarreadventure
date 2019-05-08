/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_duped_vertex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 20:29:56 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:49:16 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

int		vertex_is_equal(t_coord a, t_coord b)
{
	if (a.x == b.x && a.y == b.y)
		return (1);
	return (0);
}

t_map	remove_vertex(t_map map, int to_remove)
{
	int i;

	i = to_remove - 1;
	while (++i < map.vertex_length - 1)
		map.vertex[i] = map.vertex[i + 1];
	map.vertex_length -= 1;
	return (map);
}

t_map	rewire_edges(t_map map, int original, int to_remove)
{
	int i;

	i = -1;
	while (++i < map.edges_length)
	{
		if (map.edges[i].x == to_remove)
			map.edges[i].x = original;
		if (map.edges[i].y == to_remove)
			map.edges[i].y = original;
		if (map.edges[i].x > to_remove)
			map.edges[i].x -= 1;
		if (map.edges[i].y > to_remove)
			map.edges[i].y -= 1;
	}
	return (map);
}

t_map	remove_duped_vertex(t_map map, int i, int j)
{
	map = remove_vertex(map, i);
	map = rewire_edges(map, i, j);
	return (map);
}

t_map	remove_all_duped_vertex(t_map map)
{
	int i;
	int j;

	i = -1;
	while (++i < map.vertex_length)
	{
		j = i;
		while (++j < map.vertex_length)
		{
			if (vertex_is_equal(map.vertex[i], map.vertex[j]))
				remove_duped_vertex(map, i, j);
		}
	}
	return (map);
}
