/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:35:38 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/07 15:22:42 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_plyr	move_player2(t_b *b, t_vector temp, int s)
{
	b->player.anglesin = sinf(b->player.angle);
	b->player.anglecos = cosf(b->player.angle);
	temp.x = b->player.where.x + b->dx * 4;
	temp.y = b->player.where.y + b->dy * 4;
	if ((s = in_sector_full(b->sectors, temp, b->numsectors)) == -1)
		return (b->player);
	if (b->sectors[s].floor > b->sectors[b->player.sector].floor
		+ (b->player.where.z - b->sectors[b->player.sector].floor))
		return (b->player);
	b->player.where.x = temp.x - b->dx * 3;
	b->player.where.y = temp.y - b->dy * 3;
	if (b->sectors[b->player.sector].floor == 481)
		b->sectors[b->player.sector].floor = 440;
	return (b->player);
}

t_plyr	move_player(t_b *b)
{
	int			s;
	t_vector	temp;
	t_sector	sect;
	t_vector	*vert;

	b->px = b->player.where.x;
	b->py = b->player.where.y;
	sect = b->sectors[b->player.sector];
	vert = sect.vertex;
	s = 0;
	while (s < sect.npoints)
	{
		if (sect.neighbors[s] >= 0 && intersectbox(b->px,
			b->py, b->px + b->dx, b->py + b->dy,
			vert[s].x, vert[s].y, vert[s + 1].x,
			vert[s + 1].y) && pointside(b->px + b->dx, b->py
			+ b->dy, vert[s].x, vert[s].y, vert[s + 1].x, vert[s + 1].y) < 0)
		{
			b->player.sector = sect.neighbors[s];
			break ;
		}
		s++;
	}
	move_player2(b, temp, s);
	return (b->player);
}

int		main(int argc, char **argv)
{
	t_b		b;
	t_data	data;

	if (argc != 2 || argv[1][0] != 'm')
		return (0);
	ft_bzero(&data, sizeof(t_data));
	init_main_v(&data, &b, argv[1]);
	init_sprites(&data, b.map);
	data.weapon_ammo = data.sprite_nbr;
	init_img(&data);
	b.vert = Load_vertex(b.map);
	b.sectors = Load_sectors(b.map, &b.numsectors, b.vert);
	b.player = Load_Player(b.sectors, b.map);
	data.startgame_timer = time(0);
	data.numsectors = b.numsectors;
	//Mix_PlayMusic(data.menutheme, 1);
	game_loop(&data, &b);
	ft_exit(&data);
	return (0);
}
