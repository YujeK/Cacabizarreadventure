/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ev.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:33:22 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/08 18:53:28 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		check_keydown(t_wind wind)
{
	if (wind.event.key.keysym.sym == SDLK_ESCAPE)
	{
		SDL_DestroyWindow(wind.window);
		SDL_Quit();
		return (-1);
	}
	return (0);
}

int		event_keyboard(t_plyr *player, t_data *data,
			float *move_vec, t_sector *sector)
{
	SDL_Event	ev;
	int			change;
	Uint8		*state;

	SDL_PollEvent(&ev);
	state = (Uint8 *)SDL_GetKeyboardState(0);
	movement_ev(data, state, move_vec, player);
	wpn_bobbing(data);
	stand_ev(data, state, player);
	inv_ev(data, state);
	if (state[SDL_SCANCODE_SPACE])
	{
		if (player->velocity.z + 0.05 < sector[player->sector].ceil &&
			data->zawarudo == 1 && time(0) - data->stand_timer > 4)
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

void	move_ev(t_data *data, float *move_vec, t_plyr *player, Uint8 *state)
{
	if (state[SDL_SCANCODE_D])
	{
		move_vec[0] -= player->anglesin * 0.2f;
		move_vec[1] += player->anglecos * 0.2f;
		if (data->wpn_y > -15 && data->wpn_repos == 0 &&
			data->which_weapon != 0)
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
}

void	movement_ev(t_data *data, Uint8 *state, float *move_vec, t_plyr *player)
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
		if (data->wpn_x > -15 && data->wpn_repos == 0 &&
			data->which_weapon != 0)
			data->wpn_x -= 1;
	}
	move_ev(data, move_vec, player, state);
	player->ducking = (state[SDL_SCANCODE_LCTRL] || state[SDL_SCANCODE_RCTRL]);
	if (player->ducking)
		data->sprint = 0.3;
}
