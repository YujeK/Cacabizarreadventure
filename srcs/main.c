/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:35:38 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/06 10:03:14 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_plyr	Move_player(float dx, float dy, t_plyr player,
t_sector *sectors, unsigned int NumSectors)
{
	float px;
	float py;
	int s;
	t_vector temp;

	px = player.where.x;
	py = player.where.y;
	t_sector sect = sectors[player.sector];
	t_vector *vert = sect.vertex;
	s = 0;
	while(s < sect.npoints)
	{
		if(sect.neighbors[s] >= 0
		&& IntersectBox(px, py, px+dx,py+dy, vert[s].x, vert[s].y, vert[s+1].x, vert[s+1].y)
		&& pointside(px+dx, py+dy, vert[s].x, vert[s].y, vert[s+1].x, vert[s+1].y) < 0)
		{
			player.sector = sect.neighbors[s];
			break;
		}
		s++;
	}
	player.anglesin = sinf(player.angle);
	player.anglecos = cosf(player.angle);
	temp.x = player.where.x + dx * 4;
	temp.y = player.where.y + dy * 4;
	if(in_sector_full(sectors, temp, NumSectors) == -1)
		return(player);
	player.where.x = temp.x - dx * 3;
	player.where.y = temp.y - dy * 3;
	if (sectors[player.sector].floor == 481)
		sectors[player.sector].floor = 440;
	return (player);
}

int main(int argc, char **argv)
{
	t_b b;
	t_data data;

	if (argc != 2 || argv[1][0] != 'm')
		return (0);
	ft_bzero(&data, sizeof(t_data));
	// INIT VAR
	init_main_v(&data, &b, argv[1]);
	b.map = ft_strsplit(b.str, 'z');
	//sprites init
	init_sprites(&data, b.map);
	data.weapon_ammo = data.sprite_nbr;
	init_img(&data);
	b.vert = Load_vertex(b.map);
	b.sectors = Load_sectors(b.map, &b.NumSectors, b.vert);
	b.player = Load_Player(b.sectors, b.map);
	data.startgame_timer = time(0);
	data.numsectors = b.NumSectors;
	//Mix_PlayMusic(data.menutheme, 1);
	game_loop(&data, &b);
	ft_exit(&data);
	return 0;
}
