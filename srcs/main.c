/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:35:38 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 11:35:59 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_plyr	move_player2(t_b *b, int s)
{
	t_vector temp;

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
	unsigned int	s;
	t_sector		sect;
	t_vector		*vert;
	t_inter			t[2];

	b->px = b->player.where.x;
	b->py = b->player.where.y;
	sect = b->sectors[b->player.sector];
	vert = sect.vertex;
	s = 0;
	while (s < sect.npoints)
	{
		init_inter2(b, &t[0], vert, s);
		init_pointside2(b, &t[1], s, vert);
		if (sect.neighbors[s] >= 0 && intersectbox(&t[0])
		&& pointside(&t[1]) < 0)
		{
			b->player.sector = sect.neighbors[s];
			break ;
		}
		s++;
	}
	move_player2(b, s);
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
	b.vert = load_vertex(b.map);
	b.sectors = load_sectors(b.map, &b.numsectors, b.vert);
	b.player = load_player(b.sectors, b.map);
	data.startgame_timer = time(0);
	data.numsectors = b.numsectors;
	Mix_PlayMusic(data.menutheme, 1);
	game_loop(&data, &b);
	ft_exit();
	return (0);
}
