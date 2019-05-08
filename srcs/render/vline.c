/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vline.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <smerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 00:11:11 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/08 11:19:10 by dhorvill         ###   ########.fr       */
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

void	recycle_vline21(t_bas *bas, t_rv *rv)
{
	rv->x = bas->x;
	rv->y1 = bas->cya;
	rv->y2 = bas->cyb;
	rv->top = 0;
	rv->middle = bas->x == bas->x1 || bas->x == bas->x2 ? 0 : bas->r;
	rv->bottom = 0;
}

void	za_warudo(t_data *data, t_rv *rv)
{
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
}

void	vline(t_data *data, t_rv *rv)
{
	int	*pix;
	int	y;

	pix = (int *)data->wind.screen->pixels;
	rv->y1 = clamp(rv->y1, 0, SH - 1);
	rv->y2 = clamp(rv->y2, 0, SH - 1);
	za_warudo(data, rv);
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
	int		*pix;
	int		y;
	double	img_y;
	double	ratio;

	rv->height = bas->yb - bas->ya;
	ratio = 600.0 / rv->height;
	pix = (int *)data->wind.screen->pixels;
	rv->y1 = clamp(rv->y1, 0, SH - 1);
	rv->y2 = clamp(rv->y2, 0, SH - 1);
	img_y = (rv->y1 - bas->ya) * ratio;
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
