/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <smerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 23:31:33 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/08 01:58:52 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_vector	intersect(t_bas *bas, float x3, float x4)
{
	t_vector i;

	i.x = pv(pv(bas->tx1, bas->tz1, bas->tx2, bas->tz2), bas->tx1 - bas->tx2,
		pv(x3, bas->nearz, x4,
		bas->farz), x3 - x4) / pv(bas->tx1 - bas->tx2,
			bas->tz1 - bas->tz2, x3 - x4, bas->nearz - bas->farz);
	i.y = pv(pv(bas->tx1, bas->tz1, bas->tx2, bas->tz2), bas->tz1 - bas->tz2,
		pv(x3, bas->nearz, x4, bas->farz),
		bas->nearz - bas->farz) / pv(bas->tx1
		- bas->tx2, bas->tz1 - bas->tz2, x3 - x4, bas->nearz - bas->farz);
	return (i);
}

float		ft_iatof(char *w, int index)
{
	float	number;
	int		t[3];

	t[2] = 0;
	t[0] = index - 1;
	t[1] = 1;
	number = 0;
	if (w[index] == '-')
	{
		t[0]++;
		t[1] = -1;
	}
	while ((w[t[0]++] && w[t[0]] >= '0' && w[t[0]] <= '9') || w[t[0]] == '.')
	{
		if (w[t[0]] == '.')
		{
			t[2] = 1;
			t[0]++;
		}
		if (t[2] == 1)
			number += (w[t[0]] - '0') / 10.0;
		else
			number = number * 10 + w[t[0]] - '0';
	}
	return (number * t[1]);
}

int			ft_in_hitbox(t_data *data)
{
	if (CROSSHAIR_X > data->sprite[0].x && CROSSHAIR_X
		< data->sprite[0].x + data->sprite[0].size && CROSSHAIR_Y
			> data->sprite[0].y1
				&& CROSSHAIR_Y < data->sprite[0].y1 + data->sprite[0].size)
		return (1);
	return (0);
}

int			ft_iatoi(char *wall, int index)
{
	int number;
	int i;
	int	negative;

	i = index;
	negative = 1;
	number = 0;
	if (wall[index] == '-')
	{
		i++;
		negative = -1;
	}
	while (wall[i] && wall[i] >= '0' && wall[i] <= '9')
	{
		number = number * 10 + wall[i] - '0';
		i++;
	}
	return (number * negative);
}
