/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <smerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 21:53:02 by smerelo           #+#    #+#             */
/*   Updated: 2019/05/03 07:27:53 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_plyr	Move_player(float dx, float dy, t_plyr player, t_sector *sectors)
{
	float px = player.where.x;
	float py = player.where.y;
	t_sector sect = sectors[player.sector];
	t_vector *vert = sect.vertex;
	int s;

	s = 0;
	while(s < sect.npoints)
	{
		if(sect.neighbors[s] >= 0
		&& IntersectBox(px,py, px+dx,py+dy, vert[s].x, vert[s].y, vert[s+1].x, vert[s+1].y)
		&& pointside(px+dx, py+dy, vert[s].x, vert[s].y, vert[s+1].x, vert[s+1].y) < 0)
		{
			player.sector = sect.neighbors[s];
			break;
		}
		s++;
	}
	player.where.x += dx;
	player.where.y += dy;
	player.anglesin = sinf(player.angle);
	player.anglecos = cosf(player.angle);
	return (player);
}

int main()
{
	t_plyr player;
	t_sector *sectors;
	t_sector sect;
	t_vector *vert;
	unsigned int NumSectors;
	unsigned int s;
	char *str;
	int fd;
	int ret;
	int size;
	char *buf;
	char **map;
	int wsad[4]={0,0,0,0};
	int x;
	int y;
	float xd;
	float yd;
	float eyeheight;
	float nextz;
	float hole_low;
	float hole_high;
	float dx;
	float dy;
	float px;
	float py;
	t_data data;
	unsigned int s1;
	int pushing;
	SDL_Rect rect;

	ft_bzero(&data, sizeof(t_data));
	data.weapon_ammo = 100;
	data.luminosity = 0.99;
	player.ground = 0;
	player.falling = 1;
	player.moving = 0;
	player.ducking = 0;
	size = 800;
	SDL_Surface *surface = NULL;

	TTF_Init();
	if (Mix_Init(MIX_INIT_MP3) < 0)
		exit(EXIT_FAILURE);
	if (!(data.font = TTF_OpenFont("ressources/bb.ttf", 100)))
		ft_error_exit(" I can't load font", &data);
	SDL_Window *window = SDL_CreateWindow("Doom_Nukem", SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	data.wind.screen = SDL_GetWindowSurface(window);
	/* weapon load */
	init_sprites(&data);
	init_img(&data);
	if (SDL_SetRelativeMouseMode(TRUE) < 0)
		ft_error_exit("Wolf3d: Unable to set relative mode", &data);
	str = ft_strnew(1);
	fd = open("maps/map_clear", O_CREAT | O_RDWR | O_APPEND, 0777);
	while ((ret = get_next_line(fd, &buf)) == 1)
	{
		str = ft_strjoin2(str, buf);
		ft_strdel(&buf);
	}
	map = ft_strsplit(str, 'z');
	int i;
	i = 0;
	vert = Load_vertex(map);
	sectors = Load_sectors(map, &NumSectors, vert);
	player = Load_Player(sectors, map[ft_tablen(map) - 2]);
	rect.x = 1000;
	rect.y = 1000;
	Mix_PlayMusic(data.menutheme, 1);
	while(1)
	{
		/* render */
		draw_screen(&data, &player, sectors, NumSectors);
		draw_inventory(&data);
		draw_items(&data);
		draw_map(vert, sectors, NumSectors, data.wind, player);
		/* render */
		ft_value_display(&data);
		eyeheight = player.ducking ? DuckHeight : Eyeheight;
		player.ground = !player.falling;
		if(player.falling)
		{
			player.velocity.z -= 0.02f;
			nextz = player.where.z + player.velocity.z;
			if(player.velocity.z < 0 && nextz  < sectors[player.sector].floor + eyeheight)
			{
				player.where.z = sectors[player.sector].floor + eyeheight;
				player.velocity.z = 0;
				player.falling = 0;
				player.ground  = 1;
			}
			else if(player.velocity.z > 0 && nextz > sectors[player.sector].ceil)
			{
				player.velocity.z = 0;
				player.falling = 1;
			}
			if(player.falling)
			{
				player.where.z += player.velocity.z;
				player.moving = 1;
			}
		}
		if(player.moving)
		{
			px = player.where.x;
			py = player.where.y;
			dx = player.velocity.x;
			dy = player.velocity.y;
			sect = sectors[player.sector];
			vert = sect.vertex;
			s = -1;
			while(++s < sect.npoints)
			{
				if(IntersectBox(px,py, px+dx,py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y)
				&& pointside(px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y) < 0)
				{
					hole_low  = sect.neighbors[s] < 0 ?  9e9 : max(sect.floor, sectors[sect.neighbors[s]].floor);
					hole_high = sect.neighbors[s] < 0 ? -9e9 : min(sect.ceil,  sectors[sect.neighbors[s]].ceil );
					if(hole_high < player.where.z+HeadMargin
					|| hole_low  > player.where.z-eyeheight+KneeHeight)
					{
						xd = vert[s + 1].x - vert[s+0].x, yd = vert[s+1].y - vert[s+0].y;
						dx = xd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
						dy = yd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
						player.moving = 0;
					}
				}
			}
			player = Move_player(dx, dy, player, sectors);
			player.falling = 1;
		}
		//events//
		event_mouse(&player, &data);
		player = Move_player(0 , 0, player, sectors);
		float move_vec[2] = {0.f, 0.f};
		event_keyboard(&player, &data, move_vec) == 1 ? pushing = 1 : 0;
		float acceleration = pushing ? 0.4 : 0.2;
		player.velocity.x = player.velocity.x * (1-acceleration) + move_vec[0] * acceleration;
		player.velocity.y = player.velocity.y * (1-acceleration) + move_vec[1] * acceleration;
		if(pushing)
			player.moving = 1;
		SDL_Delay(10);
		SDL_UpdateWindowSurface(window);
	}
	ft_exit(&data);
	return 0;
}
