/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:35:38 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/05 14:49:13 by asamir-k         ###   ########.fr       */
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
	data.weapon_ammo = 30;
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
	if (SDL_SetRelativeMouseMode(TRUE) < 0)
		ft_error_exit("Wolf3d: Unable to set relative mode", &data);
	str = ft_strnew(1);
	fd = open("maps/map3", O_CREAT | O_RDWR | O_APPEND, 0777);
	while ((ret = get_next_line(fd, &buf)) == 1)
	{
		str = ft_strjoin2(str, buf);
		ft_strdel(&buf);
	}
	map = ft_strsplit(str, 'z');
	init_sprites(&data, map);
	init_img(&data);
	vert = Load_vertex(map);
	sectors = Load_sectors(map, &NumSectors, vert);
	player = Load_Player(sectors, map);
	int i;
	int j;
	int t;
	i = -1;
	t = -1;
	/*sectors[0].vertex[4].x = 0.0;
	sectors[0].vertex[4].y = 50.0;
	sectors[0].neighbors[4] = -1;*/
		//printf("%i\n\n\n",sectors[0].npoints);

 	while(++i < NumSectors)
	{
		t = - 1;
		j = -1;
		//printf("sectors[%i]\n", i);
		while(++j < sectors[i].npoints)
		{
			printf("sect[%i] vert[%i] x: %f y: %f nei[%i]\n", i, j, sectors[i].vertex[j].x, sectors[i].vertex[j].y, sectors[i].neighbors[j]);
			//printf(" neighbor[%i]: %i\n\n", j, sectors[i].neighbors[j]);
			//printf("\n");
		}
	}
	rect.x = 1000;
	rect.y = 1000;
	data.startgame_timer = time(0);
	Mix_PlayMusic(data.menutheme, 1);
	while(1)
	{
	data.starting_tick = SDL_GetTicks();
	if (data.is_cd == 1)
	{
		data.weap_cd++;
		if (data.weap_cd == 7)
		{
			data.weap_cd = 0;
			data.is_cd = 0;
		}
	}
	if (data.game_start == 1)
	{
		stand_activation(&data, &player);
		/* starting data */
		data.sprint = 1;
		data.aim = -1;
			/* render */
		draw_screen(&data, &player, sectors, NumSectors);
		draw_inventory(&data);
		draw_items(&data);
		draw_map(vert, sectors, NumSectors, data.wind, player, &data);
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
		player.velocity.x = player.velocity.x * (1-acceleration) + move_vec[0] * acceleration * data.sprint;
		player.velocity.y = player.velocity.y * (1-acceleration) + move_vec[1] * acceleration * data.sprint;
		if(pushing)
			player.moving = 1;
	}
	else
		start_menu(&data);
	cap_framerate(&data);
	SDL_UpdateWindowSurface(window);
	}
	ft_exit(&data);
	return 0;
}
