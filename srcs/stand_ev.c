/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stand_ev.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 02:26:57 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/05 18:30:01 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

 void    pick_up(t_data *data, t_plyr *player, t_object *sprite)
{

	if (player->where.y <= sprite->where.y + 2 && player->where.x <= sprite->where.x + 2  && player->where.y >= sprite->where.y - 2 && player->where.x >= sprite->where.x - 2&& sprite->status == 1)
	{
		data->score++;
		data->weapon_ammo += 3;
		sprite->status = 2;
	}
}

void stand_activation(t_data *data, t_plyr *player)
{
	if (data->zawarudo == 1)
	{
		Mix_PauseMusic();
		if (time(0) - data->stand_timer > 14)
		{
			data->luminosity = data->prev_lum;
			data->zawarudo = 0;
			data->timer_start += 15;
		}
	}
	if (data->eyesofthedead == 0 && data->zawarudo == 0)
		Mix_ResumeMusic();
}

void    stand_ev(t_data *data, Uint8 *state, t_plyr *player)
{
		if (state[SDL_SCANCODE_KP_2] && state[SDL_SCANCODE_KP_4] && state[SDL_SCANCODE_KP_8] && state[SDL_SCANCODE_KP_6])
		{
		data->zawarudo = 1;
		data->stand_timer = time(0);
		if (Mix_PlayChannel(0, data->stand_warudo, 0) == -1)
			ft_error_exit("cant play zawarudo", data);
		}
		if (state[SDL_SCANCODE_R])
		{
				data->eyesofthedead = 1;
				data->stand_timer = time(0);
				if (Mix_PlayChannel(1, data->eye_sound, 0) == -1)
					ft_error_exit("cant play eyesound", data);
					Mix_Volume(1, 128/3);
			data->stand_timer = time(0);
		}
		if (data->eyesofthedead == 1)
		{
			Mix_PauseMusic();
			if (data->aim >= 0 && data->sprite[data->aim].status == 1)
			{
				if (state[SDL_SCANCODE_F])
				{
					if (Mix_PlayChannel(0, data->tp_sound, 0) == -1)
						ft_error_exit("cant play tp", data);
					player->where.y = data->sprite[data->aim].where.y;
					player->where.x = data->sprite[data->aim].where.x;
					player->sector = data->sprite[data->aim].sectorno;
					data->score++;
					data->weapon_ammo += 3;
					data->sprite[data->aim].status = 2;
				}
			}
			if (data->zawarudo == 0 && data->eyesofthedead == 0)
			{
				Mix_ResumeMusic();
				Mix_HaltChannel(1);
				if (time(0) - data->stand_timer > 14)
				{
					data->eyesofthedead = 0;
				}
			}
		}
}
