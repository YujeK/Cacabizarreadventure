/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 22:06:04 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:47:14 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

t_coord	*create_edge(t_coord vertex_indexes, t_coord *edges, int edges_length)
{
	edges[edges_length] = vertex_indexes;
	return (edges);
}

t_map	divide_line(t_map map, int edge_index)
{
	t_coord tmp;

	tmp.x = map.vertex_length - 1;
	tmp.y = map.edges[edge_index].y;
	map.edges[edge_index].y = tmp.x;
	map.edges = create_edge(tmp, map.edges, map.edges_length);
	map.edges_length += 1;
	return (map);
}
