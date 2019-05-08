/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 19:14:40 by smerelo           #+#    #+#             */
/*   Updated: 2019/05/08 11:11:05 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

unsigned int	*resize(unsigned int *p, t_tga spe, double size)
{
	unsigned int	*im;
	double			t[3];
	int				r[2];

	t[2] = 0;
	r[1] = size - 1;
	t[0] = spe.width / size;
	if ((im = (unsigned int *)malloc((sizeof(im)) * size * size)) == 0)
		return (0);
	while (r[1] >= 0)
	{
		r[0] = size - 1;
		t[1] = 0;
		while (r[0] >= 0)
		{
			if (p[(int)t[2] * spe.width + (int)t[1]] != 0xffffffff)
				p[(int)t[2] * spe.width + (int)t[1]] -= 0xff000000;
			im[r[1] * (int)size + r[0]] = p[(int)t[2] * spe.width + (int)t[1]];
			t[1] += t[0];
			r[0]--;
		}
		t[2] += t[0];
		r[1]--;
	}
	return (im);
}

void			draw_resized_column(t_data *d, t_object *s)
{
	double		t[3];
	int			res_j;
	double		width;

	width = s->specs.width;
	t[2] = width - 1;
	res_j = s->y1 - 1;
	t[0] = width / s->size;
	t[1] = s->x_count * t[0];
	while (t[2] > 0 && ++res_j < s->y2)
	{
		if (s->img[(int)t[2] * s->specs.width + (int)t[1]] != 0xffffffff)
			s->img[(int)t[2] * s->specs.width + (int)t[1]] -= 0xff000000;
		if (res_j == SH / 2 && s->x + s->x_count == SCREEN_WIDTH / 2)
		{
			d->aim = s->i;
		}
		if (s->status == 1)
			put_pixel32(d->wind.screen, s->x + s->x_count,
				res_j, s->dead_img[(int)t[2] * s->specs.width + (int)t[1]]);
		if (s->status == 0)
			put_pixel32(d->wind.screen, s->x + s->x_count,
				res_j, s->img[(int)t[2] * s->specs.width + (int)t[1]]);
		t[2] -= t[0];
	}
}
