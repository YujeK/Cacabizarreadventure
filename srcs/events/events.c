/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:35:53 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/06 12:38:45 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int check_keydown(t_wind wind)
{
	if (wind.event.key.keysym.sym == SDLK_ESCAPE)
	{
		SDL_DestroyWindow(wind.window);
		SDL_Quit();
		return (-1);
	}
	return (0);
}

void event_mouse(t_plyr *player, t_data *data)
{
	float t;
	int x;
	int y;

	SDL_GetRelativeMouseState(&x, &y);
	player->angle += x * 0.005f;
	data->yaw = fclamp(data->yaw + y * 0.01f, -5, 5);
	player->yaw = data->yaw + player->velocity.z * 0.5f;
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && data->weapon_state == 0 && data->story_step == 3)
	{
		if(data->aim >= 0 && data->which_weapon != 0 && data->weapon_ammo > 0)
		{
			if (data->sprite[data->aim].status == 0)
				data->score++;
			data->sprite[data->aim].status = 1;
			data->death_timer = time(0);
		}
		if (data->weapon_ammo > 0 && data->is_cd == 0)
		{
			if (Mix_PlayChannel(2, data->ak, 0) == -1)
				ft_error_exit("cant play ak", data);
			Mix_Volume(2, 128/3);
			data->weapon_ammo--;
			data->weapon_state = 1;
			data->is_cd = 1;
		}
	}
	else if (data->weapon_state == 1)
		data->weapon_state = 0;
}

void inv_ev(t_data *data, Uint8 *state, float *move_vec)
{
	if (state[SDL_SCANCODE_TAB] && data->story_step == 0 && data->msg_readen == 1)
	{
		if (data->inventory_state == 0)
			data->inventory_state = 1;
		data->story_step = 1;
	}
	if (data->inventory_state == 1)
	{
		if (state[SDL_SCANCODE_1] && data->story_step == 1)
		{
			data->which_weapon = 1;
			data->inventory_state = 0;
			data->story_step = 2;
		}
		if (state[SDL_SCANCODE_2] && data->story_step == 1)
		{
			data->which_weapon = 2;
			data->inventory_state = 0;
			data->story_step = 2;
		}
		if (state[SDL_SCANCODE_3] && data->story_step == 1)
		{
			data->which_weapon = 3;
			data->inventory_state = 0;
			data->story_step = 2;
		}
	}
	if (state[SDL_SCANCODE_M] && data->story_step == 2)
	{
		data->timer_start = time(0);
		Mix_PlayMusic(data->maintheme, -1);
		data->story_step = 3;
	}
	if (state[SDL_SCANCODE_J] && data->story_step == 0)
		data->msg_readen = 1;
	if (state[SDL_SCANCODE_KP_MINUS])
		data->luminosity -= 0.0005;
	if (state[SDL_SCANCODE_KP_PLUS] && data->luminosity < 0.9995)
		data->luminosity += 0.0005;
}

void	event_manager(t_data *data, t_b *b)
{
	event_mouse(&b->player, data);
	b->player = Move_player(0, 0, b->player, b->sectors, b->NumSectors);
	event_keyboard(&b->player, data, b->move_vec, b->sectors) == 1 ? b->pushing = 1 : 0;
	b->acceleration = b->pushing ? 0.4 : 0.2;
	b->player.velocity.x = b->player.velocity.x * (1 - b->acceleration) + b->move_vec[0] * b->acceleration * data->sprint;
	b->player.velocity.y = b->player.velocity.y * (1 - b->acceleration) + b->move_vec[1] * b->acceleration * data->sprint;
	if (b->pushing)
		b->player.moving = 1;
}
