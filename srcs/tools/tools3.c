/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 23:31:33 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/04 04:12:35 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int             rbw(int x)
{
    int         color;
    int         whichcolor;
    int         thiscolor;
    static int  rainbow[7] = {RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE};
    color = 0;
    whichcolor = (SCREEN_WIDTH) / 7;
    thiscolor = 0;
    while (color < 6)
    {
        thiscolor = thiscolor + whichcolor;
        if (x <= thiscolor)
            return (rainbow[color]);
        color++;
    }
    return (rainbow[color]);
}

t_vector	Intersect(float x1, float y1, float x2, float y2, float x3, float  y3, float x4, float y4)
{
	t_vector i;

	i.x = pv(pv(x1, y1, x2, y2), x1 - x2, pv(x3, y3, x4, y4), x3 - x4) / pv(x1 - x2, y1 - y2, x3 - x4, y3 - y4);
	i.y = pv(pv(x1, y1, x2, y2), y1 - y2, pv(x3, y3, x4, y4), y3 - y4) / pv (x1 - x2, y1 - y2, x3 - x4, y3 - y4);
	return (i);
}

float       ft_iatof(char *wall, int index)
{
	float number;
	int i;
	int	negative;
	int d;

	d = 0;
	i = index;
	negative = 1;
	number = 0;
	if (wall[index] == '-')
	{
		i++;
		negative = -1;
	}
	while ((wall[i] && wall[i] >= '0' && wall[i] <= '9') || wall[i] == '.')
	{
		if(wall[i] == '.')
		{
			d = 1;
			i++;
		}
		if (d == 1)
			number += (wall[i] - '0') / 10.0;
		else
			number = number * 10 + wall[i] - '0';
		i++;
	}
	return (number * negative);
}

int         ft_in_hitbox(t_data *data)
{
    if (CROSSHAIR_X > data->sprite[0].x && CROSSHAIR_X < data->sprite[0].x + data->sprite[0].size
        && CROSSHAIR_Y > data->sprite[0].y1 && CROSSHAIR_Y < data->sprite[0].y1 + data->sprite[0].size)
            return (1);
    return (0);
}
