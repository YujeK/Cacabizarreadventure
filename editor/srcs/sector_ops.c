/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:24:46 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 23:04:18 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

t_map		displace_edges(t_map map, int sector_to_change, int edge_index)
{
	int i;

	i = map.sector[sector_to_change].edges_length + 1;
	while (--i > edge_index + 1)
		map.sector[sector_to_change].edges[i] =
			map.sector[sector_to_change].edges[i - 1];
	return (map);
}

t_map		connect_new_edges(t_map map, int edge_to_extrude_index)
{
	t_coord vertex_to_connect;

	vertex_to_connect.x = map.edges[edge_to_extrude_index].x;
	vertex_to_connect.y = map.vertex_length - 2;
	map.edges = create_edge(vertex_to_connect, map.edges, map.edges_length);
	map.edges_length++;
	vertex_to_connect.x = map.vertex_length - 2;
	vertex_to_connect.y = map.vertex_length - 1;
	map.edges = create_edge(vertex_to_connect, map.edges, map.edges_length);
	map.edges_length++;
	vertex_to_connect.x = map.vertex_length - 1;
	vertex_to_connect.y = map.edges[edge_to_extrude_index].y;
	map.edges = create_edge(vertex_to_connect, map.edges, map.edges_length);
	map.edges_length++;
	return (map);
}

t_map		create_new_sector(t_map map, int edge_to_extrude)
{
	int		i;
	int		j;
	t_coord last_sector_edge;

	map.sector[map.sector_length].num = map.sector_length;
	map.sector[map.sector_length].edges_length = 4;
	map.sector[map.sector_length].ceil_height = 520;
	map.sector[map.sector_length].floor_height = 480;
	if ((map.sector[map.sector_length].edges =
				(int*)malloc(sizeof(t_coord) * (250))) == NULL)
		exit_on_error();
	i = map.edges_length - 4;
	j = 0;
	while (++i < map.edges_length)
		map.sector[map.sector_length].edges[j++] = i;
	last_sector_edge.x = map.edges[edge_to_extrude].y;
	last_sector_edge.y = map.edges[edge_to_extrude].x;
	map.edges = create_edge(last_sector_edge, map.edges, map.edges_length);
	map.sector[map.sector_length].edges[j] = map.edges_length;
	map.edges_length++;
	map.sector_length++;
	return (map);
}

t_map		extrude_sector(t_map map, int edge_to_extrude,
		t_coord extrude_start, t_coord extrude_end)
{
	t_coord extrude_vector;

	extrude_vector.x = extrude_end.x - extrude_start.x;
	extrude_vector.y = extrude_end.y - extrude_start.y;
	if (sqrt(pow(extrude_vector.x, 2) + pow(extrude_vector.y, 2)) < 5)
		return (map);
	map = create_new_vertexes(map, edge_to_extrude, extrude_vector);
	map = connect_new_edges(map, edge_to_extrude);
	map = create_new_sector(map, edge_to_extrude);
	if (nested_extrude(map) || !(geometry_is_valid(map)))
		map = remove_latest_sector(map);
	return (map);
}

int			select_edge_to_extrude(t_map map, t_coord mouse_pos)
{
	int		min_dist_allowed;
	int		current_dist;
	int		min_dist_found;
	t_coord closest_point;
	t_coord	p;

	p.x = -1;
	min_dist_allowed = 10;
	min_dist_found = 11;
	while (++p.x < map.edges_length)
	{
		closest_point = get_closest_point_on_line(map, mouse_pos, p.x);
		if (point_in_segment(map, closest_point, p.x))
			current_dist = get_point_distance(closest_point, mouse_pos);
		else
			continue;
		if (current_dist < min_dist_found)
		{
			min_dist_found = current_dist;
			p.y = p.x;
		}
	}
	return (min_dist_found <= min_dist_allowed ? p.y : -1);
}
