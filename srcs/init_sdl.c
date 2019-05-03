/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 23:53:54 by asamir-k          #+#    #+#             */
/*   Updated: 2019/04/04 19:56:46 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_wind		init_wind(t_wind wind)
{
	wind.screen = NULL;
	wind.window = SDL_CreateWindow("Doom_Nukem", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	wind.screen = SDL_GetWindowSurface(wind.window);
	return (wind);
}
