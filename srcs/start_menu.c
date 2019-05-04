/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 01:15:43 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/04 09:19:36 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void    fillerect(SDL_Rect rect, int color, t_wind wind)
{
    int x;
    int y;
    y = 0;
    while (y < SCREEN_HEIGHT)
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
	data->count_frames++;
	if (data->count_frames == 35)
	{
		data->count_frames = 0;
		if (data->which_menu == 0)
			data->which_menu = 1;
		else
			data->which_menu = 0;
	}
	SDL_Event ev;
	SDL_PollEvent(&ev);
	Uint8 *state;
	state = (Uint8 *)SDL_GetKeyboardState(0);
		if (state[SDL_SCANCODE_RETURN])
			data->game_start = 1;
		if (state[SDL_SCANCODE_ESCAPE])
			ft_exit(data);
			SDL_Rect rect;
	rect = (SDL_Rect){0, 0, 1000, 1000};
	fillerect(rect, WHITE, data->wind);
	if (data->which_menu == 1)
		display_img(0, 0, data->wind, 1001, data->menu.res_img);
	if (data->which_menu == 0)
		display_img(0, 0, data->wind, 1001, data->menustart.res_img);
}
