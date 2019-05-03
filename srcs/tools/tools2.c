/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 23:24:40 by asamir-k          #+#    #+#             */
/*   Updated: 2019/04/30 02:38:08 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int overlap(float a1 ,float a2, float b1, float b2)
{
	if(min(a1, a2) <= max(b1, b2) && min(b1, b2) <= max(a1, a2))
		return(1);
	else
		return (0);
}

int IntersectBox(float x0, float y0, float x1, float y1, float x2, float y2,  float x3, float y3)
{
	if(overlap(x0, x1, x2, x3) == 1 && overlap(y0, y1, y2, y3) == 1)
		return (1);
	else
		return (0);
}

float	yaw(float y, float z, float Yaw)
{
	return(y + z * Yaw);
}

float	pointside(float px, float py, float x0, float y0, float x1, float y1)
{
	return (pv(x1 - x0, y1 - y0, px - x0, py - y0));
}

float clamp(float a , int min, int max)
{
	int temp;

	temp = a > min ? a : min;
	temp = temp < max ? temp : max;
	return (temp);
}


float fclamp(float a , float min, float max)
{
	float temp;

	temp = a > min ? a : min;
	temp = temp < max ? temp : max;
	return (temp);
}
