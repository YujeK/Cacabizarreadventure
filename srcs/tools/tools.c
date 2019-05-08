/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 23:18:51 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/07 14:56:24 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

float	max(float a, float b)
{
	return (a > b ? a : b);
}

int		imax(int a, int b)
{
	return (a > b ? a : b);
}

int		imin(int a, int b)
{
	return (a < b ? a : b);
}

float	min(float a, float b)
{
	return (a < b ? a : b);
}

float	pv(float x0, float y0, float x1, float y1)
{
	return (x0 * y1 - x1 * y0);
}
