/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 09:40:28 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/06 13:31:40 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_main_v(t_data *data, t_b *b, char *arg)
{
	data->luminosity = 0.99;
	b->player.ground = 0;
	b->player.falling = 1;
	b->player.moving = 0;
	b->player.ducking = 0;

	TTF_Init();
	if (Mix_Init(MIX_INIT_MP3) < 0)
		exit(EXIT_FAILURE);
	if (!(data->font = TTF_OpenFont("ressources/bb.ttf", 100)))
		ft_error_exit(" I can't load font", data);
	data->wind.window = SDL_CreateWindow("Doom_Nukem", SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	data->wind.screen = SDL_GetWindowSurface(data->wind.window);
	if (SDL_SetRelativeMouseMode(TRUE) < 0)
		ft_error_exit("Wolf3d: Unable to set relative mode", data);
	b->str = ft_strnew(1);
	b->fd = open(arg, O_CREAT | O_RDWR | O_APPEND, 0777);
	while ((b->ret = get_next_line(b->fd, &b->buf)) == 1)
	{
		b->str = ft_strjoin2(b->str, b->buf);
		ft_strdel(&b->buf);
	}
}

void        init_ingame_vars(t_data *data, t_b *b)
{

    b->move_vec[0] = 0.f;
    b->move_vec[1] = 0.f;
    b->eyeheight = b->player.ducking ? DuckHeight : b->eyeheight;
    b->player.ground = !b->player.falling;
    stand_activation(data, &b->player);
    data->sprint = 1;
    data->aim = -1;
}
