/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_ops3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 10:07:20 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:49:44 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

t_map		create_edge_on_sector(t_map map,
		int sector_to_change, int edge_index)
{
	map = displace_edges(map, sector_to_change, edge_index);
	map.sector[sector_to_change].edges[edge_index + 1] = map.edges_length - 1;
	map.sector[sector_to_change].edges_length += 1;
	return (map);
}

int			sector_contains_edge(t_sector sector, int altered_edge)
{
	int i;

	i = -1;
	while (++i < sector.edges_length)
	{
		if (sector.edges[i] == altered_edge)
			return (i);
	}
	return (-1);
}

t_map		add_edge_to_sector(t_map map, int altered_edge)
{
	int i;
	int	edge_index;

	i = -1;
	while (++i < map.sector_length)
	{
		if ((edge_index = (sector_contains_edge(map.sector[i],
							altered_edge))) != -1)
			map = create_edge_on_sector(map, i, edge_index);
	}
	return (map);
}

t_map		create_new_vertexes(t_map map,
		int edge_to_extrude_index, t_coord extrude_vector)
{
	t_wall	edge_to_extrude;
	t_coord	new_vertex;

	edge_to_extrude = get_line_coordinates(map, edge_to_extrude_index);
	new_vertex.x = edge_to_extrude.start.x + extrude_vector.x;
	new_vertex.y = edge_to_extrude.start.y + extrude_vector.y;
	map.vertex = place_vertex(new_vertex, map.vertex, map.vertex_length);
	map.vertex_length++;
	new_vertex.x = edge_to_extrude.end.x + extrude_vector.x;
	new_vertex.y = edge_to_extrude.end.y + extrude_vector.y;
	map.vertex = place_vertex(new_vertex, map.vertex, map.vertex_length);
	map.vertex_length++;
	return (map);
}
