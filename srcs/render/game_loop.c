/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 09:47:55 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/06 11:17:35 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void    game_loop(t_data *data, t_b *b)
{
	while (1)
	{
		data->starting_tick = SDL_GetTicks();
		if (data->game_start == 1)
		{
			init_ingame_vars(data, b);
			draw_screen(data, &b->player, b->sectors, b->NumSectors); // norme S
			draw_inventory(data);
			draw_items(data);
			end_game(data); // norme A
			//draw_map(b, data); // norme S
			ft_value_display(data); // norme A
			engine_interaction(b); // norme S
			event_manager(data, b); // norme A
		}
		else
			start_menu(data);
		cap_framerate(data);
		SDL_UpdateWindowSurface(data->wind.window);
	}
}
