/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 23:03:06 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/08 11:29:35 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			timer_ui(t_data *data, SDL_Rect rect)
{
	if (data->timer_start && data->zawarudo == 0)
	{
		if (data->story_step != 4)
		{
			rect = (SDL_Rect){431, 50, 60, 60};
			data->timer = time(0) - data->timer_start;
		}
		ft_set_nbrstring(data->timer, rect, ft_color_nb_state(1), data);
	}
	if (data->zawarudo == 1 && data->timer_start)
	{
		rect = (SDL_Rect){431, 50, 60, 60};
		ft_set_nbrstring(data->timer, rect, ft_color_nb_state(1), data);
	}
}

void			ft_start_game(t_data *data)
{
	SDL_Rect		rect;

	ft_bzero(&rect, sizeof(SDL_Rect));
	timer_ui(data, rect);
	story_0and1(data, rect);
	story_2and3(data, rect);
	if (data->story_step == 4)
	{
		data->timer_start = 0;
		rect = (SDL_Rect){431, 50, 60, 60};
		ft_set_nbrstring(data->timer, rect, ft_color_nb_state(1), data);
		if (data->win == 1)
		{
			rect = (SDL_Rect){400, 400, 100, 100};
			ft_set_string(rect, "You win", ft_hex_to_rgb(GREEN), data);
		}
		else
		{
			rect = (SDL_Rect){400, 400, 100, 100};
			ft_set_string(rect, "You lose", ft_hex_to_rgb(RED), data);
		}
	}
}

void			ft_value_display(t_data *data)
{
	SDL_Rect		rect;

	if (data->which_weapon != 0)
	{
		rect = (SDL_Rect){0, 80, 60, 30};
		ft_set_string(rect, "AMMO", ft_color_nb_state(data->weapon_ammo), data);
		rect = (SDL_Rect){0, 120, 60, 30};
		ft_set_nbrstring(data->weapon_ammo,
			rect, ft_color_nb_state(data->weapon_ammo), data);
		rect = (SDL_Rect){200, 0, 60, 60};
		ft_set_string(rect, "SCORE", ft_color_nb_state(data->score), data);
		rect = (SDL_Rect){240, 50, 60, 60};
		ft_set_nbrstring(data->score,
			rect, ft_color_nb_state(data->score), data);
	}
	ft_crosshair(data);
	ft_start_game(data);
}
