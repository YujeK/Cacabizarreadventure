/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vline.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <smerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 00:11:11 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/07 14:00:45 by smerelo          ###   ########.fr       */
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

void	vline(t_data *data, t_bas *bas, t_rv *rv)
{
	int *pix;
	int y;

	pix = (int *)data->wind.screen->pixels;
	rv->y1 = clamp(rv->y1, 0, SH - 1);
	rv->y2 = clamp(rv->y2, 0, SH - 1);
	if (data->zawarudo == 1)
	{
		if (time(0) - data->stand_timer > 4)
		{
			data->prev_lum = data->luminosity;
			data->luminosity = 0.999995;
			rv->top = return_grayscale(rv->top);
			rv->middle = return_grayscale(rv->middle);
			rv->bottom = return_grayscale(rv->bottom);
		}
	}
	if (rv->y1 == rv->y2)
	{
		pix[rv->y1 * SCREEN_WIDTH + rv->x] = rv->middle;
	}
	else if (rv->y2 > rv->y1)
	{
		pix[rv->y1 * SCREEN_WIDTH + rv->x] = rv->top;
		y = rv->y1 + 1;
		while (y < rv->y2)
		{
			pix[y * SCREEN_WIDTH + rv->x] = rv->middle;
			pix[rv->y2 * SCREEN_WIDTH + rv->x] = rv->bottom;
			y++;
		}
	}
}

void	vline2(t_data *data, t_bas *bas, t_rv *rv)
{
	int *pix;
	int y;
	double img_y;
	double wall_y1;
	int wall_y2;
	double height;
	double ratio;
	height = bas->yb - bas->ya;
	wall_y1 = rv->y1;
	wall_y2 = rv->y2;
	ratio = 600.0 / height;
	pix = (int *)data->wind.screen->pixels;
	rv->y1 = clamp(rv->y1, 0, SH - 1);
	rv->y2 = clamp(rv->y2, 0, SH - 1);
	img_y = (rv->y1 - bas->ya) * ratio;
	//img_y = 0;
	//height = height < 300 ? height + 200 : height;
	if (rv->y1 == rv->y2)
		pix[rv->y1 * SCREEN_WIDTH + rv->x] = rv->middle;
	else if (rv->y2 > rv->y1)
	{
		pix[rv->y1 * SCREEN_WIDTH + rv->x] = rv->top;
		y = rv->y1 + 1;
		while (y < rv->y2 && img_y < 599)
		{
			pix[y * SCREEN_WIDTH + rv->x] = data->pepo.img[(int)img_y * 599];
			pix[rv->y2 * SCREEN_WIDTH + rv->x] = rv->bottom;
			y++;
			img_y += ratio;
		}
	}
}
