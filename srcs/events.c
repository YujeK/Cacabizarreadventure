/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:35:53 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/03 22:37:18 by dhorvill         ###   ########.fr       */
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
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && data->weapon_state == 0)
	{
		//if (ft_in_hitbox(data) == 1 && data->aim == 2)
		data->weapon_state = 1;
		data->weapon_ammo += (data->weapon_ammo > 0) ? -1 : 100;
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
	if (state[SDL_SCANCODE_R] && data->story_step == 0)
		data->msg_readen = 1;
	if (data->zawarudo == 1)
	{
		Mix_PauseMusic();
		data->toto++;
	}
	else
		Mix_ResumeMusic();
	if (data->toto == 700)
	{
		data->zawarudo = 0;
		data->toto = 0;
	}
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

int event_keyboard(t_plyr *player, t_data *data, float *move_vec)
{
	SDL_Event ev;
	SDL_PollEvent(&ev);
	int change;
	Uint8 *state;
	state = (Uint8 *)SDL_GetKeyboardState(0);
	movement_ev(data, state, move_vec, player);
	wpn_bobbing(data);
	stand_ev(data, state);
	inv_ev(data, state, move_vec);
	if (state[SDL_SCANCODE_SPACE])
	{
		if (player->ground)
		{
			player->velocity.z += 0.5;
			player->falling = 1;
		}
	}
	if (state[SDL_SCANCODE_Q])
		exit(EXIT_FAILURE);
	change = 1;
	return (change);
}
