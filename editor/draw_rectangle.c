/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rectangle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 22:11:10 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:46:54 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

void	draw_rectangle(t_coord start, t_coord end, t_wind wind)
{
	int i;
	int j;

	i = start.x - 1;
	while (++i <= end.x)
	{
		j = start.y - 1;
		while (++j <= end.y)
			put_pixel32(wind.screen, i, j, 0xffffff);
	}
}
