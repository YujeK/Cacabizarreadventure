/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 09:47:55 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/08 23:12:05 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	game_loop(t_data *data, t_b *b)
{
	while (1)
	{
		data->starting_tick = SDL_GetTicks();
		if (data->game_start == 1)
		{
			end_game(data);
			init_ingame_vars(data, b);
			draw_screen(data, b);
			draw_inventory(data);
			draw_items(data);
			ft_value_display(data);
			engine_interaction(b);
			move_interaction(b);
			event_manager(data, b);
		}
		else
			start_menu(data);
		cap_framerate(data);
		SDL_UpdateWindowSurface(data->wind.window);
	}
}
