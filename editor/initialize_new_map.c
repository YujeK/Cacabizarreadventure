/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_new_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:18:45 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:48:29 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

t_sector	initialize_sector(t_map map)
{
	int i;

	if ((map.sector[0].edges = (int*)malloc(sizeof(int) * (500))) == NULL)
		exit_on_error();
	i = -1;
	while (++i < 4)
		map.sector[0].edges[i] = i;
	map.sector[0].num = 0;
	map.sector[0].ceil_height = 40;
	map.sector[0].floor_height = 20;
	map.sector[0].edges_length = 4;
	return (map.sector[0]);
}

t_coord		*initialize_vertex(t_map map)
{
	map.vertex[0].x = 200;
	map.vertex[0].y = 200;
	map.vertex[1].x = 400;
	map.vertex[1].y = 200;
	map.vertex[2].x = 400;
	map.vertex[2].y = 400;
	map.vertex[3].x = 200;
	map.vertex[3].y = 400;
	return (map.vertex);
}

t_coord		*initialize_edges(t_map map)
{
	map.edges[0].x = 0;
	map.edges[0].y = 1;
	map.edges[1].x = 1;
	map.edges[1].y = 2;
	map.edges[2].x = 2;
	map.edges[2].y = 3;
	map.edges[3].x = 3;
	map.edges[3].y = 0;
	return (map.edges);
}

t_map		initialize_rest(t_map map)
{
	map.vertex_length = 4;
	map.edges_length = 4;
	map.sector_length = 1;
	map.player.sector_num = 0;
	map.player.pos.x = 300;
	map.player.pos.y = 300;
	map.sprite_g_len = 0;
	map.sprite_r_len = 0;
	return (map);
}

t_map		initialize_values(void)
{
	t_map map;

	if ((map.vertex = (t_coord*)malloc(sizeof(t_coord) * (1000))) == NULL)
		exit_on_error();
	if ((map.edges = (t_coord*)malloc(sizeof(t_coord) * (1000))) == NULL)
		exit_on_error();
	if ((map.sector = (t_sector*)malloc(sizeof(t_sector) * (200))) == NULL)
		exit_on_error();
	if ((map.g_sprite =
				(t_sprite_g*)malloc(sizeof(t_sprite_g) * (200))) == NULL)
		exit_on_error();
	if ((map.r_sprite =
				(t_sprite_r*)malloc(sizeof(t_sprite_r) * (200))) == NULL)
		exit_on_error();
	map.vertex = initialize_vertex(map);
	map.edges = initialize_edges(map);
	map.sector[0] = initialize_sector(map);
	map = initialize_rest(map);
	return (map);
}
