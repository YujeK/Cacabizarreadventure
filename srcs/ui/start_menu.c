/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 01:15:43 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/08 11:40:22 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	end_game(t_data *data)
{
	if (data->score == data->sprite_nbr * 2)
	{
		data->story_step = 4;
		data->win = 1;
	}
	if (data->weapon_ammo == 0)
		data->story_step = 4;
}

void	fillerect(SDL_Rect rect, int color, t_wind wind)
{
	int x;
	int y;

	y = 0;
	while (y < SH)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			put_pixel32(wind.screen, rect.x + x, rect.y + y, color);
			x++;
		}
		y++;
	}
}

void	start_menu(t_data *data)
{
	SDL_Event	ev;
	Uint8		*state;
	SDL_Rect	rect;

	SDL_PollEvent(&ev);
	state = (Uint8 *)SDL_GetKeyboardState(0);
	data->count_frames++;
	if (data->count_frames == 35)
	{
		data->count_frames = 0;
		if (data->which_menu == 0)
			data->which_menu = 1;
		else
			data->which_menu = 0;
	}
	if (state[SDL_SCANCODE_RETURN])
		data->game_start = 1;
	if (state[SDL_SCANCODE_ESCAPE])
		ft_exit();
	rect = (SDL_Rect){0, 0, 1000, 1000};
	fillerect(rect, WHITE, data->wind);
	if (data->which_menu == 1)
		display_img(data->pos, data->wind, 1001, data->menu.res_img);
	if (data->which_menu == 0)
		display_img(data->pos, data->wind, 1001, data->menustart.res_img);
}
