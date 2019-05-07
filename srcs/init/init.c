/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <smerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 09:40:28 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/07 14:22:27 by smerelo          ###   ########.fr       */
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
				SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SH, SDL_WINDOW_SHOWN);
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
	b->map = ft_strsplit(b->str, 'z');
}

void        init_ingame_vars(t_data *data, t_b *b)
{
	b->eyeheight = b->player.ducking ? DuckHeight : Eyeheight;
	b->move_vec[0] = 0.f;
	b->move_vec[1] = 0.f;
	b->player.ground = !b->player.falling;
	stand_activation(data, &b->player);
	data->sprint = 1;
	data->aim = -1;
}

t_bas init_draw_vars(t_data *data, t_b *b, t_bas *bas)
{
	bas->head = bas->queue;
	bas->tail = bas->queue;
	data->sprite = sprite_size(data->sprite, b->player, *data, b);
	bas->i = -1;
	while (++bas->i < 32)
		data->sectqueue[bas->i] = -1;
	bas->x = -1;
	while (++bas->x < SH)
		bas->ybottom[bas->x] = SH - 1;
	bas->x = -1;
	while (++bas->x < SCREEN_WIDTH)
		bas->ytop[bas->x] = 0;
	bas->x = -1;
	while (++bas->x < data->numsectors)
		bas->renderedsectors[bas->x] = 0;
	bas->head->sectorno = b->player.sector;
	bas->head->sx1 = 0;
	bas->head->sx2 = SCREEN_WIDTH - 1;
	if (++bas->head == bas->queue + 32)
		bas->head = bas->queue;
	return (*bas);
}

void init_intersect_vars(t_data *data, t_b *b, t_bas *bas)
{
	bas->nearz = 1e-4f;
	bas->farz = 5;
	bas->nearside = 1e-5f;
	bas->farside = 20.f;
	bas->i1 = Intersect(bas->tx1, bas->tz1, bas->tx2, bas->tz2,
	-bas->nearside, bas->nearz, -bas->farside, bas->farz);
	bas->i2 = Intersect(bas->tx1, bas->tz1, bas->tx2, bas->tz2,
	bas->nearside, bas->nearz, bas->farside, bas->farz);
	if (bas->tz1 < bas->nearz)
	{
		if (bas->i1.y > 0)
		{
			bas->tx1 = bas->i1.x;
			bas->tz1 = bas->i1.y;
		}
		else
		{
			bas->tx1 = bas->i2.x;
			bas->tz1 = bas->i2.y;
		}
	}
}

void init_intersect_vars2(t_data *data, t_b *b, t_bas *bas)
{
	if (bas->tz1 <= 0 || bas->tz2 <= 0)
	{
		init_intersect_vars(data, b, bas);
		if (bas->tz2 < bas->nearz)
		{
			if (bas->i1.y > 0)
			{
				bas->tx2 = bas->i1.x;
				bas->tz2 = bas->i1.y;
			}
			else
			{
				bas->tx2 = bas->i2.x;
				bas->tz2 = bas->i2.y;
			}
		}
	}
}
