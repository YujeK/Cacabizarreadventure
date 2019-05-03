/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stand_ev.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 02:26:57 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/03 09:03:39 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void    stand_ev(t_data *data, Uint8 *state)
{
    if (state[SDL_SCANCODE_KP_2] && state[SDL_SCANCODE_KP_4] && state[SDL_SCANCODE_KP_8] && state[SDL_SCANCODE_KP_6])
    {
    data->zawarudo = 1;
    data->stand_timer = time(0);
    if (Mix_PlayChannel(0, data->stand_warudo, 0) == -1)
		ft_error_exit("cant play zawarudo", data);
    }
    if (state[SDL_SCANCODE_KP_7] && state[SDL_SCANCODE_KP_5] && state[SDL_SCANCODE_KP_3])
      ft_putstr("over the rainbow");
}
