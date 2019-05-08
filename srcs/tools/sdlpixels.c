/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdlpixels.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:30:14 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/07 08:24:01 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	Uint32 *pixels;
	Uint32 alpha;

	alpha = pixel & 0xff000000;
	pixels = (Uint32 *)surface->pixels;
	if (x >= 0 && y >= 0 && x < SCREEN_WIDTH && y < SH && alpha != 0xff000000)
		pixels[y * surface->w + x] = pixel;
}

Uint32	get_pixel32(SDL_Surface *surface, int x, int y)
{
	t_pixel pixel;

	pixel.color = 0;
	pixel.pixels = (Uint32*)surface->pixels;
	pixel.pixel = pixel.pixels[y * surface->w + x];
	SDL_GetRGB(pixel.pixel, surface->format, &pixel.r, &pixel.g, &pixel.b);
	pixel.color += pixel.r << 16;
	pixel.color += pixel.g << 8;
	pixel.color += pixel.b;
	return (pixel.color);
}
