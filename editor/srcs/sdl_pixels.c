/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 21:25:33 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:49:21 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

void	put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	Uint32 *pixels;

	pixels = (Uint32 *)surface->pixels;
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
