/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vline.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 00:11:11 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/04 14:38:15 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		return_grayscale(int color)
{
	int r;
	int g;
	int b;
	int average;

	b = color % 255;
	color /= 255;
	g = color % 255;
	color /= 255;
	r = color % 255;
	average = (r + g + b) / 3;
	color = average * 0x010000 + average * 0x000100 + average;
	return (color);
}

int		return_redscale(int color)
{
	int	r;
	int	g;
	int	b;
	int	average;

	b = color % 255;
	color /= 255;
	g = color % 255;
	r = color % 255;
	average = (r + g + b) / 3;
	color = average * 0x010000;
	return (color);
}

void	vline(t_data *data, int x, int y1, int y2, int top, int middle, int bottom, SDL_Surface *surface, unsigned int *img)
{
	int *pix;
	int y;

	pix = (int*)surface->pixels;
	y1 = clamp(y1, 0, SCREEN_HEIGHT - 1);
	y2 = clamp(y2, 0, SCREEN_HEIGHT - 1);
	if (data->zawarudo == 1)
	{
		if (time(0) - data->stand_timer > 4)
		{
			data->prev_lum = data->luminosity;
    		data->luminosity = 0.999995;
			top = return_redscale(top);
			middle = return_redscale(middle);
			bottom = return_redscale(bottom);
		}
	}
	if(y1 == y2)
	{
		pix[y1 * SCREEN_WIDTH + x] = middle;
	}
	else if(y2 > y1)
	{
		pix[y1 * SCREEN_WIDTH + x] = top;
		y = y1 + 1;
		while (y < y2)
		{/* 
			if (y == SCREEN_HEIGHT / 2 && x == SCREEN_WIDTH / 2)
				data->aim = 1; */
			pix[y * SCREEN_WIDTH + x] = middle;
			pix[y2 * SCREEN_WIDTH + x] = bottom;
			y++;
		}
	}
}

void	vline2(int x1, int x, int y1, int y2, int top, int middle, int bottom, SDL_Surface *surface, unsigned int *img, int ya, int yb)
{
	int *pix;
	int y;
	double img_y;
	double wall_y1;
	int wall_y2;
	double height;
	double ratio;
	height = yb - ya;
	wall_y1 = y1;
	wall_y2 = y2;
	ratio = 600.0 / height;
	pix = (int*)surface->pixels;
	y1 = clamp(y1, 0, SCREEN_HEIGHT - 1);
	y2 = clamp(y2, 0, SCREEN_HEIGHT - 1);
	img_y = (y1 - ya) * ratio;
	//img_y = 0;
	//printf("%i %i %i\n", y1, y2, y2 - y1);
	//height = height < 300 ? height + 200 : height;
	if(y1 == y2)
		pix[y1 * SCREEN_WIDTH + x] = middle;
	else if(y2 > y1)
	{
		pix[y1 * SCREEN_WIDTH + x] = top;
		y = y1 + 1;
		while (y < y2)
		{
			pix[y * SCREEN_WIDTH + x] = img[(int)img_y * 600 + x] ;
			//printf("%X\n", img[(int)img_y * 600 + x]);
	        pix[y2 * SCREEN_WIDTH + x] = bottom;
			y++;
			img_y += ratio;
		}
	}
}
