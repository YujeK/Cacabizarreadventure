/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:35:53 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 14:09:06 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	shoot_ev(t_data *data)
{
	if (data->aim >= 0 && data->which_weapon != 0 && data->weapon_ammo > 0)
	{
		if (data->sprite[data->aim].status == 0)
		{
			data->score++;
			if (Mix_PlayChannel(3, data->target_hit, 1) == -1)
				ft_error_exit("cant play target_hit");
			Mix_Volume(3, 128 / 2);
		}
		data->sprite[data->aim].status = 1;
		data->death_timer = time(0);
	}
	if (data->weapon_ammo > 0 && data->is_cd == 0)
	{
		if (Mix_PlayChannel(2, data->ak, 0) == -1)
			ft_error_exit("cant play ak");
		Mix_Volume(2, 128 / 4);
		data->weapon_ammo--;
		data->weapon_state = 1;
		data->is_cd = 1;
	}
}

void	event_mouse(t_plyr *player, t_data *data)
{
	int		x;
	int		y;

	SDL_GetRelativeMouseState(&x, &y);
	player->angle += x * 0.005f;
	data->yaw = fclamp(data->yaw + y * 0.01f, -5, 5);
	player->yaw = data->yaw + player->velocity.z * 0.5f;
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) &&
		data->weapon_state == 0 && data->story_step == 3)
		shoot_ev(data);
	else if (data->weapon_state == 1)
		data->weapon_state = 0;
}

void	special_ev(t_data *data, Uint8 *state)
{
	if (state[SDL_SCANCODE_TAB] &&
		data->story_step == 0 && data->msg_readen == 1)
	{
		if (data->inventory_state == 0)
			data->inventory_state = 1;
		data->story_step = 1;
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

void	inv_ev(t_data *data, Uint8 *state)
{
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
	special_ev(data, state);
}

void	event_manager(t_data *data, t_b *b)
{
	event_mouse(&b->player, data);
	b->player = move_player(b);
	event_keyboard(&b->player, data,
		b->move_vec, b->sectors) == 1 ? b->pushing = 1 : 0;
	b->acceleration = b->pushing ? 0.1 : 0.05;
	b->player.velocity.x = b->player.velocity.x * (1 - b->acceleration)
		+ b->move_vec[0] * b->acceleration * data->sprint;
	b->player.velocity.y = b->player.velocity.y * (1 - b->acceleration)
		+ b->move_vec[1] * b->acceleration * data->sprint;
	if (b->pushing)
		b->player.moving = 1;
}
