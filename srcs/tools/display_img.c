/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 02:08:11 by smerelo           #+#    #+#             */
/*   Updated: 2019/05/07 17:22:31 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	display_img(t_coord pos, t_wind wind, int size, unsigned int *res_img)
{
	int		i;
	int		j;
	int		iprime;
	int		jprime;

	iprime = 0;
	i = -1;
	while (++i < size - 1)
	{
		j = -1;
		jprime = size - 1;
		while (++j < size - 1)
		{
			put_pixel32(wind.screen, j + pos.x, i + pos.y,
				(Uint32)res_img[iprime * size + jprime]);
			jprime--;
		}
		iprime++;
	}
}
