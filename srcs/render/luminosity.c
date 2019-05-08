/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   luminosity.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:46:12 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/03 07:25:56 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		luminosity(int r1, double z, double luminosity)
{
	double r;
	double g;
	double b;

	b = 0xff;
	g = 0xff;
	r = 0xff;
	r *= pow(luminosity, z);
	g *= pow(luminosity, z);
	b *= pow(luminosity, z);
	r1 = (int)r * 0x010000 + (int)g * 0x000100 + (int)b;
	return (r1);
}
