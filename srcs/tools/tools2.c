/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 23:24:40 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/07 23:47:16 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		intersectbox(t_inter *ic)
{
	if (overlap(ic->x0, ic->x1, ic->x2,
		ic->x3) == 1 && overlap(ic->y0, ic->y1, ic->y2, ic->y3) == 1)
		return (1);
	else
		return (0);
}

float	yaw(float y, float z, float yaw)
{
	return (y + z * yaw);
}

float	pointside(t_inter *ic)
{
	return (pv(ic->x1 - ic->x0,
		ic->y1 - ic->y0, ic->px - ic->x0, ic->py - ic->y0));
}

float	clamp(float a, int min, int max)
{
	int temp;

	temp = a > min ? a : min;
	temp = temp < max ? temp : max;
	return (temp);
}

float	fclamp(float a, float min, float max)
{
	float temp;

	temp = a > min ? a : min;
	temp = temp < max ? temp : max;
	return (temp);
}
