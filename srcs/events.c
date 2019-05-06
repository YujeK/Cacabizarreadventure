/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:35:53 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/06 03:03:29 by asamir-k         ###   ########.fr       */
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

void movement_ev(t_data *data, Uint8 *state, float *move_vec, t_plyr *player)
{
	if (state[SDL_SCANCODE_W])
	{
		move_vec[0] += player->anglecos * 0.2f;
		move_vec[1] += player->anglesin * 0.2f;
		if (data->wpn_x < 15 && data->wpn_repos == 0 && data->which_weapon != 0)
			data->wpn_x += 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		move_vec[0] -= player->anglecos * 0.2f;
		move_vec[1] -= player->anglesin * 0.2f;
		if (data->wpn_x > -15 && data->wpn_repos == 0 && data->which_weapon != 0)
			data->wpn_x -= 1;
	}
	if (state[SDL_SCANCODE_D])
	{
		move_vec[0] -= player->anglesin * 0.2f;
		move_vec[1] += player->anglecos * 0.2f;
		if (data->wpn_y > -15 && data->wpn_repos == 0 && data->which_weapon != 0)
			data->wpn_y -= 1;
	}
	if (state[SDL_SCANCODE_A])
	{
		move_vec[0] += player->anglesin * 0.2f;
		move_vec[1] -= player->anglecos * 0.2f;
		if (data->wpn_y < 15 && data->wpn_repos == 0 && data->which_weapon != 0)
			data->wpn_y += 1;
	}
		if (state[SDL_SCANCODE_LSHIFT])
			data->sprint = 1.3;
		if (state[SDL_SCANCODE_LALT])
			data->sprint = 0.4;
	player->ducking = (state[SDL_SCANCODE_LCTRL] || state[SDL_SCANCODE_RCTRL]);
	if (player->ducking)
		data->sprint = 0.3;
}

int event_keyboard(t_plyr *player, t_data *data, float *move_vec, t_sector *sector)
{
	SDL_Event ev;
	SDL_PollEvent(&ev);
	int change;
	Uint8 *state;
	state = (Uint8 *)SDL_GetKeyboardState(0);
	movement_ev(data, state, move_vec, player);
	wpn_bobbing(data);
	stand_ev(data, state, player);
	inv_ev(data, state, move_vec);
	if (state[SDL_SCANCODE_SPACE])
	{
		if (player->velocity.z + 0.05 < sector[player->sector].ceil && data->zawarudo == 1 && time(0) - data->stand_timer > 4)
			player->velocity.z += 0.05;
		else if (player->ground)
		{
			player->velocity.z += 0.5;
			player->falling = 1;
		}
	}
	if (state[SDL_SCANCODE_ESCAPE])
		exit(EXIT_FAILURE);
	change = 1;
	return (change);
}
