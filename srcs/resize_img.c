/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <smerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 19:14:40 by smerelo           #+#    #+#             */
/*   Updated: 2019/05/03 02:43:16 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

unsigned int *resize(unsigned int *pixels, t_tga specs, double size)
{
	unsigned int *res_img;
	double prop;
	double i;
	double j;
	int	res_i;
	int res_j;

	j = 0;
	res_j = size - 1;
	prop = specs.width / size;
	if ((res_img = (unsigned int *)malloc((sizeof(res_img)) * size * size)) == 0)
		return (0);
	while (j < specs.height)
	{
		res_i = size - 1;
		i = 0;
		while (i < specs.width)
		{
			if (pixels[(int)j * specs.width + (int)i] != 0xffffffff)
			{
				pixels[(int)j * specs.width + (int)i] -= 0xff000000; 
			}
			res_img[res_j * (int)size + res_i] = pixels[(int)j * specs.width + (int)i];
			i += prop;
			res_i--;
		}
		if (i > specs.width)
			res_img[res_j * (int)size + res_i] = pixels[(int)j * specs.width + specs.width - 1];
		j += prop;
		res_j--;
	}
	return(res_img);
}

void		draw_resized_column(t_data *data, t_object sprite, t_wind wind)
{
	double prop;
	double i;
	double j;
	int res_j;
	double width;

	width = sprite.specs.width;
	j = width - 1;
	res_j = sprite.y1;
	prop = width / sprite.size;
	i = sprite.x_count * prop;
	while (j > 0 && res_j < sprite.y2)
	{
		if (sprite.img[(int)j * sprite.specs.width + (int)i] != 0xffffffff)
			sprite.img[(int)j * sprite.specs.width + (int)i] -= 0xff000000;
		
		if (res_j == SCREEN_HEIGHT / 2 && sprite.x + sprite.x_count == SCREEN_WIDTH / 2)
			data->aim = 2;
		put_pixel32(wind.screen, sprite.x + sprite.x_count, res_j, sprite.img[(int)j * sprite.specs.width + (int)i]);
		j -= prop;
		res_j++;
	}
}
